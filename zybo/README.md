# Zybo Bridge

Thor(ROS2 노드)와 OpenRB(모터 펌웨어) 사이의 **프로토콜 변환 브릿지**입니다.  
UDP ↔ UART(Serial) 양방향 변환을 담당하며, Zybo 보드 위에서 단독 프로세스로 동작합니다.

---

## 역할

```
Thor ──UDP──→ Zybo Bridge ──UART──→ OpenRB  (명령)
Thor ←─UDP── Zybo Bridge ←─UART── OpenRB  (피드백)
```

Zybo 자체는 제어 로직이 없고, 패킷 포맷 변환과 라우팅만 수행합니다.

---

## 패킷 구조

### 명령 방향 (Thor → Zybo → OpenRB)

**UDP 수신 (Thor → Zybo, 8B)**

| 인덱스 | 필드 | 크기 | 설명 |
|--------|------|------|------|
| [0] | mode | 1B | 0=SCAN, 1=MANUAL, 2=TRACK |
| [1] | btn | 1B | 수동 버튼 비트마스크 |
| [2~3] | pan | 2B | 팬 목표 위치 (Little-Endian, 0~4095) |
| [4~5] | tilt | 2B | 틸트 목표 위치 (Little-Endian, 0~4095) |
| [6] | scan_step | 1B | 스캔 스텝 (0=유지, 1~10) |
| [7] | manual_step | 1B | 수동 스텝 (0=유지, 1~10) |

**UART 송신 (Zybo → OpenRB, 11B)**

| 인덱스 | 필드 | 크기 | 설명 |
|--------|------|------|------|
| [0] | FRAME_START | 1B | 0xAA |
| [1] | mode | 1B | 0=SCAN, 1=MANUAL, 2=TRACK |
| [2] | btn | 1B | 수동 버튼 비트마스크 |
| [3~4] | pan | 2B | 팬 목표 위치 (Little-Endian) |
| [5~6] | tilt | 2B | 틸트 목표 위치 (Little-Endian) |
| [7] | scan_step | 1B | 스캔 스텝 |
| [8] | manual_step | 1B | 수동 스텝 |
| [9] | checksum | 1B | sum(frame[1..8]) & 0xFF |
| [10] | FRAME_END | 1B | 0x55 |

변환 내용: UDP 8B 페이로드에 `0xAA` 헤더 / 체크섬 / `0x55` 테일 추가 → 11B UART 프레임

---

### 피드백 방향 (OpenRB → Zybo → Thor)

**UART 수신 (OpenRB → Zybo, 40B)**

| 인덱스 | 필드 | 크기 |
|--------|------|------|
| [0] | FRAME_START | 1B |
| [1] | mode | 1B |
| [2~19] | PAN 데이터 | 18B |
| [20~37] | TILT 데이터 | 18B |
| [38] | checksum | 1B |
| [39] | FRAME_END | 1B |

**UDP 송신 (Zybo → Thor, 36B)**

| 내용 | 크기 |
|------|------|
| PAN 데이터 | 18B |
| TILT 데이터 | 18B |

변환 내용: UART 40B에서 헤더/mode/체크섬/테일 제거 → `byte[2..37]` 36B만 UDP로 전달

---

## 프레임 동기화

**UART 수신 시** 첫 바이트가 `0xAA`일 때만 버퍼 수집을 시작합니다.  
수집 중인 40바이트가 채워지면 경계 검사 + 체크섬 검사를 수행하고, 실패 시 인덱스를 0으로 리셋하여 재동기화합니다.

```
parse_serial_byte(b):
    if ser_rx_idx == 0 and b != 0xAA → 무시 (동기화 대기)
    ser_rx_buf[ser_rx_idx++] = b
    if ser_rx_idx == 40 → handle_serial_frame(), ser_rx_idx = 0
```

---

## Jetson(Thor) IP 자동 감지

`--feedback-ip`를 지정하지 않으면, **첫 UDP 수신 시 송신자 IP를 피드백 목적지로 자동 등록**합니다.  
이후 동일 포트로 피드백을 전송합니다. `--feedback-ip`를 명시하면 고정 IP로 전송합니다.

```
UDP RX 수신 시:
    if feedback_ip_fixed_ == false:
        jetson_endpoint_ = remote_endpoint_.address() : feedback_port_
        has_jetson_ = true
```

피드백은 `has_jetson_`이 `true`일 때만 전송됩니다.

---

## 빌드 및 실행

**의존성**
- Boost.Asio (`libboost-dev`)
- C++17 이상

**빌드**
```bash
g++ -std=c++17 -O2 zybo_bridge.cpp -o zybo_bridge -lboost_system -lpthread
```

**Docker 빌드 및 실행 (Zybo 보드)**
```bash
# 빌드 + 실행
docker build -t zybo-bridge . && docker run --rm -it --network host --device /dev/ttyPS1 zybo-bridge

# 실행만
docker run --rm -it --network host --device /dev/ttyPS1 zybo-bridge
```

**실행 옵션**

| 옵션 | 기본값 | 설명 |
|------|--------|------|
| `--udp-port` | 6000 | Thor 명령 수신 포트 |
| `--feedback-port` | 6001 | Thor 피드백 송신 포트 |
| `--feedback-ip` | (자동) | Thor IP 고정 지정 시 사용 |
| `--serial` | /dev/ttyPS1 | OpenRB 연결 시리얼 포트 |
| `--baud` | 115200 | 시리얼 통신 속도 |

**실행 예시**
```bash
# IP 자동 감지 (권장)
./zybo_bridge --udp-port 6000 --feedback-port 6001 --serial /dev/ttyPS1

# Thor IP 고정 지정
./zybo_bridge --udp-port 6000 --feedback-ip 10.42.0.10 --feedback-port 6001 --serial /dev/ttyPS1
```
---

## 디버그 출력

모든 송수신 패킷을 stdout에 hex dump로 출력합니다.

```
[UDP RX] 8B from 10.42.0.10:5000 | AA 00 01 FF 07 FF 07 05 01
[UDP→SER] 1234567 ms | mode=0 btn=0x00 pan=2047 tilt=2047 scan_step=5 manual_step=1
[SER TX] 11B | AA 00 00 FF 07 FF 07 05 01 XX 55
[SER RX] 40B | AA 00 ...
[SER→UDP] mode=0 (36B, mode excluded)
[UDP TX] 36B | ...
```

종료는 `Ctrl+C` (SIGINT) 또는 SIGTERM으로 처리됩니다.

---

## 주요 상수

```cpp
FRAME_START    = 0xAA
FRAME_END      = 0x55
CMD_UDP_LEN    = 8    // Thor → Zybo UDP
CMD_SERIAL_LEN = 11   // Zybo → OpenRB UART
FB_SERIAL_LEN  = 40   // OpenRB → Zybo UART
FB_UDP_LEN     = 36   // Zybo → Thor UDP
```
