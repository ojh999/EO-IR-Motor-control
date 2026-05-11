#!/usr/bin/env python3
import math
import random
import rclpy
from rclpy.node import Node
from sentinel_interfaces.msg import Detection, FrameSize, MotorAngle
from std_msgs.msg import UInt8

class MovingStub(Node):
    def __init__(self):
        super().__init__('moving_stub')

        self.declare_parameter('frame_w',      640)
        self.declare_parameter('frame_h',      480)
        self.declare_parameter('pub_hz',       10.0)
        self.declare_parameter('scenario',     'circle')  # circle | sweep | random
        self.declare_parameter('speed',        1.0)       # 객체 이동 속도 배율
        self.declare_parameter('deg_to_px',    4.0)       # 모터 1도당 픽셀

        # 시나리오별 파라미터
        self.declare_parameter('center_pan',   180.0)     # 객체 중심 pan 각도
        self.declare_parameter('center_tilt',  180.0)     # 객체 중심 tilt 각도
        self.declare_parameter('radius_deg',   10.0)      # circle 반경 (도)
        self.declare_parameter('amplitude_deg', 15.0)     # sweep 진폭 (도)

        self.frame_w       = self.get_parameter('frame_w').value
        self.frame_h       = self.get_parameter('frame_h').value
        hz                 = self.get_parameter('pub_hz').value
        self.scenario      = self.get_parameter('scenario').value
        self.speed         = self.get_parameter('speed').value
        self.deg_to_px     = self.get_parameter('deg_to_px').value
        self.center_pan    = self.get_parameter('center_pan').value
        self.center_tilt   = self.get_parameter('center_tilt').value
        self.radius_deg    = self.get_parameter('radius_deg').value
        self.amplitude_deg = self.get_parameter('amplitude_deg').value

        # 모터 현재 위치 (cmd 피드백으로 업데이트)
        self.current_pan   = 180.0
        self.current_tilt  = 180.0

        # 시간/상태
        self.t   = 0.0
        self.dt  = 1.0 / hz

        # random 시나리오 상태
        self.obj_pan  = self.center_pan
        self.obj_tilt = self.center_tilt
        self.vx = random.uniform(1.0, 3.0)
        self.vy = random.uniform(1.0, 2.0)

        # 발행
        self.pub_mode  = self.create_publisher(UInt8,      '/system/mode',          10)
        self.pub_det   = self.create_publisher(Detection,  '/driver/eo/detection',  10)
        self.pub_frame = self.create_publisher(FrameSize,  '/driver/eo/frame_size', 10)
        self.pub_angle = self.create_publisher(MotorAngle, '/motor/angle/get',      10)

        # 구독
        self.sub_cmd = self.create_subscription(
            MotorAngle, '/motor/angle/set',
            self.cmd_callback, 10
        )

        self.get_logger().info(
            f'MovingStub | scenario={self.scenario} speed={self.speed} '
            f'hz={hz} deg_to_px={self.deg_to_px}'
        )

        self.timer = self.create_timer(self.dt, self.tick)

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
        angle.pan  = int(self.current_pan)
        angle.tilt = int(self.current_tilt)
        self.pub_angle.publish(angle)

        # 객체 위치 계산 (시나리오별)
        obj_pan, obj_tilt = self._get_obj_angle()

        # 모터와 객체 각도 차이 → 화면 픽셀 위치
        cx = self.frame_w / 2.0 + (obj_pan  - self.current_pan)  * self.deg_to_px
        cy = self.frame_h / 2.0 + (obj_tilt - self.current_tilt) * self.deg_to_px

        # 화면 밖으로 나가면 클램핑
        cx = max(0.0, min(float(self.frame_w), cx))
        cy = max(0.0, min(float(self.frame_h), cy))

        det = Detection()
        det.cx = cx
        det.cy = cy
        self.pub_det.publish(det)

        self.get_logger().info(
            f'[OBJ] pan={obj_pan:.1f} tilt={obj_tilt:.1f} | '
            f'motor=({self.current_pan:.1f},{self.current_tilt:.1f}) | '
            f'px=({cx:.1f},{cy:.1f}) | '
            f'err=({cx - self.frame_w/2:.1f},{cy - self.frame_h/2:.1f})'
        )

        self.t += self.dt * self.speed

    def _get_obj_angle(self):
        if self.scenario == 'circle':
            # 원형 궤도
            obj_pan  = self.center_pan  + self.radius_deg * math.cos(self.t)
            obj_tilt = self.center_tilt + self.radius_deg * math.sin(self.t)

        elif self.scenario == 'sweep':
            # 좌우 왕복
            obj_pan  = self.center_pan + self.amplitude_deg * math.sin(self.t)
            obj_tilt = self.center_tilt

        elif self.scenario == 'random':
            # 랜덤 이동 (벽에서 튕김)
            pan_min  = self.center_pan  - 20.0
            pan_max  = self.center_pan  + 20.0
            tilt_min = self.center_tilt - 15.0
            tilt_max = self.center_tilt + 15.0

            self.obj_pan  += self.vx * self.speed * self.dt
            self.obj_tilt += self.vy * self.speed * self.dt

            if self.obj_pan < pan_min or self.obj_pan > pan_max:
                self.vx *= -1
                self.vx += random.uniform(-0.3, 0.3)
                self.obj_pan = max(pan_min, min(pan_max, self.obj_pan))

            if self.obj_tilt < tilt_min or self.obj_tilt > tilt_max:
                self.vy *= -1
                self.vy += random.uniform(-0.3, 0.3)
                self.obj_tilt = max(tilt_min, min(tilt_max, self.obj_tilt))

            obj_pan  = self.obj_pan
            obj_tilt = self.obj_tilt

        else:
            obj_pan  = self.center_pan
            obj_tilt = self.center_tilt

        return obj_pan, obj_tilt

    def cmd_callback(self, msg: MotorAngle):
        # 트래킹 노드 명령을 현재 모터 위치로 업데이트
        self.current_pan  = float(msg.pan)
        self.current_tilt = float(msg.tilt)


def main():
    rclpy.init()
    rclpy.spin(MovingStub())
    rclpy.shutdown()

if __name__ == '__main__':
    main()