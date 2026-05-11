# gui_interface

`gui_interface` 패키지는 운용통제 GUI PC와 ROS 2 시스템 사이의 UDP 브릿지입니다.

- GUI CMD RX port: `3000`
- GUI TLM TX port: `5001`

## GUI -> ROS 2

- `0x01` Mode Change
  - mode values: `0=Scan`, `1=Tracking`, `2=Manual`
  - 내부 상태 `motor_mode`, `system_mode` 갱신
  - `/system/mode` publish
- `0x02` Button Command
  - `/control/button` publish
  - `Manual` 모드일 때 버튼 비트마스크를 현재 각도에 반영해 `/motor/angle/set` publish

## ROS 2 -> GUI

- `0x81` System Status
- `0x82` Motor Telemetry
- `0x83` Detection Result
- `0x84` Frame Info

## Run

```bash
cd ~/ros2_ws
colcon build --packages-select gui_interface
source install/setup.bash
ros2 launch gui_interface gui_interface.launch.py
```
