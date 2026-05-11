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

| 모드 | 값 | 동작 |
|------|----|------|
| **SCAN** | 0 | scan_step 속도로 팬 자동 왕복, 틸트 고정 |
| **MANUAL** | 1 | 버튼 비트마스크로 팬/틸트 수동 조작 |
| **TRACK** | 2 | PID 제어 결과를 모터에 직접 전달 |

---

## 패킷 구조

### 명령 (GUI → Thor → Zybo → OpenRB)

| 구간 | 크기 | 주요 필드 |
|------|------|-----------|
| GUI → Thor | 9B (UDP) | mode(1) + tracking(1) + btn(1) + pan(2) + tilt(2) + scan_step(1) + manual_step(1) |
| Thor → Zybo | 8B (UDP) | mode(1) + btn(1) + pan(2) + tilt(2) + scan_step(1) + manual_step(1) |
| Zybo → OpenRB | 11B (UART) | AA + mode + btn + pan(2) + tilt(2) + scan_step + manual_step + CHK + 55 |

### 피드백 (OpenRB → Zybo → Thor → GUI)

| 구간 | 크기 | 주요 필드 |
|------|------|-----------|
| OpenRB → Zybo | 40B (UART) | AA + mode + PAN(18B) + TILT(18B) + CHK + 55 |
| Zybo → Thor | 36B (UDP) | PAN(18B) + TILT(18B) |
| Thor → GUI | 36B (UDP) | PAN(18B) + TILT(18B) |

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
├── zybo_bridge.cpp              # Zybo: UDP ↔ UART 브릿지
├── openrb_firmware.ino          # OpenRB: 모터 펌웨어 (Arduino)
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

---

## 통신 설정

| 항목 | 값 |
|------|----|
| Thor ↔ Zybo UDP 포트 (명령) | 6000 |
| Thor ↔ Zybo UDP 포트 (피드백) | 6001 |
| Zybo ↔ OpenRB UART 속도 | 115200 bps |
| OpenRB ↔ Dynamixel 속도 | 1,000,000 bps |
| Dynamixel 프로토콜 | 2.0 |

---

## 브랜치 구조

```
main
├── feature/openrb-firmware   # OpenRB 모터 펌웨어
└── featur/zybo               # Zybo 브릿지
```

---

## 개발 환경

- ROS2 Humble
- Ubuntu 22.04
- Boost.Asio (Zybo Bridge)
- Arduino IDE / Dynamixel2Arduino (OpenRB)# EO-IR-Motor-control
