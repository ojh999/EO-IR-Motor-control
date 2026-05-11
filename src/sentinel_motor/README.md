# sentinel_motor

## pan_tilt_control_node

`pan_tilt_control_node`는 `/motor/angle/set`과 `/system/mode`를 받아 자이보로 UDP 명령을 전송합니다.

- `flag=0`: scan mode command
- `flag=1`: non-scan command
- TX packet: 5 bytes `[flag][pan LE16][tilt LE16]`
- RX packet: 12 bytes feedback from Zybo/gimbal

### ROS 2 interfaces

- Subscribe: `/motor/angle/set` (`sentinel_interfaces/msg/MotorAngle`)
- Subscribe: `/system/mode` (`std_msgs/msg/UInt8`)
- Publish: `/motor/angle/get` (`sentinel_interfaces/msg/MotorAngle`)
- Publish: `/motor/status` (`sentinel_interfaces/msg/MotorStatus`)

### Parameters

- `target_ip` default `10.42.0.168`
- `target_port` default `6000`
- `listen_port` default `6001`
- `feedback_poll_ms` default `50`
- `command_resend_ms` default `50`

### Run

```bash
cd ~/ros2_ws
colcon build --packages-select sentinel_motor
source install/setup.bash
ros2 launch sentinel_motor pan_tilt_control.launch.py
```

### Test command

```bash
ros2 topic pub /motor/angle/set sentinel_interfaces/msg/MotorAngle "{pan: 2048, tilt: 1024}" --once
```
