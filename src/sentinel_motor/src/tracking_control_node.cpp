#include <rclcpp/rclcpp.hpp>
#include <sentinel_interfaces/msg/frame_info.hpp>
#include <sentinel_interfaces/msg/motor_angle.hpp>
#include <sentinel_interfaces/msg/object_center.hpp>
#include <std_msgs/msg/u_int8.hpp>

#include <algorithm>

class TrackingControlNode : public rclcpp::Node
{
public:
    TrackingControlNode() : Node("tracking_control_node")
    {
        kp_pan_      = this->declare_parameter("kp_pan",      0.1);
        kp_tilt_     = this->declare_parameter("kp_tilt",     0.1);
        ki_pan_      = this->declare_parameter("ki_pan",      0.0);
        ki_tilt_     = this->declare_parameter("ki_tilt",     0.0);
        kd_pan_      = this->declare_parameter("kd_pan",      0.0);
        kd_tilt_     = this->declare_parameter("kd_tilt",     0.0);
        deadband_px_ = this->declare_parameter("deadband_px", 5);

        sub_mode_ = this->create_subscription<std_msgs::msg::UInt8>(
            "/system/mode", 10,
            std::bind(&TrackingControlNode::modeCallback, this, std::placeholders::_1)
        );

        sub_center_ = this->create_subscription<sentinel_interfaces::msg::ObjectCenter>(
            "/detection/object/center", 10,
            std::bind(&TrackingControlNode::centerCallback, this, std::placeholders::_1)
        );

        sub_frame_ = this->create_subscription<sentinel_interfaces::msg::FrameInfo>(
            "/video/frame_info", 10,
            std::bind(&TrackingControlNode::frameCallback, this, std::placeholders::_1)
        );

        sub_angle_ = this->create_subscription<sentinel_interfaces::msg::MotorAngle>(
            "/motor/angle/get", 10,
            std::bind(&TrackingControlNode::angleCallback, this, std::placeholders::_1)
        );

        pub_ = this->create_publisher<sentinel_interfaces::msg::MotorAngle>(
            "/motor/angle/set", 10
        );

        RCLCPP_INFO(this->get_logger(),
            "TrackingControlNode started | "
            "kp=(%.2f, %.2f) ki=(%.2f, %.2f) kd=(%.2f, %.2f) deadband=%dpx",
            kp_pan_, kp_tilt_, ki_pan_, ki_tilt_, kd_pan_, kd_tilt_, deadband_px_);
    }

private:
    void modeCallback(const std_msgs::msg::UInt8::SharedPtr msg)
    {
        // 모드 전환 시 적분 누적 초기화
        if (current_mode_ != msg->data) {
            integral_pan_  = 0.0;
            integral_tilt_ = 0.0;
            prev_error_x_  = 0.0;
            prev_error_y_  = 0.0;
        }
        current_mode_ = msg->data;
    }

    void angleCallback(const sentinel_interfaces::msg::MotorAngle::SharedPtr msg)
    {
        current_pan_ = msg->pan;
        current_tilt_ = msg->tilt;
    }

    void centerCallback(const sentinel_interfaces::msg::ObjectCenter::SharedPtr msg)
    {
        cx_ = msg->center_x;
        cy_ = msg->center_y;
        compute();
    }

    void frameCallback(const sentinel_interfaces::msg::FrameInfo::SharedPtr msg)
    {
        frame_w_ = msg->width;
        frame_h_ = msg->height;
    }

    void compute()
    {
        if (current_mode_ != TRACKING_MODE) return;
        if (frame_w_ == 0 || frame_h_ == 0) return;

        // ── 1. 픽셀 오차 계산 ──────────────────────────────────────
        double error_x = cx_ - (frame_w_ / 2.0);
        double error_y = cy_ - (frame_h_ / 2.0);

        // ── 2. Dead-band ───────────────────────────────────────────
        if (std::abs(error_x) < deadband_px_ && std::abs(error_y) < deadband_px_) {
            // deadband 진입 시 적분/미분 초기화
            integral_pan_  = 0.0;
            integral_tilt_ = 0.0;
            prev_error_x_  = 0.0;
            prev_error_y_  = 0.0;
            RCLCPP_DEBUG(this->get_logger(),
                "Within deadband (%.1f, %.1f) — no command", error_x, error_y);
            return;
        }

        // ── 3. 파라미터 최신값 읽기 ────────────────────────────────
        kp_pan_  = this->get_parameter("kp_pan").as_double();
        kp_tilt_ = this->get_parameter("kp_tilt").as_double();
        ki_pan_  = this->get_parameter("ki_pan").as_double();
        ki_tilt_ = this->get_parameter("ki_tilt").as_double();
        kd_pan_  = this->get_parameter("kd_pan").as_double();
        kd_tilt_ = this->get_parameter("kd_tilt").as_double();

        // ── 4. 적분 누적 (I) ───────────────────────────────────────
        integral_pan_  += error_x;
        integral_tilt_ += error_y;

        // ── 5. 미분 계산 (D) ───────────────────────────────────────
        double deriv_pan_  = error_x - prev_error_x_;
        double deriv_tilt_ = error_y - prev_error_y_;

        // ── 6. PID 출력 계산 ───────────────────────────────────────
        double delta_pan  = -(kp_pan_  * error_x  +
                              ki_pan_  * integral_pan_  +
                              kd_pan_  * deriv_pan_);
        double delta_tilt = -(kp_tilt_ * error_y  +
                              ki_tilt_ * integral_tilt_ +
                              kd_tilt_ * deriv_tilt_);

        // ── 7. 이전 오차 갱신 ──────────────────────────────────────
        prev_error_x_ = error_x;
        prev_error_y_ = error_y;

        // ── 8. 새 목표 각도 = 직전 명령값 + 보정량 ────────────────
        int cmd_pan  = static_cast<int>(current_pan_  + delta_pan);
        int cmd_tilt = static_cast<int>(current_tilt_ + delta_tilt);

        // ── 9. 하드웨어 한계 클램핑 ────────────────────────────────
        cmd_pan  = std::clamp(cmd_pan,  PAN_MIN,  PAN_MAX);
        cmd_tilt = std::clamp(cmd_tilt, TILT_MIN, TILT_MAX);

        // ── 10. 명령 발행 ──────────────────────────────────────────
        sentinel_interfaces::msg::MotorAngle cmd;
        cmd.pan  = static_cast<uint16_t>(cmd_pan);
        cmd.tilt = static_cast<uint16_t>(cmd_tilt);
        pub_->publish(cmd);

        // ── 11. 직전 명령값 갱신 ───────────────────────────────────
        current_pan_  = cmd_pan;
        current_tilt_ = cmd_tilt;

        RCLCPP_INFO(this->get_logger(),
            "mode=tracking | error=(%.1f, %.1f) | delta=(%.1f, %.1f) | cmd=(%d, %d)",
            error_x, error_y, delta_pan, delta_tilt, cmd_pan, cmd_tilt);
    }

    // 구독
    rclcpp::Subscription<std_msgs::msg::UInt8>::SharedPtr                   sub_mode_;
    rclcpp::Subscription<sentinel_interfaces::msg::MotorAngle>::SharedPtr   sub_angle_;
    rclcpp::Subscription<sentinel_interfaces::msg::ObjectCenter>::SharedPtr sub_center_;
    rclcpp::Subscription<sentinel_interfaces::msg::FrameInfo>::SharedPtr    sub_frame_;

    // 발행
    rclcpp::Publisher<sentinel_interfaces::msg::MotorAngle>::SharedPtr      pub_;

    // 상태값
    int    current_mode_ = 0;
    double current_pan_  = 180.0;
    double current_tilt_ = 180.0;
    double cx_ = 0.0, cy_ = 0.0;
    int    frame_w_ = 0, frame_h_ = 0;

    // PID 내부 상태
    double integral_pan_  = 0.0;
    double integral_tilt_ = 0.0;
    double prev_error_x_  = 0.0;
    double prev_error_y_  = 0.0;

    // 제어 파라미터
    double kp_pan_,  kp_tilt_;
    double ki_pan_,  ki_tilt_;
    double kd_pan_,  kd_tilt_;
    int    deadband_px_;

    const int TRACKING_MODE = 1;
    const int PAN_MIN  = 0,    PAN_MAX  = 360;
    const int TILT_MIN = 0,    TILT_MAX = 360;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TrackingControlNode>());
    rclcpp::shutdown();
    return 0;
}
