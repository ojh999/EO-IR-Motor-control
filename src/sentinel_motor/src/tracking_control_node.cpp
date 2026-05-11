#include <rclcpp/rclcpp.hpp>
#include <sentinel_interfaces/msg/detection.hpp>
#include <sentinel_interfaces/msg/frame_size.hpp>
#include <sentinel_interfaces/msg/motor_angle.hpp>
#include <std_msgs/msg/u_int8.hpp>

#include <algorithm>
#include <cmath>

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

        sub_detection_ = this->create_subscription<sentinel_interfaces::msg::Detection>(
            "/driver/eo/detection", 10,
            std::bind(&TrackingControlNode::detectionCallback, this, std::placeholders::_1)
        );

        sub_frame_size_ = this->create_subscription<sentinel_interfaces::msg::FrameSize>(
            "/driver/eo/frame_size", 10,
            std::bind(&TrackingControlNode::frameSizeCallback, this, std::placeholders::_1)
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
        if (current_mode_ != msg->data) {
            resetPidState();
            RCLCPP_INFO(this->get_logger(),
                "Mode changed: %d → %d | PID state reset", current_mode_, msg->data);
        }
        current_mode_ = msg->data;
    }

    void angleCallback(const sentinel_interfaces::msg::MotorAngle::SharedPtr msg)
    {
        // 최초 한 번만 초기값 설정 (이후엔 내부 double 누적값 사용)
        if (!angle_initialized_) {
            current_pan_  = msg->pan;
            current_tilt_ = msg->tilt;
            angle_initialized_ = true;
        }
    }

    void frameSizeCallback(const sentinel_interfaces::msg::FrameSize::SharedPtr msg)
    {
        frame_w_ = msg->frame_w;
        frame_h_ = msg->frame_h;
    }

    void detectionCallback(const sentinel_interfaces::msg::Detection::SharedPtr msg)
    {
        cx_ = msg->cx;
        cy_ = msg->cy;
        compute();
    }

    void compute()
    {
        if (current_mode_ != TRACKING_MODE) return;
        if (frame_w_ == 0 || frame_h_ == 0) return;
        if (!angle_initialized_) return;

        // ── 1. 픽셀 오차 ───────────────────────────────────────
        const double error_x = cx_ - (frame_w_ / 2.0);
        const double error_y = cy_ - (frame_h_ / 2.0);

        // ── 2. Dead-band ────────────────────────────────────────
        if (std::abs(error_x) < deadband_px_ && std::abs(error_y) < deadband_px_) {
            resetPidState();
            RCLCPP_DEBUG(this->get_logger(),
                "Within deadband (%.1f, %.1f) — no command", error_x, error_y);
            return;
        }

        // ── 3. 파라미터 최신값 읽기 ────────────────────────────
        kp_pan_  = this->get_parameter("kp_pan").as_double();
        kp_tilt_ = this->get_parameter("kp_tilt").as_double();
        ki_pan_  = this->get_parameter("ki_pan").as_double();
        ki_tilt_ = this->get_parameter("ki_tilt").as_double();
        kd_pan_  = this->get_parameter("kd_pan").as_double();
        kd_tilt_ = this->get_parameter("kd_tilt").as_double();

        // ── 4. 적분 누적 (I) ────────────────────────────────────
        integral_pan_  += error_x;
        integral_tilt_ += error_y;

        // ── 5. 미분 계산 (D) ────────────────────────────────────
        const double deriv_pan_  = error_x - prev_error_x_;
        const double deriv_tilt_ = error_y - prev_error_y_;

        // ── 6. PID 출력 ─────────────────────────────────────────
        const double delta_pan  = kp_pan_  * error_x + ki_pan_  * integral_pan_  + kd_pan_  * deriv_pan_;
        const double delta_tilt = kp_tilt_ * error_y + ki_tilt_ * integral_tilt_ + kd_tilt_ * deriv_tilt_;

        // ── 7. 이전 오차 갱신 ───────────────────────────────────
        prev_error_x_ = error_x;
        prev_error_y_ = error_y;

        // ── 8. double로 누적 (정수 잘림 방지) ──────────────────
        current_pan_  += delta_pan;
        current_tilt_ += delta_tilt;

        // ── 9. 하드웨어 한계 클램핑 ────────────────────────────
        current_pan_  = std::clamp(current_pan_,  (double)PAN_MIN,  (double)PAN_MAX);
        current_tilt_ = std::clamp(current_tilt_, (double)TILT_MIN, (double)TILT_MAX);

        // ── 10. 명령 발행 (int 변환은 발행할 때만) ─────────────
        sentinel_interfaces::msg::MotorAngle cmd;
        cmd.pan  = static_cast<uint16_t>(current_pan_);
        cmd.tilt = static_cast<uint16_t>(current_tilt_);
        pub_->publish(cmd);

        RCLCPP_INFO(this->get_logger(),
            "[TRACKING] error=(%.1f, %.1f) | delta=(%.2f, %.2f) | cmd=(%d, %d)",
            error_x, error_y, delta_pan, delta_tilt,
            cmd.pan, cmd.tilt);
    }

    void resetPidState()
    {
        integral_pan_  = 0.0;
        integral_tilt_ = 0.0;
        prev_error_x_  = 0.0;
        prev_error_y_  = 0.0;
    }

    rclcpp::Subscription<std_msgs::msg::UInt8>::SharedPtr                   sub_mode_;
    rclcpp::Subscription<sentinel_interfaces::msg::Detection>::SharedPtr    sub_detection_;
    rclcpp::Subscription<sentinel_interfaces::msg::FrameSize>::SharedPtr    sub_frame_size_;
    rclcpp::Subscription<sentinel_interfaces::msg::MotorAngle>::SharedPtr   sub_angle_;
    rclcpp::Publisher<sentinel_interfaces::msg::MotorAngle>::SharedPtr      pub_;

    int    current_mode_       = 0;
    bool   angle_initialized_  = false;  // 최초 모터 위치 수신 여부
    double current_pan_        = 180.0;
    double current_tilt_       = 180.0;
    double cx_ = 0.0, cy_      = 0.0;
    int    frame_w_ = 0, frame_h_ = 0;

    double integral_pan_  = 0.0;
    double integral_tilt_ = 0.0;
    double prev_error_x_  = 0.0;
    double prev_error_y_  = 0.0;

    double kp_pan_,  kp_tilt_;
    double ki_pan_,  ki_tilt_;
    double kd_pan_,  kd_tilt_;
    int    deadband_px_;

    const int TRACKING_MODE = 1;
    const int PAN_MIN  = 0,   PAN_MAX  = 360;
    const int TILT_MIN = 0,   TILT_MAX = 360;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TrackingControlNode>());
    rclcpp::shutdown();
    return 0;
}