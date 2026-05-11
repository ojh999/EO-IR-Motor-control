#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from sentinel_interfaces.msg import Detection, FrameSize, MotorAngle
from std_msgs.msg import UInt8

class StaticStub(Node):
    def __init__(self):
        super().__init__('static_stub')

        self.declare_parameter('frame_w',    640)
        self.declare_parameter('frame_h',    480)
        self.declare_parameter('pub_hz',     10.0)
        # 객체가 있는 모터 각도 (목표 각도)
        self.declare_parameter('obj_pan',    196.0)
        self.declare_parameter('obj_tilt',   186.0)
        # 모터 1도당 픽셀 수 (FOV 시뮬레이션)
        self.declare_parameter('deg_to_px',  4.0)

        self.frame_w    = self.get_parameter('frame_w').value
        self.frame_h    = self.get_parameter('frame_h').value
        hz              = self.get_parameter('pub_hz').value
        self.obj_pan    = self.get_parameter('obj_pan').value
        self.obj_tilt   = self.get_parameter('obj_tilt').value
        self.deg_to_px  = self.get_parameter('deg_to_px').value

        # 모터 현재 위치
        self.current_pan  = 180
        self.current_tilt = 180

        self.pub_mode  = self.create_publisher(UInt8,      '/system/mode',          10)
        self.pub_det   = self.create_publisher(Detection,  '/driver/eo/detection',  10)
        self.pub_frame = self.create_publisher(FrameSize,  '/driver/eo/frame_size', 10)
        self.pub_angle = self.create_publisher(MotorAngle, '/motor/angle/get',      10)

        self.sub_cmd = self.create_subscription(
            MotorAngle, '/motor/angle/set',
            self.cmd_callback, 10
        )

        self.get_logger().info(
            f'StaticStub | frame=({self.frame_w},{self.frame_h}) '
            f'obj_pan={self.obj_pan} obj_tilt={self.obj_tilt}'
        )

        self.timer = self.create_timer(1.0 / hz, self.tick)

    def tick(self):
        # 모드
        mode = UInt8()
        mode.data = 1
        self.pub_mode.publish(mode)

        # 프레임 사이즈
        fs = FrameSize()
        fs.frame_w = self.frame_w
        fs.frame_h = self.frame_h
        self.pub_frame.publish(fs)

        # 모터 현재 위치
        angle = MotorAngle()
        angle.pan  = self.current_pan
        angle.tilt = self.current_tilt
        self.pub_angle.publish(angle)

        # ── 핵심: 모터가 움직이면 객체의 화면 위치도 바뀜 ──────
        # 모터와 객체 각도 차이 → 픽셀 오차
        cx = self.frame_w / 2.0 + (self.obj_pan  - self.current_pan)  * self.deg_to_px
        cy = self.frame_h / 2.0 + (self.obj_tilt - self.current_tilt) * self.deg_to_px

        det = Detection()
        det.cx = cx
        det.cy = cy
        self.pub_det.publish(det)

        self.get_logger().debug(
            f'motor=({self.current_pan},{self.current_tilt}) '
            f'obj_px=({cx:.1f},{cy:.1f}) '
            f'err=({cx - self.frame_w/2:.1f},{cy - self.frame_h/2:.1f})'
        )

    def cmd_callback(self, msg: MotorAngle):
        self.current_pan  = msg.pan
        self.current_tilt = msg.tilt
        self.get_logger().info(
            f'[CMD] pan={msg.pan:4d}  tilt={msg.tilt:4d}'
        )


def main():
    rclpy.init()
    rclpy.spin(StaticStub())
    rclpy.shutdown()

if __name__ == '__main__':
    main()