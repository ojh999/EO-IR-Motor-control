#!/usr/bin/env python3
"""
Pan/Tilt Gimbal UDP GUI — matched to system design document

GUI -> Thor UDP: 9 bytes
    Byte 0      : mode (1B)  0=scan, 1=manual
    Byte 1      : tracking (1B)  0=off, 1=on
    Byte 2      : manual-mode button bitmask (1B)
    Byte 3..4   : pan position (uint16, little-endian, 0~4095)
    Byte 5..6   : tilt position (uint16, little-endian, 0~4095)
    Byte 7      : scan step (1B)
    Byte 8      : manual step (1B)

Thor -> GUI UDP: 36 bytes
    Byte 0..17  : pan MotorFeedback raw 18B
    Byte 18..35 : tilt MotorFeedback raw 18B

Run:
    python3 gui_test.py --ip 192.168.3.143 --cmd-port 3000 --tlm-port 5001

Keys:
    1 / 2          : Scan / Manual mode
    T              : Tracking toggle
    Arrow keys     : direction (manual mode only)
    W/A/S/D        : direction (manual mode only)
    C              : Home/center
    +/-            : Step size of current mode
"""

import argparse
import socket
import struct
import threading
import time
import tkinter as tk
from tkinter import ttk
from dataclasses import dataclass, field

# ─── Protocol Constants ───────────────────────────────────────────────

BUTTON_L = 0x01
BUTTON_R = 0x02
BUTTON_U = 0x04
BUTTON_D = 0x08
BUTTON_C = 0x10

MODE_SCAN = 0
MODE_MANUAL = 1
MODE_NAMES = {
    MODE_SCAN: "Scan",
    MODE_MANUAL: "Manual",
}

MOTOR_FB_SIZE = 18
TLM_PACKET_SIZE = 36

PAN_MIN = 0
PAN_MAX = 4095
TILT_MIN = 0
TILT_MAX = 4095
CENTER_POS = 2047


# ─── Data Model ──────────────────────────────────────────────────────

@dataclass
class MotorFeedback:
    moving: int = 0
    moving_status: int = 0
    pwm: int = 0
    current: int = 0
    velocity: int = 0
    position: int = 0
    voltage: int = 0
    temperature: int = 0
    hw_error: int = 0


@dataclass
class TelemetryState:
    pan: MotorFeedback = field(default_factory=MotorFeedback)
    tilt: MotorFeedback = field(default_factory=MotorFeedback)
    rx_packets: int = 0
    rx_bad_packets: int = 0
    last_rx_time: float = 0.0


# ─── Network Layer ───────────────────────────────────────────────────

class UdpTransceiver:
    def __init__(self, target_ip: str, cmd_port: int, tlm_port: int):
        self.target = (target_ip, cmd_port)

        self.tx_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        self.rx_sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.rx_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.rx_sock.bind(("0.0.0.0", tlm_port))
        self.rx_sock.settimeout(0.1)

    def send_cmd(
        self,
        mode: int,
        tracking: int,
        button: int,
        pan_pos: int,
        tilt_pos: int,
        scan_step: int,
        manual_step: int,
    ):
        """Send GUI -> Thor 9B command packet."""
        pan_pos = max(PAN_MIN, min(PAN_MAX, int(pan_pos)))
        tilt_pos = max(TILT_MIN, min(TILT_MAX, int(tilt_pos)))

        pkt = struct.pack(
            "<BBBHHBB",
            mode & 0xFF,
            tracking & 0xFF,
            button & 0xFF,
            pan_pos & 0xFFFF,
            tilt_pos & 0xFFFF,
            scan_step & 0xFF,
            manual_step & 0xFF,
        )
        self.tx_sock.sendto(pkt, self.target)

    def recv(self) -> bytes | None:
        try:
            data, _ = self.rx_sock.recvfrom(256)
            return data
        except socket.timeout:
            return None

    def close(self):
        self.tx_sock.close()
        self.rx_sock.close()


# ─── TLM Parser ──────────────────────────────────────────────────────

def _parse_motor_fb(data: bytes, offset: int) -> MotorFeedback:
    fb = MotorFeedback()
    fb.moving = data[offset]
    fb.moving_status = data[offset + 1]
    fb.pwm = struct.unpack_from("<H", data, offset + 2)[0]
    fb.current = struct.unpack_from("<H", data, offset + 4)[0]
    fb.velocity = struct.unpack_from("<I", data, offset + 6)[0]
    fb.position = struct.unpack_from("<I", data, offset + 10)[0]
    fb.voltage = struct.unpack_from("<H", data, offset + 14)[0]
    fb.temperature = data[offset + 16]
    fb.hw_error = data[offset + 17]
    return fb


def parse_tlm_36b(data: bytes, state: TelemetryState) -> bool:
    if len(data) != TLM_PACKET_SIZE:
        state.rx_bad_packets += 1
        return False

    state.pan = _parse_motor_fb(data, 0)
    state.tilt = _parse_motor_fb(data, MOTOR_FB_SIZE)
    state.rx_packets += 1
    state.last_rx_time = time.time()
    return True


# ─── GUI ─────────────────────────────────────────────────────────────

def step_to_deg(step: int) -> float:
    return step * 360.0 / 4095.0


def clamp_u16_step(value: int) -> int:
    return max(0, min(4095, int(value)))


class App:
    SEND_INTERVAL_MS = 50
    STEP_MIN = 1
    STEP_MAX = 10

    KEY_MAP = {
        "Left": "L", "Right": "R", "Up": "U", "Down": "D",
        "a": "L", "d": "R", "w": "U", "s": "D",
        "c": "C",
    }

    def __init__(self, udp: UdpTransceiver):
        self.udp = udp
        self.tlm = TelemetryState()
        self.running = True

        self.current_mode = MODE_MANUAL
        self.tracking = False
        self.scan_step = 1
        self.manual_step = 1
        self.pan_cmd = CENTER_POS
        self.tilt_cmd = CENTER_POS
        self.pressed_keys: set[str] = set()

        self.root = tk.Tk()
        self.root.title("Pan/Tilt UDP GUI — 9B CMD / 36B TLM")
        self.root.configure(bg="#1e1e2e")
        self.root.resizable(False, False)

        self._init_style()
        self._build_layout()
        self._bind_keys()

        self._start_rx_thread()
        self._schedule_tx()
        self._schedule_tlm_update()

        self._send_current_cmd("initial")
        self._log(f"Ready — CMD 9B -> {udp.target[0]}:{udp.target[1]}, TLM 36B RX")

    def _init_style(self):
        style = ttk.Style()
        style.theme_use("clam")
        style.configure("TFrame", background="#1e1e2e")
        style.configure("TLabel", background="#1e1e2e", foreground="#cdd6f4", font=("Menlo", 11))
        style.configure("H.TLabel", background="#1e1e2e", foreground="#89b4fa", font=("Menlo", 13, "bold"))
        style.configure("V.TLabel", background="#1e1e2e", foreground="#a6e3a1", font=("Menlo", 16, "bold"))
        style.configure("TButton", font=("Menlo", 11))
        style.configure("TLabelframe", background="#1e1e2e", foreground="#89b4fa")
        style.configure("TLabelframe.Label", background="#1e1e2e", foreground="#89b4fa", font=("Menlo", 11, "bold"))

    def _build_layout(self):
        main = ttk.Frame(self.root, padding=16)
        main.pack()

        info = ttk.Frame(main)
        info.pack(fill="x", pady=(0, 8))
        ttk.Label(info, text=f"Target Thor: {self.udp.target[0]}:{self.udp.target[1]}  |  CMD=9B, TLM=36B").pack(side="left")

        # ── Mode + Tracking ──
        mode_frame = ttk.LabelFrame(main, text="  Mode  ", padding=8)
        mode_frame.pack(fill="x", pady=(0, 8))

        self.mode_btns = {}
        for val, name in MODE_NAMES.items():
            btn = ttk.Button(mode_frame, text=f"{val}: {name}", width=14, command=lambda v=val: self._set_mode(v))
            btn.pack(side="left", padx=4)
            self.mode_btns[val] = btn
        self._highlight_mode()

        self.track_var = tk.BooleanVar(value=False)
        self.track_chk = tk.Checkbutton(
            mode_frame, text="추적", variable=self.track_var,
            font=("Menlo", 11, "bold"), bg="#1e1e2e", fg="#f38ba8",
            selectcolor="#313244", activebackground="#1e1e2e", activeforeground="#f38ba8",
            command=self._on_track_toggle,
        )
        self.track_chk.pack(side="left", padx=(16, 4))

        # ── Direction Pad ──
        pad_frame = ttk.LabelFrame(main, text="  Direction / Home (Manual only)  ", padding=12)
        pad_frame.pack(fill="x", pady=(0, 8))

        grid = ttk.Frame(pad_frame)
        grid.pack()

        self.btn_labels = {}
        positions = {"U": (0, 1), "L": (1, 0), "C": (1, 1), "R": (1, 2), "D": (2, 1)}
        symbols = {"U": "▲", "L": "◄", "C": "●", "R": "►", "D": "▼"}
        for name, (r, c) in positions.items():
            lbl = tk.Label(grid, text=symbols[name], font=("Menlo", 22), width=3, height=1,
                           bg="#313244", fg="#6c7086", relief="flat", cursor="hand2")
            lbl.grid(row=r, column=c, padx=3, pady=3)
            lbl.bind("<ButtonPress-1>", lambda e, n=name: self._on_btn_mouse_press(n))
            lbl.bind("<ButtonRelease-1>", lambda e, n=name: self._on_btn_mouse_release(n))
            self.btn_labels[name] = lbl

        self.tx_var = tk.StringVar()
        ttk.Label(pad_frame, textvariable=self.tx_var, style="V.TLabel").pack(pady=(8, 0))

        # ── Pan/Tilt Entry ──
        pos_frame = ttk.LabelFrame(main, text="  Pan/Tilt Command Position (Enter로 전송)  ", padding=8)
        pos_frame.pack(fill="x", pady=(0, 8))

        self.pan_var = tk.StringVar(value=str(self.pan_cmd))
        self.tilt_var = tk.StringVar(value=str(self.tilt_cmd))
        self._make_pos_entry(pos_frame, "Pan", self.pan_var, self._on_pan_enter)
        self._make_pos_entry(pos_frame, "Tilt", self.tilt_var, self._on_tilt_enter)

        # ── Step Size ──
        step_frame = ttk.LabelFrame(main, text="  Step Size  ", padding=8)
        step_frame.pack(fill="x", pady=(0, 8))

        self.scan_step_var = tk.StringVar(value=str(self.scan_step))
        self.manual_step_var = tk.StringVar(value=str(self.manual_step))
        self.active_step_var = tk.StringVar()
        self._make_step_row(step_frame, "Scan", self.scan_step_var, self._scan_step_dec, self._scan_step_inc)
        self._make_step_row(step_frame, "Manual", self.manual_step_var, self._manual_step_dec, self._manual_step_inc)
        ttk.Label(step_frame, textvariable=self.active_step_var, style="H.TLabel").pack(pady=(4, 0))
        self._update_active_step_label()

        # ── Telemetry ──
        tlm_frame = ttk.LabelFrame(main, text="  Thor -> GUI Telemetry 36B  ", padding=8)
        tlm_frame.pack(fill="x", pady=(0, 8))

        self.tlm_text = tk.Text(tlm_frame, height=11, width=62, font=("Menlo", 11),
                                bg="#181825", fg="#cdd6f4", insertbackground="#cdd6f4",
                                relief="flat", state="disabled", borderwidth=0)
        self.tlm_text.pack()

        # ── Log ──
        log_frame = ttk.LabelFrame(main, text="  Log  ", padding=8)
        log_frame.pack(fill="x")

        self.log_text = tk.Text(log_frame, height=5, width=62, font=("Menlo", 10),
                                bg="#181825", fg="#a6adc8", relief="flat", state="disabled", borderwidth=0)
        self.log_text.pack()

    def _make_pos_entry(self, parent, name: str, var: tk.StringVar, on_enter):
        row = ttk.Frame(parent)
        row.pack(fill="x", pady=2)
        ttk.Label(row, text=f"{name}:", width=7).pack(side="left")
        entry = tk.Entry(row, textvariable=var, font=("Menlo", 14), width=8,
                         bg="#313244", fg="#a6e3a1", insertbackground="#a6e3a1",
                         relief="flat", justify="center")
        entry.pack(side="left", padx=6)
        entry.bind("<Return>", on_enter)
        ttk.Label(row, text="0~4095").pack(side="left", padx=8)

    def _make_step_row(self, parent, name: str, var: tk.StringVar, dec_cmd, inc_cmd):
        row = ttk.Frame(parent)
        row.pack(fill="x", pady=2)
        ttk.Label(row, text=f"{name}:", width=8).pack(side="left")
        ttk.Button(row, text="−", width=3, command=dec_cmd).pack(side="left", padx=2)
        tk.Label(row, textvariable=var, font=("Menlo", 18, "bold"), width=4,
                 bg="#313244", fg="#89b4fa", relief="flat").pack(side="left", padx=4)
        ttk.Button(row, text="+", width=3, command=inc_cmd).pack(side="left", padx=2)
        ttk.Label(row, text="1~10").pack(side="left", padx=8)

    def _bind_keys(self):
        self.root.bind("<KeyPress>", self._on_key_press)
        self.root.bind("<KeyRelease>", self._on_key_release)
        self.root.protocol("WM_DELETE_WINDOW", self._on_close)

    # ── Command State ────────────────────────────────────────────────

    def _set_mode(self, mode: int):
        self.current_mode = mode
        self._highlight_mode()
        self._update_active_step_label()
        self._send_current_cmd("mode")
        self._log(f"Mode -> {MODE_NAMES[mode]}")

    def _highlight_mode(self):
        for mode, btn in self.mode_btns.items():
            btn.state(["pressed"] if mode == self.current_mode else ["!pressed"])

    def _on_pan_enter(self, event=None):
        try:
            val = clamp_u16_step(int(self.pan_var.get()))
        except ValueError:
            val = self.pan_cmd
        self.pan_cmd = val
        self.pan_var.set(str(val))
        self._send_current_cmd("pan")
        self._log(f"Pan -> {val}")

    def _on_tilt_enter(self, event=None):
        try:
            val = clamp_u16_step(int(self.tilt_var.get()))
        except ValueError:
            val = self.tilt_cmd
        self.tilt_cmd = val
        self.tilt_var.set(str(val))
        self._send_current_cmd("tilt")
        self._log(f"Tilt -> {val}")

    def _on_track_toggle(self):
        self.tracking = self.track_var.get()
        self._send_current_cmd("track")
        self._log(f"Tracking -> {'ON' if self.tracking else 'OFF'}")

    def _on_btn_mouse_press(self, name: str):
        if name not in self.pressed_keys:
            self.pressed_keys.add(name)
            if name == "C":
                self.pan_cmd = CENTER_POS
                self.tilt_cmd = CENTER_POS
                self.pan_var.set(str(self.pan_cmd))
                self.tilt_var.set(str(self.tilt_cmd))
            self._update_pad_visual()
            self._send_current_cmd("mouse_press")

    def _on_btn_mouse_release(self, name: str):
        self.pressed_keys.discard(name)
        self._update_pad_visual()

    def _scan_step_inc(self):
        if self.scan_step < self.STEP_MAX:
            self.scan_step += 1
            self.scan_step_var.set(str(self.scan_step))
            self._update_active_step_label()
            self._send_current_cmd("scan_step")

    def _scan_step_dec(self):
        if self.scan_step > self.STEP_MIN:
            self.scan_step -= 1
            self.scan_step_var.set(str(self.scan_step))
            self._update_active_step_label()
            self._send_current_cmd("scan_step")

    def _manual_step_inc(self):
        if self.manual_step < self.STEP_MAX:
            self.manual_step += 1
            self.manual_step_var.set(str(self.manual_step))
            self._update_active_step_label()
            self._send_current_cmd("manual_step")

    def _manual_step_dec(self):
        if self.manual_step > self.STEP_MIN:
            self.manual_step -= 1
            self.manual_step_var.set(str(self.manual_step))
            self._update_active_step_label()
            self._send_current_cmd("manual_step")

    def _update_active_step_label(self):
        if self.current_mode == MODE_SCAN:
            self.active_step_var.set(f"Active step: scan={self.scan_step}")
        else:
            self.active_step_var.set(f"Active step: manual={self.manual_step}")

    def _build_button_mask(self) -> int:
        """수동 모드일 때만 버튼 bitmask 반환, 그 외 0."""
        if self.current_mode != MODE_MANUAL:
            return 0x00
        mask = 0
        if "L" in self.pressed_keys: mask |= BUTTON_L
        if "R" in self.pressed_keys: mask |= BUTTON_R
        if "U" in self.pressed_keys: mask |= BUTTON_U
        if "D" in self.pressed_keys: mask |= BUTTON_D
        if "C" in self.pressed_keys: mask |= BUTTON_C
        return mask

    def _send_current_cmd(self, reason: str = ""):
        button = self._build_button_mask()
        track_flag = 1 if self.tracking else 0

        self.udp.send_cmd(
            self.current_mode,     # byte 0: mode (0=scan, 1=manual)
            track_flag,            # byte 1: tracking (0=off, 1=on)
            button,                # byte 2: manual button bitmask
            self.pan_cmd,          # byte 3-4: pan
            self.tilt_cmd,         # byte 5-6: tilt
            self.scan_step,        # byte 7: scan step
            self.manual_step,      # byte 8: manual step
        )

        track_str = " [TRACK]" if self.tracking else ""
        self.tx_var.set(
            f"TX 9B: mode={self.current_mode}({MODE_NAMES[self.current_mode]}) "
            f"track={track_flag} btn=0x{button:02X} "
            f"pan={self.pan_cmd} tilt={self.tilt_cmd} "
            f"S={self.scan_step} M={self.manual_step}{track_str}"
        )

    # ── Key Handling ─────────────────────────────────────────────────

    def _on_key_press(self, event):
        btn = self.KEY_MAP.get(event.keysym)
        if btn and btn not in self.pressed_keys:
            self.pressed_keys.add(btn)
            if btn == "C":
                self.pan_cmd = CENTER_POS
                self.tilt_cmd = CENTER_POS
                self.pan_var.set(str(self.pan_cmd))
                self.tilt_var.set(str(self.tilt_cmd))
            self._update_pad_visual()
            self._send_current_cmd("key_press")

        if event.keysym == "1":
            self._set_mode(MODE_SCAN)
        elif event.keysym == "2":
            self._set_mode(MODE_MANUAL)
        elif event.keysym == "t":
            self.track_var.set(not self.track_var.get())
            self._on_track_toggle()
        elif event.keysym in ("plus", "equal"):
            if self.current_mode == MODE_SCAN:
                self._scan_step_inc()
            else:
                self._manual_step_inc()
        elif event.keysym in ("minus", "underscore"):
            if self.current_mode == MODE_SCAN:
                self._scan_step_dec()
            else:
                self._manual_step_dec()

    def _on_key_release(self, event):
        btn = self.KEY_MAP.get(event.keysym)
        if btn and btn in self.pressed_keys:
            self.pressed_keys.discard(btn)
            self._update_pad_visual()

    def _update_pad_visual(self):
        for name, lbl in self.btn_labels.items():
            if name in self.pressed_keys and self.current_mode == MODE_MANUAL:
                lbl.configure(bg="#89b4fa", fg="#1e1e2e")
            else:
                lbl.configure(bg="#313244", fg="#6c7086")

    def _schedule_tx(self):
        if not self.running:
            return
        if self.pressed_keys:
            self._send_current_cmd("periodic")
        self.root.after(self.SEND_INTERVAL_MS, self._schedule_tx)

    # ── Telemetry RX ─────────────────────────────────────────────────

    def _start_rx_thread(self):
        def _rx_loop():
            while self.running:
                data = self.udp.recv()
                if data is not None:
                    parse_tlm_36b(data, self.tlm)
        threading.Thread(target=_rx_loop, daemon=True).start()

    def _schedule_tlm_update(self):
        if not self.running:
            return

        s = self.tlm
        p = s.pan
        t = s.tilt
        now = time.time()
        age = now - s.last_rx_time if s.last_rx_time else 0.0
        hw = lambda e: "OK" if e == 0 else f"0x{e:02X}"

        lines = [
            "┌─ Motor Feedback: Thor -> GUI 36B ─────────────────────────┐",
            "│                Pos(step)   Pos(°)   Curr   Temp   HwErr    │",
            f"│  Pan       {p.position:>10d}  {step_to_deg(p.position):>7.1f}  {p.current:>5d}  {p.temperature:>4d}°  {hw(p.hw_error):<7s}│",
            f"│  Tilt      {t.position:>10d}  {step_to_deg(t.position):>7.1f}  {t.current:>5d}  {t.temperature:>4d}°  {hw(t.hw_error):<7s}│",
            "├─ Raw Status ───────────────────────────────────────────────┤",
            f"│  Pan  moving={p.moving} status={p.moving_status} pwm={p.pwm:>5d} vel={p.velocity:>7d} │",
            f"│  Tilt moving={t.moving} status={t.moving_status} pwm={t.pwm:>5d} vel={t.velocity:>7d} │",
            f"│  Voltage: pan={p.voltage:>5d}, tilt={t.voltage:>5d}                      │",
            "├─ Packet Counter ───────────────────────────────────────────┤",
            f"│  good={s.rx_packets:>7d}  bad_len={s.rx_bad_packets:>7d}  last_age={age:>5.2f}s       │",
            "└────────────────────────────────────────────────────────────┘",
        ]

        self.tlm_text.configure(state="normal")
        self.tlm_text.delete("1.0", "end")
        self.tlm_text.insert("1.0", "\n".join(lines))
        self.tlm_text.configure(state="disabled")

        self.root.after(100, self._schedule_tlm_update)

    # ── Log / Cleanup ────────────────────────────────────────────────

    def _log(self, msg: str):
        ts = time.strftime("%H:%M:%S")
        self.log_text.configure(state="normal")
        self.log_text.insert("end", f"[{ts}] {msg}\n")
        self.log_text.see("end")
        self.log_text.configure(state="disabled")

    def _on_close(self):
        self.running = False
        self.udp.close()
        self.root.destroy()

    def run(self):
        self.root.mainloop()


# ─── Main ────────────────────────────────────────────────────────────

def main():
    parser = argparse.ArgumentParser(description="Pan/Tilt UDP GUI: GUI->Thor 9B, Thor->GUI 36B")
    parser.add_argument("--ip", default="10.42.0.168", help="Thor IP address")
    parser.add_argument("--cmd-port", type=int, default=3000, help="GUI -> Thor UDP port")
    parser.add_argument("--tlm-port", type=int, default=5001, help="Thor -> GUI UDP receive port")
    args = parser.parse_args()

    print("Pan/Tilt UDP GUI")
    print(f"  GUI -> Thor CMD : {args.ip}:{args.cmd_port} / 9B")
    print(f"  Thor -> GUI TLM : 0.0.0.0:{args.tlm_port} / 36B")
    print("  CMD packet      : <BBBHHBB = mode, tracking, button, pan, tilt, scan_step, manual_step")
    print()

    udp = UdpTransceiver(args.ip, args.cmd_port, args.tlm_port)
    app = App(udp)
    app.run()


if __name__ == "__main__":
    main()
