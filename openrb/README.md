# OpenRB-150 Pan-Tilt Firmware

Dynamixel 모터 2축(Pan/Tilt)을 제어하는 OpenRB-150 펌웨어입니다.  
UART(Serial3)로 상위 보드(Zybo)와 통신하며, SCAN / MANUAL / TRACK 3가지 모드를 지원합니다.

---

## 시스템 구성

```
openRB  ←──UART──→  Zybo  ←──UDP──→  Thor  ←──UDP──→  GUI
```

OpenRB는 Zybo와 UART(115200bps)로만 통신합니다.  
Serial3 = Zybo 통신용, Serial1 = Dynamixel 버스, Serial = USB 디버그 출력

---

## 패킷 구조

### RX 프레임 (Zybo → OpenRB, 11B)

| 인덱스 | 필드 | 크기 | 설명 |
|--------|------|------|------|
| [0] | FRAME_START | 1B | 0xAA |
| [1] | mode | 1B | 0=SCAN, 1=MANUAL, 2=TRACK |
| [2] | btn | 1B | 수동 버튼 비트마스크 |
| [3~4] | pan | 2B | 팬 목표 위치 (Little-Endian, 0~4095) |
| [5~6] | tilt | 2B | 틸트 목표 위치 (Little-Endian, 0~4095) |
| [7] | scan_step | 1B | 스캔 스텝 (0=유지, 1~10) |
| [8] | manual_step | 1B | 수동 스텝 (0=유지, 1~10) |
| [9] | checksum | 1B | sum(frame[1..8]) & 0xFF |
| [10] | FRAME_END | 1B | 0x55 |

### TX 프레임 (OpenRB → Zybo, 40B)

| 인덱스 | 필드 | 크기 | 설명 |
|--------|------|------|------|
| [0] | FRAME_START | 1B | 0xAA |
| [1] | mode | 1B | 현재 모드 |
| [2~19] | PAN 데이터 | 18B | 아래 모터 데이터 구조 참고 |
| [20~37] | TILT 데이터 | 18B | 아래 모터 데이터 구조 참고 |
| [38] | checksum | 1B | sum(frame[1..37]) & 0xFF |
| [39] | FRAME_END | 1B | 0x55 |

**모터 데이터 18B 구조 (PAN/TILT 동일)**

| 오프셋 | 필드 | 크기 |
|--------|------|------|
| +0 | Moving | 1B |
| +1 | Moving Status | 1B |
| +2~3 | PWM | 2B |
| +4~5 | Current | 2B |
| +6~9 | Velocity | 4B |
| +10~13 | Position | 4B |
| +14~15 | Voltage | 2B |
| +16 | Temperature | 1B |
| +17 | Hardware Error | 1B |

---

## 수동 버튼 비트마스크 (btn 필드)

```
bit 0 (0x01) : 팬  + (우)
bit 1 (0x02) : 팬  - (좌)
bit 2 (0x04) : 틸트 + (업)
bit 3 (0x08) : 틸트 - (다운)
bit 4~7      : 예비
```

반대 방향 비트 동시 입력 시 delta 합산으로 상쇄되어 정지합니다.

---

## 모드별 동작

### MODE_SCAN (0) — 자동 스캔

- 팬을 `SCAN_MIN(0)` ~ `SCAN_MAX(4095)` 사이에서 왕복
- 틸트는 `TILT_CENTER(2047)` 고정
- `scan_step` 범위: 1~10 (RX로 실시간 변경 가능, 0이면 유지)

```
scan_pos += scan_step * scan_dir
if scan_pos >= 4095 → scan_dir = -1
if scan_pos <= 0    → scan_dir = +1
```

- **모션 제어 주기**: 20ms (`SCAN_INTERVAL`) — 20ms마다 `scan_pos`를 모터에 전달
- **피드백 주기**: 50ms (`SCAN_STATUS_INTERVAL`) — 50ms마다 모터 상태를 Zybo로 전송

### MODE_MANUAL (1) — 수동 버튼 제어

- RX 프레임의 `btn` 비트마스크로 팬/틸트 모두 제어
- 버튼 입력 없으면 `setGoalPosition` 호출 안 함 → 현재 위치 유지
- 모드 진입 시 현재 실제 모터 위치로 `manual_pan`/`manual_tilt` 초기화 (튐 방지)
- `manual_step` 범위: 1~10

```
pan_delta  = (+step if BTN_PAN_PLUS)  + (-step if BTN_PAN_MINUS)
tilt_delta = (+step if BTN_TILT_PLUS) + (-step if BTN_TILT_MINUS)
manual_pan  = clamp(manual_pan  + pan_delta,  0, 4095)
manual_tilt = clamp(manual_tilt + tilt_delta, 0, 4095)
```

- **모션 제어 주기**: 20ms (`MANUAL_INTERVAL`) — 20ms마다 버튼 상태 반영 후 모터에 전달
- **피드백 주기**: 20ms (`MANUAL_STATUS_INTERVAL`) — 20ms마다 모터 상태를 Zybo로 전송

### MODE_TRACK (2) — 트래킹 (PID 결과 직접 수신)

- RX 프레임의 `pan`/`tilt` 값을 스텝 없이 모터에 직접 전달
- 이전과 값이 같으면 `setGoalPosition` 호출 안 함 (불필요한 버스 트래픽 방지)

```
if (track_pan != last_pan || track_tilt != last_tilt):
    setGoalPosition(PAN,  track_pan)
    setGoalPosition(TILT, track_tilt)
```

- **모션 제어 주기**: 별도 주기 없음 — RX 패킷 수신 즉시 모터에 전달 (상위 PID 루프 주기에 종속)
- **피드백 주기**: 10ms (`TRACK_STATUS_INTERVAL`) — 상위 PID 루프가 현재 위치를 빠르게 받아야
  다음 제어 명령을 정확히 계산할 수 있으므로 가장 짧게 설정

---

## 모드 전환 로직

```
set_mode(new_mode):
    if current_mode == new_mode → return (no-op)

    torqueOff(PAN), torqueOff(TILT)
    프로파일 속도/가속도 재설정
    현재 실제 위치 읽어서 상태 초기화
    torqueOn(PAN), torqueOn(TILT)
```

**모드별 초기화 내용**

| 전환 대상 | 초기화 내용 |
|-----------|-------------|
| → SCAN | `scan_pos` = 현재 실제 팬 위치 (현재 위치에서 스캔 재개) |
| → MANUAL | `manual_pan/tilt` = 현재 실제 위치, `manual_btn` = 0 |
| → TRACK | `last_pan`, `last_tilt` = -1 (첫 수신 즉시 명령 전송 보장) |

---

## 프로파일 속도/가속도

| 모드 | PROFILE_VELOCITY | PROFILE_ACCELERATION |
|------|-----------------|----------------------|
| SCAN | 50 | 20 |
| MANUAL | 200 | 100 |
| TRACK | 300 | 150 |

---

## RX 수신 처리 흐름

```
loop():
    while Serial3.available():
        b = read()
        if b == 0xAA → rx_idx = 0     ← 프레임 시작 감지 & 버퍼 리셋
        rx_buf[rx_idx++] = b
        if rx_idx == 11 → frame_handle(rx_buf), rx_idx = 0

frame_handle():
    1. boundary check: frame[0]==0xAA, frame[10]==0x55
    2. checksum check: sum(frame[1..8]) == frame[9]
    3. 스텝 업데이트 (0이면 현재값 유지)
    4. 모드 분기 → set_mode() 호출
       MANUAL일 때: set_mode() 후 manual_btn 갱신
       (set_mode early return 시에도 btn은 항상 갱신됨)
```

---

## 주요 상수 요약

```c
POS_MIN  = 0       // 위치 최솟값
POS_MAX  = 4095    // 위치 최댓값
PAN_CENTER  = 2047
TILT_CENTER = 2047

STEP_MIN = 1
STEP_MAX = 10

// 모션 제어 주기 (모터에 명령을 보내는 주기)
SCAN_INTERVAL   = 20 ms   // SCAN:   20ms마다 scan_pos 전달
MANUAL_INTERVAL = 20 ms   // MANUAL: 20ms마다 버튼 반영 후 전달
                           // TRACK:  주기 없음, RX 수신 즉시 전달

// 피드백 주기 (모터 상태를 Zybo로 올려보내는 주기)
SCAN_STATUS_INTERVAL   = 50 ms   // 느리게 움직이므로 여유있게
MANUAL_STATUS_INTERVAL = 20 ms   // 버튼 응답감을 위해 중간
TRACK_STATUS_INTERVAL  = 10 ms   // 상위 PID 루프에 빠른 위치 피드백 필요
```

---

## Dynamixel 벌크 읽기

- 읽기 시작 주소: addr 122 (Moving)
- 읽기 길이: 25B (addr 122 ~ 146)
- `HARDWARE_ERROR_STATUS`는 별도 `readControlTableItem`으로 읽음
- 읽기는 `send_status()` 호출 시마다 수행 (모드별 주기 적용)
