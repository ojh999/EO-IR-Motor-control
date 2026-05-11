# sentinel_motor

## pan_tilt_control_node

`pan_tilt_control_node`는 GUI에서 오는 모드/버튼/스텝 명령을 수신하고 Zybo로 UDP 명령을 전송합니다.  
피드백은 Zybo로부터 36B UDP로 수신하여 ROS2 토픽으로 퍼블리시합니다.

---

## 패킷 구조

### TX (Thor → Zybo, 8B UDP)

| 인덱스 | 필드 | 크기 | 설명 |
|--------|------|------|------|
| [0] | mode_cmd | 1B | 0=SCAN, 1=MANUAL, 2=TRACK |
| [1] | btn | 1B | 버튼 비트마스크 (MANUAL 모드) |
| [2~3] | pan | 2B | 팬 목표 위치 (Little-Endian, 0~4095) |
| [4~5] | tilt | 2B | 틸트 목표 위치 (Little-Endian, 0~4095) |
| [6] | scan_step | 1B | 스캔 스텝 (1~10) |
| [7] | manual_step | 1B | 수동 스텝 (1~10) |

**모드별 유효 필드**

| mode_cmd | btn | pan/tilt | 설명 |
|----------|-----|----------|------|
| 0 (SCAN) | 0 | 0 | scan_step으로 팬 자동 왕복 |
| 1 (MANUAL) | 비트마스크 | 0 | 버튼으로 수동 조작 |
| 2 (TRACK) | 0 | step값 | PID 결과 직접 전달 |

### RX (Zybo → Thor, 36B UDP)

| 인덱스 | 필드 | 크기 |
|--------|------|------|
| [0~17] | PAN 모터 데이터 | 18B |
| [18~35] | TILT 모터 데이터 | 18B |

---

## 모드 결정

GUI에서 `auto_manual`(0/1) + `tracking`(0/1) 두 값을 조합해 `gui_interface` 노드가 `mode_cmd`(0/1/2)로 변환 후 `/system/mode` 토픽으로 퍼블리시합니다.

| auto_manual | tracking | mode_cmd | 동작 |
|-------------|----------|----------|------|
| 0 (scan) | 0 (비추적) | 0 (SCAN) | 팬 자동 왕복 |
| 1 (manual) | 0 (비추적) | 1 (MANUAL) | 버튼 수동 조작 |
| 1 (manual) | 1 (추적) | 2 (TRACK) | PID 추적 제어 |

---

## ROS2 인터페이스

### 구독

| 토픽 | 타입 | 설명 |
|------|------|------|
| `/motor/angle/set` | `sentinel_interfaces/msg/MotorAngle` | TRACK 모드 PID 결과 각도 |
| `/system/mode` | `std_msgs/msg/UInt8` | mode_cmd (0/1/2) |
| `/motor/scan_step` | `std_msgs/msg/UInt16` | 스캔 스텝 (1~10) |
| `/motor/manual_step` | `std_msgs/msg/UInt16` | 수동 스텝 (1~10) |
| `/motor/manual_btn` | `std_msgs/msg/UInt8` | 버튼 비트마스크 |

### 퍼블리시

| 토픽 | 타입 | 설명 |
|------|------|------|
| `/motor/angle/get` | `sentinel_interfaces/msg/MotorAngle` | 현재 모터 각도 |
| `/motor/status` | `sentinel_interfaces/msg/MotorStatus` | 모터 상태 (전류/온도/에러) |
| `/motor/feedback/raw` | `std_msgs/msg/UInt8MultiArray` | 36B 피드백 raw 데이터 |

---

## 파라미터

| 파라미터 | 기본값 | 설명 |
|----------|--------|------|
| `target_ip` | 10.42.0.168 | Zybo IP |
| `target_port` | 6000 | Thor → Zybo 명령 포트 |
| `listen_port` | 6001 | Zybo → Thor 피드백 포트 |
| `feedback_poll_ms` | 50 | 피드백 수신 주기 (ms) |
| `command_resend_ms` | 50 | 명령 재전송 주기 (ms) |

---

## 빌드 및 실행

```bash
cd ~/ros2_ws
colcon build --packages-select sentinel_motor
source install/setup.bash
ros2 launch sentinel_motor pan_tilt_control.launch.py
```

---

## 테스트 명령어

```bash
# TRACK 모드 각도 명령
ros2 topic pub /motor/angle/set sentinel_interfaces/msg/MotorAngle "{pan: 2048, tilt: 1024}" --once

# 모드 변경 (0=SCAN, 1=MANUAL, 2=TRACK)
ros2 topic pub /system/mode std_msgs/msg/UInt8 "{data: 1}" --once

# 수동 버튼 (0x02=팬우, 0x01=팬좌, 0x04=틸트업, 0x08=틸트다운)
ros2 topic pub /motor/manual_btn std_msgs/msg/UInt8 "{data: 2}" --once

# 스캔 스텝 변경
ros2 topic pub /motor/scan_step std_msgs/msg/UInt16 "{data: 5}" --once
```