---

## 테스트 환경

| 항목 | 값 |
|------|----|
| 시나리오 | 원형 궤도 (circle) |
| 객체 속도 | speed=0.5 |
| 프레임 크기 | 640 x 480 px |
| Kp | 0.1 |
| Ki | 0.0 |
| Kd | 0.0 |
| Deadband | 5px |

---

## 결과 그래프

### 전체 추적 응답
![tracking_overview](docs/tracking_overview.png)

| 색상 | 토픽 | 설명 |
|------|------|------|
| 파란색 | `/driver/eo/detection.cx` | 객체 X 픽셀 위치 |
| 노란색 | `/driver/eo/detection.cy` | 객체 Y 픽셀 위치 |
| 주황색 | `/motor/angle/set.pan` | 모터 Pan 명령값 |
| 초록색 | `/motor/angle/set.tilt` | 모터 Tilt 명령값 |

→ 원형 궤도 객체를 모터가 정상 추적하는 것을 확인

---

### Pan 추적 상세
![tracking_peak_pan](docs/tracking_peak_pan.png)

→ detection.cx(파란색)와 motor.pan(주황색) 위상 차이 약 2~3초
→ Kp=0.1 기준 추적 지연, Kp 증가 시 개선 가능

---

### Tilt 추적 상세
![tracking_peak_tilt](docs/tracking_peak_tilt.png)

→ detection.cy(노란색)와 motor.tilt(초록색) 동일 패턴 확인

---

## 스텁 실행 방법

```bash
source /opt/ros/jazzy/setup.bash
source /root/ros2_ws/install/setup.bash

# 트래킹 노드
ros2 run sentinel_motor tracking_control_node

# 고정 객체 스텁
python3 src/stub/static_stub.py

# 이동 객체 스텁 (원형)
python3 src/stub/moving_stub.py --ros-args \
    -p scenario:=circle -p speed:=0.5

# 랜덤 이동 스텁
python3 src/stub/moving_stub.py --ros-args \
    -p scenario:=random -p speed:=1.0
```

---

## PID 런타임 튜닝

```bash
# Kp 조정 (수렴 속도)
ros2 param set /tracking_control_node kp_pan 0.3
ros2 param set /tracking_control_node kp_tilt 0.3

# Kd 추가 (진동 억제)
ros2 param set /tracking_control_node kd_pan 0.05
ros2 param set /tracking_control_node kd_tilt 0.05

# Ki 추가 (정상 상태 오차 제거)
ros2 param set /tracking_control_node ki_pan 0.01
ros2 param set /tracking_control_node ki_tilt 0.01
```

---

## 비고

- 실제 하드웨어 환경에서 PID 재튜닝 필요
- 모터 관성, 카메라 FOV, detection 딜레이에 따라 파라미터 달라짐
- rosbag 녹화 후 Foxglove Studio로 분석 가능
