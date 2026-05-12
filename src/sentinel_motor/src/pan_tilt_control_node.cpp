#include "sentinel_motor/PacketDef.hpp"
#include "sentinel_motor/UdpTransport.hpp"

#include <rclcpp/rclcpp.hpp>
#include <sentinel_interfaces/msg/motor_angle.hpp>
#include <sentinel_interfaces/msg/motor_status.hpp>
#include <std_msgs/msg/u_int8.hpp>
#include <std_msgs/msg/u_int16.hpp>
#include <std_msgs/msg/u_int8_multi_array.hpp>

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <functional>
#include <string>
#include <vector>

using namespace std::chrono_literals;

// ── 모드 상수 (OpenRB 펌웨어 / Zybo Bridge와 동일) ──
static constexpr uint8_t MODE_SCAN   = 0;
static constexpr uint8_t MODE_MANUAL = 1;
static constexpr uint8_t MODE_TRACK  = 2;

class PanTiltControlNode : public rclcpp::Node
{
public:
  PanTiltControlNode()
  : Node("pan_tilt_control_node")
  {
    target_ip_         = this->declare_parameter<std::string>("target_ip", "10.42.0.168");
    target_port_       = this->declare_parameter<int>("target_port", 6000);
    listen_port_       = this->declare_parameter<int>("listen_port", 6001);
    feedback_poll_ms_  = this->declare_parameter<int>("feedback_poll_ms", 50);
    command_resend_ms_ = this->declare_parameter<int>("command_resend_ms", 50);

    angle_set_topic_    = this->declare_parameter<std::string>("angle_set_topic",    "/motor/angle/set");
    angle_get_topic_    = this->declare_parameter<std::string>("angle_get_topic",    "/motor/angle/get");
    status_topic_       = this->declare_parameter<std::string>("status_topic",       "/motor/status");
    // BUG FIX: system_mode_topic은 GUI의 auto_manual+tracking 조합 결과(0/1/2)를 받음
    system_mode_topic_  = this->declare_parameter<std::string>("system_mode_topic",  "/system/mode");
    scan_step_topic_    = this->declare_parameter<std::string>("scan_step_topic",    "/motor/scan_step");
    manual_step_topic_  = this->declare_parameter<std::string>("manual_step_topic",  "/motor/manual_step");
    // BUG FIX: manual_btn 구독 추가
    manual_btn_topic_   = this->declare_parameter<std::string>("manual_btn_topic",   "/motor/manual_btn");
    raw_feedback_topic_ = this->declare_parameter<std::string>("raw_feedback_topic", "/motor/feedback/raw");

    home_pan_  = this->declare_parameter<int>("home_pan",  180);
    home_tilt_ = this->declare_parameter<int>("home_tilt", 180);
    pan_min_   = this->declare_parameter<int>("pan_min",   0);
    pan_max_   = this->declare_parameter<int>("pan_max",   360);
    tilt_min_  = this->declare_parameter<int>("tilt_min",  0);
    tilt_max_  = this->declare_parameter<int>("tilt_max",  360);

    current_angle_.pan  = static_cast<uint16_t>(home_pan_);
    current_angle_.tilt = static_cast<uint16_t>(home_tilt_);
    last_command_ = current_angle_;

    last_cmd_pan_step_  = angle_to_step(home_pan_,  pan_err_acc_);
    last_cmd_tilt_step_ = angle_to_step(home_tilt_, tilt_err_acc_);
    has_command_ = true;

    transport_ = std::make_unique<sentinel_motor::UdpTransport>(
      target_ip_,
      static_cast<uint16_t>(target_port_),
      static_cast<uint16_t>(listen_port_));
    transport_->open();

    // ── 구독 ──
    // TRACK 모드 전용: PID 결과 각도 수신
    command_sub_ = this->create_subscription<sentinel_interfaces::msg::MotorAngle>(
      angle_set_topic_, rclcpp::QoS(10),
      std::bind(&PanTiltControlNode::commandCallback, this, std::placeholders::_1));

    // GUI auto_manual + tracking 조합 결과 mode_cmd(0/1/2) 수신
    system_mode_sub_ = this->create_subscription<std_msgs::msg::UInt8>(
      system_mode_topic_, rclcpp::QoS(10),
      std::bind(&PanTiltControlNode::systemModeCallback, this, std::placeholders::_1));

    scan_step_sub_ = this->create_subscription<std_msgs::msg::UInt16>(
      scan_step_topic_, rclcpp::QoS(10),
      std::bind(&PanTiltControlNode::scanStepCallback, this, std::placeholders::_1));

    manual_step_sub_ = this->create_subscription<std_msgs::msg::UInt16>(
      manual_step_topic_, rclcpp::QoS(10),
      std::bind(&PanTiltControlNode::manualStepCallback, this, std::placeholders::_1));

    // BUG FIX: manual_btn 구독 추가
    manual_btn_sub_ = this->create_subscription<std_msgs::msg::UInt8>(
      manual_btn_topic_, rclcpp::QoS(10),
      std::bind(&PanTiltControlNode::manualBtnCallback, this, std::placeholders::_1));

    // ── 퍼블리셔 ──
    angle_pub_        = this->create_publisher<sentinel_interfaces::msg::MotorAngle>(
      angle_get_topic_, rclcpp::QoS(10));
    status_pub_       = this->create_publisher<sentinel_interfaces::msg::MotorStatus>(
      status_topic_, rclcpp::QoS(10));
    raw_feedback_pub_ = this->create_publisher<std_msgs::msg::UInt8MultiArray>(
      raw_feedback_topic_, rclcpp::QoS(10));

    // ── 타이머 ──
    feedback_timer_ = this->create_wall_timer(
      std::chrono::milliseconds(feedback_poll_ms_),
      std::bind(&PanTiltControlNode::pollFeedback, this));
    command_resend_timer_ = this->create_wall_timer(
      std::chrono::milliseconds(command_resend_ms_),
      std::bind(&PanTiltControlNode::resendCommand, this));

    RCLCPP_INFO(
      this->get_logger(),
      "pan_tilt_control_node ready | target=%s:%d listen=%d set=%s get=%s status=%s",
      target_ip_.c_str(), target_port_, listen_port_,
      angle_set_topic_.c_str(), angle_get_topic_.c_str(), status_topic_.c_str());
  }

private:
  // ── 브레즌험 오차 보상: 도(degree) → 모터 step (0~4095) ──
  uint16_t angle_to_step(double deg, double & acc)
  {
    double raw   = deg / 360.0 * 4096.0;
    int    steps = static_cast<int>(std::round(raw + acc));
    acc += raw - static_cast<double>(steps);
    steps = std::clamp(steps, 0, 4095);
    return static_cast<uint16_t>(steps);
  }

  // ── TRACK 모드 전용: PID 결과 각도 수신 ──
  void commandCallback(const sentinel_interfaces::msg::MotorAngle::SharedPtr msg)
  {
    // TRACK 모드가 아닐 때는 무시
    if (current_mode_ != MODE_TRACK) {
      RCLCPP_WARN(this->get_logger(),
        "CMD RX ignored (mode=%u, expected TRACK=%u)", current_mode_, MODE_TRACK);
      return;
    }

    RCLCPP_INFO(this->get_logger(), "CMD RX | pan=%u° tilt=%u°", msg->pan, msg->tilt);
    last_command_.pan  = msg->pan;
    last_command_.tilt = msg->tilt;
    current_angle_     = last_command_;

    last_cmd_pan_step_  = angle_to_step(msg->pan,  pan_err_acc_);
    last_cmd_tilt_step_ = angle_to_step(msg->tilt, tilt_err_acc_);
    has_command_ = true;
    sendCommand();
  }

  // ── 피드백 수신 ──
  void pollFeedback()
  {
    std::array<uint8_t, sentinel_motor::kFeedbackPacketSize> raw_feedback{};
    std::array<uint8_t, sentinel_motor::kFeedbackPacketSize> latest_feedback{};
    bool got_any = false;

    try {
      while (transport_->receive_feedback(raw_feedback)) {
        latest_feedback = raw_feedback;
        got_any = true;
      }
    } catch (const std::exception & ex) {
      RCLCPP_WARN(this->get_logger(), "Bad feedback packet: %s", ex.what());
      return;
    }

    if (!got_any) return;

    std_msgs::msg::UInt8MultiArray raw_msg;
    raw_msg.data.assign(latest_feedback.begin(), latest_feedback.end());
    raw_feedback_pub_->publish(raw_msg);

    const auto fb = sentinel_motor::parse_feedback(latest_feedback);

    const auto step_to_deg = [](uint32_t pos) -> uint16_t {
      return static_cast<uint16_t>(std::round(static_cast<double>(pos) * 360.0 / 4095.0));
    };
    uint16_t pan_deg  = step_to_deg(fb.pan.position);
    uint16_t tilt_deg = step_to_deg(fb.tilt.position);

    current_angle_.pan  = pan_deg;
    current_angle_.tilt = tilt_deg;

    sentinel_interfaces::msg::MotorAngle angle_msg;
    angle_msg.pan  = pan_deg;
    angle_msg.tilt = tilt_deg;
    angle_pub_->publish(angle_msg);

    sentinel_interfaces::msg::MotorStatus status_msg;
    status_msg.pan.position    = static_cast<uint16_t>(fb.pan.position);
    status_msg.pan.load        = fb.pan.current;
    status_msg.pan.temperature = fb.pan.temperature;
    status_msg.pan.hw_error    = fb.pan.hw_error;
    status_msg.tilt.position    = static_cast<uint16_t>(fb.tilt.position);
    status_msg.tilt.load        = fb.tilt.current;
    status_msg.tilt.temperature = fb.tilt.temperature;
    status_msg.tilt.hw_error    = fb.tilt.hw_error;
    status_pub_->publish(status_msg);

    RCLCPP_INFO_THROTTLE(
      this->get_logger(), *this->get_clock(), 1000,
      "FB pan=%u(%.1f°) tilt=%u(%.1f°)",
      fb.pan.position,  static_cast<double>(pan_deg),
      fb.tilt.position, static_cast<double>(tilt_deg));
  }

  // ── 주기적 재전송 ──
  void resendCommand()
  {
    if (!has_command_) return;
    RCLCPP_INFO_THROTTLE(
      this->get_logger(), *this->get_clock(), 2000,
      "RESEND | mode=%u btn=0x%02X pan_step=%u tilt_step=%u",
      current_mode_, manual_btn_, last_cmd_pan_step_, last_cmd_tilt_step_);
    sendCommand(false);
  }

  // ── 스텝 콜백 ──
  void scanStepCallback(const std_msgs::msg::UInt16::SharedPtr msg)
  {
    // BUG FIX: 1~10 범위 clamp
    scan_step_ = static_cast<uint8_t>(std::clamp<int>(msg->data, 1, 10));
    RCLCPP_INFO(this->get_logger(), "SCAN step: %u", scan_step_);
  }

  void manualStepCallback(const std_msgs::msg::UInt16::SharedPtr msg)
  {
    // BUG FIX: 1~10 범위 clamp
    manual_step_ = static_cast<uint8_t>(std::clamp<int>(msg->data, 1, 10));
    RCLCPP_INFO(this->get_logger(), "MANUAL step: %u", manual_step_);
  }

  // BUG FIX: manual_btn 콜백 추가
  void manualBtnCallback(const std_msgs::msg::UInt8::SharedPtr msg)
  {
    manual_btn_ = msg->data;
    if (current_mode_ == MODE_MANUAL) {
      sendCommand();
    }
  }

  // ── 모드 전환 ──
  // GUI: auto_manual(0/1) + tracking(0/1) → gui_interface 노드가 조합 후 mode_cmd(0/1/2) 발행
  void systemModeCallback(const std_msgs::msg::UInt8::SharedPtr msg)
  {
    // BUG FIX: 유효하지 않은 모드 무시
    if (msg->data > MODE_TRACK) {
      RCLCPP_WARN(this->get_logger(), "Unknown mode: %u, ignored", msg->data);
      return;
    }

    if (current_mode_ != msg->data) {
      pan_err_acc_  = 0.0;
      tilt_err_acc_ = 0.0;
      manual_btn_   = 0;   // BUG FIX: 모드 전환 시 버튼 초기화

      last_command_       = getReferenceAngle();
      last_cmd_pan_step_  = angle_to_step(last_command_.pan,  pan_err_acc_);
      last_cmd_tilt_step_ = angle_to_step(last_command_.tilt, tilt_err_acc_);
      has_command_ = true;

      RCLCPP_INFO(
        this->get_logger(),
        "Mode changed %u → %u | hold=(%u°,%u°) step=(%u,%u)",
        current_mode_, msg->data,
        last_command_.pan, last_command_.tilt,
        last_cmd_pan_step_, last_cmd_tilt_step_);
    }
    current_mode_ = msg->data;
  }

  sentinel_interfaces::msg::MotorAngle getReferenceAngle() const
  {
    sentinel_interfaces::msg::MotorAngle reference = current_angle_;

    if (reference.pan  < pan_min_  || reference.pan  > pan_max_)  reference.pan  = last_command_.pan;
    if (reference.tilt < tilt_min_ || reference.tilt > tilt_max_) reference.tilt = last_command_.tilt;

    reference.pan  = static_cast<uint16_t>(std::clamp<int>(reference.pan,  pan_min_,  pan_max_));
    reference.tilt = static_cast<uint16_t>(std::clamp<int>(reference.tilt, tilt_min_, tilt_max_));
    return reference;
  }

  // BUG FIX: sendStepCommand → sendCommand 재설계
  // 모드별로 의미있는 필드만 채워서 전송
  //
  // SCAN   : mode=0, btn=0,          pan=0,             tilt=0,          scan_step, manual_step
  // MANUAL : mode=1, btn=manual_btn, pan=0,             tilt=0,          scan_step, manual_step
  // TRACK  : mode=2, btn=0,          pan=pan_step,      tilt=tilt_step,  scan_step, manual_step
  void sendCommand(bool log_on_send = true)
  {
    sentinel_motor::CommandPacket command{};
    // BUG FIX: 모드 직접 대입 (기존 (mode==0)?0:1 은 TRACK(2)→MANUAL(1) 잘못 매핑)
    command.mode      = current_mode_;
    command.scan_step = scan_step_;
    command.man_step  = manual_step_;

    switch (current_mode_) {
      case MODE_SCAN:
        command.btn  = 0;
        command.pan  = 0;
        command.tilt = 0;
        break;

      case MODE_MANUAL:
        // BUG FIX: 버튼 비트마스크 전송
        command.btn  = manual_btn_;
        command.pan  = 0;
        command.tilt = 0;
        break;

      case MODE_TRACK:
        command.btn  = 0;
        // Bresenham 변환된 step 값 전송
        command.pan  = last_cmd_pan_step_;
        command.tilt = last_cmd_tilt_step_;
        break;

      default:
        return;
    }

    try {
      transport_->send_command(command);
      if (log_on_send) {
        RCLCPP_INFO(
          this->get_logger(),
          "UDP TX | mode=%u btn=0x%02X pan=%u tilt=%u scan_step=%u man_step=%u",
          command.mode, command.btn, command.pan, command.tilt,
          command.scan_step, command.man_step);
      }
    } catch (const std::exception & ex) {
      RCLCPP_ERROR(this->get_logger(), "Failed to send UDP command: %s", ex.what());
    }
  }

  // ── 파라미터 ──
  std::string target_ip_;
  int target_port_;
  int listen_port_;
  int feedback_poll_ms_;
  int command_resend_ms_;
  std::string angle_set_topic_;
  std::string angle_get_topic_;
  std::string status_topic_;
  std::string raw_feedback_topic_;
  std::string system_mode_topic_;
  std::string scan_step_topic_;
  std::string manual_step_topic_;
  std::string manual_btn_topic_;   // BUG FIX: 추가
  int home_pan_;
  int home_tilt_;
  int pan_min_;
  int pan_max_;
  int tilt_min_;
  int tilt_max_;

  // ── 상태 ──
  uint8_t  current_mode_{MODE_SCAN};
  bool     has_command_{false};
  uint8_t  manual_btn_{0};         // BUG FIX: 추가
  uint8_t  scan_step_{1};          // BUG FIX: uint8_t로 변경 (1~10)
  uint8_t  manual_step_{1};        // BUG FIX: uint8_t로 변경 (1~10)

  sentinel_interfaces::msg::MotorAngle current_angle_{};
  sentinel_interfaces::msg::MotorAngle last_command_{};

  double   pan_err_acc_{0.0};
  double   tilt_err_acc_{0.0};
  uint16_t last_cmd_pan_step_{0};
  uint16_t last_cmd_tilt_step_{0};

  // ── ROS ──
  std::unique_ptr<sentinel_motor::UdpTransport> transport_;
  rclcpp::Subscription<sentinel_interfaces::msg::MotorAngle>::SharedPtr command_sub_;
  rclcpp::Subscription<std_msgs::msg::UInt8>::SharedPtr  system_mode_sub_;
  rclcpp::Subscription<std_msgs::msg::UInt16>::SharedPtr scan_step_sub_;
  rclcpp::Subscription<std_msgs::msg::UInt16>::SharedPtr manual_step_sub_;
  rclcpp::Subscription<std_msgs::msg::UInt8>::SharedPtr  manual_btn_sub_;  // BUG FIX: 추가
  rclcpp::Publisher<sentinel_interfaces::msg::MotorAngle>::SharedPtr angle_pub_;
  rclcpp::Publisher<sentinel_interfaces::msg::MotorStatus>::SharedPtr status_pub_;
  rclcpp::Publisher<std_msgs::msg::UInt8MultiArray>::SharedPtr raw_feedback_pub_;
  rclcpp::TimerBase::SharedPtr feedback_timer_;
  rclcpp::TimerBase::SharedPtr command_resend_timer_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PanTiltControlNode>());
  rclcpp::shutdown();
  return 0;
}