# EO-IR Motor Control

EO/IR 짐벌 시스템의 Pan-Tilt 모터 제어 소프트웨어입니다.  
OpenRB-150 펌웨어부터 ROS2 제어 노드까지 전체 스택을 포함합니다.

---

## 시스템 구성

```
GUI ──UDP──→ Thor(ROS2) ──UDP──→ Zybo Bridge ──UART──→ OpenRB ──Dynamixel──→ Pan/Tilt Motor
GUI ←─UDP── Thor(ROS2) ←─UDP── Zybo Bridge ←─UART── OpenRB ←─────────────── Pan/Tilt Motor
```

| 컴포넌트 | 플랫폼 | 역할 |
|----------|--------|------|
| **GUI** | PC | 모드 전환, 버튼 조작, 상태 모니터링 |
| **Thor** | Jetson (ROS2) | 제어 명령 생성, PID 트래킹, 피드백 처리 |
| **Zybo Bridge** | Zybo FPGA | UDP ↔ UART 프로토콜 변환 (바이패스) |
| **OpenRB** | OpenRB-150 | Dynamixel 모터 직접 제어 |
| **Motor** | Dynamixel | Pan(ID=1), Tilt(ID=2) 2축 구동 |

---

## 제어 모드

GUI에서 **자동/수동** 과 **추적/비추적** 두 가지를 조합해 최종 모드가 결정됩니다.

| auto_manual | tracking | 최종 모드 | 동작 |
|-------------|----------|-----------|------|
| 0 (scan) | 0 (비추적) | SCAN | scan_step으로 팬 자동 왕복 |
| 1 (manual) | 0 (비추적) | MANUAL | 버튼으로 팬/틸트 수동 조작 |
| 1 (manual) | 1 (추적) | TRACK | PID 제어 결과를 모터에 직접 전달 |

Thor가 두 값을 조합해 `mode_cmd`(0/1/2)로 변환 후 Zybo로 전달합니다.

---

## 패킷 구조

### 명령 (GUI → Thor → Zybo → OpenRB)

| 구간 | 크기 | 주요 필드 |
|------|------|-----------|
| GUI → Thor | 9B (UDP) | auto_manual(1) + tracking(1) + btn(1) + pan(2) + tilt(2) + scan_step(1) + manual_step(1) |
| Thor → Zybo | 8B (UDP) | mode_cmd(1) + btn(1) + pan(2) + tilt(2) + scan_step(1) + manual_step(1) |
| Zybo → OpenRB | 11B (UART) | AA + mode_cmd + btn + pan(2) + tilt(2) + scan_step + manual_step + CHK + 55 |

> `mode_cmd` : Thor가 조합 후 OpenRB에 내리는 최종 명령 (0=SCAN, 1=MANUAL, 2=TRACK)

### 피드백 (OpenRB → Zybo → Thor → GUI)

| 구간 | 크기 | 주요 필드 |
|------|------|-----------|
| OpenRB → Zybo | 40B (UART) | AA + mode_status + PAN(18B) + TILT(18B) + CHK + 55 |
| Zybo → Thor | 36B (UDP) | PAN(18B) + TILT(18B) |
| Thor → GUI | 36B (UDP) | PAN(18B) + TILT(18B) |

> `mode_status` : OpenRB가 현재 실행 중인 **동작 상태** (0=SCAN, 1=MANUAL, 2=TRACK)

---

## 디렉토리 구조

```
project/
├── src/
│   ├── sentinel_motor/          # Thor: ROS2 Pan-Tilt 제어 노드
│   │   ├── src/
│   │   │   ├── pan_tilt_control_node.cpp
│   │   │   └── tracking_control_node.cpp
│   │   └── include/sentinel_motor/
│   │       ├── PacketDef.hpp    # 패킷 구조체 정의
│   │       └── UdpTransport.hpp # UDP 송수신
│   ├── sentinel_interfaces/     # ROS2 커스텀 메시지 정의
│   │   └── msg/
│   │       ├── MotorAngle.msg
│   │       ├── MotorStatus.msg
│   │       └── ...
│   └── gui_interface/           # GUI ROS2 인터페이스 노드
├── gui/
│   └── gui.py                   # Pan/Tilt UDP GUI
├── zybo/
│   ├── zybo_bridge.cpp          # Zybo: UDP ↔ UART 브릿지
│   └── README.md
├── openrb/
│   ├── openrb_firmware.ino      # OpenRB: 모터 펌웨어 (Arduino)
│   └── README.md
├── Dockerfile
├── docker-compose.yml
└── .gitignore
```

---

## 빌드 및 실행

### Thor (ROS2)

```bash
cd ~/project
colcon build --packages-select sentinel_interfaces sentinel_motor gui_interface
source install/setup.bash

# Pan-Tilt 제어 노드 실행
ros2 launch sentinel_motor pan_tilt_control.launch.py
```

### Zybo Bridge

```bash
g++ -std=c++17 -O2 zybo_bridge.cpp -o zybo_bridge -lboost_system -lpthread

# 실행 (Thor IP 자동 감지)
./zybo_bridge --udp-port 6000 --feedback-port 6001 --serial /dev/ttyPS1
```

### OpenRB 펌웨어

Arduino IDE에서 `openrb_firmware.ino` 열고 OpenRB-150 보드에 업로드

### GUI

```bash
python3 gui/gui.py --ip <Thor IP> --cmd-port 3000 --tlm-port 5001
```

---

## 통신 설정

| 항목 | 값 |
|------|----|
| GUI ↔ Thor UDP 포트 (명령) | 3000 |
| GUI ↔ Thor UDP 포트 (피드백) | 5001 |
| Thor ↔ Zybo UDP 포트 (명령) | 6000 |
| Thor ↔ Zybo UDP 포트 (피드백) | 6001 |
| Zybo ↔ OpenRB UART 속도 | 115200 bps |
| OpenRB ↔ Dynamixel 속도 | 1,000,000 bps |
| Dynamixel 프로토콜 | 2.0 |

---

## 브랜치 구조

```
main
└── dev
    ├── feature/openrb-firmware   # OpenRB 모터 펌웨어
    ├── feature/zybo              # Zybo 브릿지
    ├── feature/thor              # Thor ROS2 제어 노드
    └── feature/gui               # Pan/Tilt GUI
```

---

## 개발 환경

- ROS2 Humble
- Ubuntu 22.04
- Boost.Asio (Zybo Bridge)
- Arduino IDE / Dynamixel2Arduino (OpenRB)
- Python 3.x / tkinter (GUI)