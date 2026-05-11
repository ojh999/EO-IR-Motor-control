#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

#include <rclcpp/rclcpp.hpp>
#include <sentinel_interfaces/msg/motor_angle.hpp>
#include <sentinel_interfaces/msg/motor_status.hpp>
#include <std_msgs/msg/u_int8.hpp>
#include <std_msgs/msg/u_int16.hpp>
#include <std_msgs/msg/u_int8_multi_array.hpp>

#include <array>
#include <chrono>
#include <cstdint>
#include <string>

using namespace std::chrono_literals;

// ── 모드 상수 ──
static constexpr uint8_t MODE_SCAN   = 0;
static constexpr uint8_t MODE_MANUAL = 1;
static constexpr uint8_t MODE_TRACK  = 2;

// ── GUI → Thor 9B 패킷 ──
// [0] mode        : 0=scan, 1=manual
// [1] tracking    : 0=off, 1=on
// [2] btn         : 버튼 비트마스크
// [3~4] pan       : uint16 LE, 0~4095
// [5~6] tilt      : uint16 LE, 0~4095
// [7] scan_step   : 1~10
// [8] manual_step : 1~10
static constexpr size_t kCmdPacketSize = 9;

// ── Thor → GUI 36B 피드백 ──
// [0~17]  PAN  MotorFeedback 18B
// [18~35] TILT MotorFeedback 18B
static constexpr size_t kFeedbackSize = 36;

class GuiInterfaceNode : public rclcpp::Node
{
public:
  GuiInterfaceNode()
  : Node("gui_interface_node"),
    socket_(io_context_)
  {
    // ── 파라미터 ──
    listen_ip_      = this->declare_parameter<std::string>("listen_ip",      "0.0.0.0");
    listen_port_    = this->declare_parameter<int>("listen_port",    3000);
    gui_ip_         = this->declare_parameter<std::string>("gui_ip",         "10.42.0.1");
    telemetry_port_ = this->declare_parameter<int>("telemetry_port", 9001);
    command_poll_ms_= this->declare_parameter<int>("command_poll_ms", 10);
    motor_tlm_ms_   = this->declare_parameter<int>("motor_tlm_period_ms", 50);

    system_mode_topic_  = this->declare_parameter<std::string>("system_mode_topic",  "/system/mode");
    angle_set_topic_    = this->declare_parameter<std::string>("angle_set_topic",    "/motor/angle/set");
    scan_step_topic_    = this->declare_parameter<std::string>("scan_step_topic",    "/motor/scan_step");
    manual_step_topic_  = this->declare_parameter<std::string>("manual_step_topic",  "/motor/manual_step");
    manual_btn_topic_   = this->declare_parameter<std::string>("manual_btn_topic",   "/motor/manual_btn");
    raw_motor_topic_    = this->declare_parameter<std::string>("raw_motor_topic",    "/motor/feedback/raw");

    // ── UDP 소켓 열기 ──
    openSocket();

    // ── 퍼블리셔 ──
    system_mode_pub_  = this->create_publisher<std_msgs::msg::UInt8>(system_mode_topic_, 10);
    angle_set_pub_    = this->create_publisher<sentinel_interfaces::msg::MotorAngle>(angle_set_topic_, 10);
    scan_step_pub_    = this->create_publisher<std_msgs::msg::UInt16>(scan_step_topic_, 10);
    manual_step_pub_  = this->create_publisher<std_msgs::msg::UInt16>(manual_step_topic_, 10);
    manual_btn_pub_   = this->create_publisher<std_msgs::msg::UInt8>(manual_btn_topic_, 10);

    // ── 구독 ──
    raw_motor_sub_ = this->create_subscription<std_msgs::msg::UInt8MultiArray>(
      raw_motor_topic_, 10,
      std::bind(&GuiInterfaceNode::rawMotorCallback, this, std::placeholders::_1));

    // ── 타이머 ──
    cmd_timer_ = this->create_wall_timer(
      std::chrono::milliseconds(command_poll_ms_),
      std::bind(&GuiInterfaceNode::pollCommands, this));
    tlm_timer_ = this->create_wall_timer(
      std::chrono::milliseconds(motor_tlm_ms_),
      std::bind(&GuiInterfaceNode::sendMotorTelemetry, this));

    RCLCPP_INFO(
      this->get_logger(),
      "gui_interface_node ready | listen=%s:%d gui=%s:%d",
      listen_ip_.c_str(), listen_port_, gui_ip_.c_str(), telemetry_port_);
  }

private:
  void openSocket()
  {
    socket_.open(boost::asio::ip::udp::v4());
    socket_.set_option(boost::asio::socket_base::reuse_address(true));
    socket_.bind(boost::asio::ip::udp::endpoint(
      boost::asio::ip::make_address(listen_ip_),
      static_cast<uint16_t>(listen_port_)));
    socket_.non_blocking(true);

    telemetry_endpoint_ = boost::asio::ip::udp::endpoint(
      boost::asio::ip::make_address(gui_ip_),
      static_cast<uint16_t>(telemetry_port_));
  }

  // ── GUI → Thor 9B 패킷 수신 및 파싱 ──
  void pollCommands()
  {
    for (;;) {
      std::array<uint8_t, 64> buf{};
      boost::asio::ip::udp::endpoint sender;
      boost::system::error_code ec;
      const auto bytes = socket_.receive_from(boost::asio::buffer(buf), sender, 0, ec);

      if (ec == boost::asio::error::would_block || ec == boost::asio::error::try_again) return;
      if (ec) {
        RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 2000,
          "UDP RX error: %s", ec.message().c_str());
        return;
      }
      if (bytes == 0U) continue;

      // GUI IP 자동 감지
      telemetry_endpoint_ = boost::asio::ip::udp::endpoint(
        sender.address(), static_cast<uint16_t>(telemetry_port_));

      if (bytes != kCmdPacketSize) {
        RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 2000,
          "Unexpected GUI packet size: %zu (expected %zu)", bytes, kCmdPacketSize);
        continue;
      }

      parseAndDispatch(buf.data());
    }
  }

  void parseAndDispatch(const uint8_t * data)
  {
    const uint8_t  auto_manual = data[0];   // 0=scan, 1=manual
    const uint8_t  tracking    = data[1];   // 0=off,  1=on
    const uint8_t  btn         = data[2];   // 버튼 비트마스크
    const uint16_t pan         = static_cast<uint16_t>(data[3]) | (static_cast<uint16_t>(data[4]) << 8);
    const uint16_t tilt        = static_cast<uint16_t>(data[5]) | (static_cast<uint16_t>(data[6]) << 8);
    const uint8_t  scan_step   = data[7];
    const uint8_t  manual_step = data[8];

    // ── auto_manual + tracking → mode_cmd 변환 ──
    // scan  + 비추적 = SCAN(0)
    // manual + 비추적 = MANUAL(1)
    // manual + 추적   = TRACK(2)
    uint8_t mode_cmd;
    if (auto_manual == 0U) {
      mode_cmd = MODE_SCAN;
    } else if (tracking == 0U) {
      mode_cmd = MODE_MANUAL;
    } else {
      mode_cmd = MODE_TRACK;
    }

    RCLCPP_INFO_THROTTLE(
      this->get_logger(), *this->get_clock(), 500,
      "GUI RX | auto_manual=%u tracking=%u btn=0x%02X pan=%u tilt=%u scan_step=%u manual_step=%u → mode_cmd=%u",
      auto_manual, tracking, btn, pan, tilt, scan_step, manual_step, mode_cmd);

    // ── mode_cmd 발행 ──
    if (mode_cmd != last_mode_cmd_) {
      std_msgs::msg::UInt8 mode_msg;
      mode_msg.data = mode_cmd;
      system_mode_pub_->publish(mode_msg);
      last_mode_cmd_ = mode_cmd;
    }

    // ── 버튼 비트마스크 발행 (MANUAL 모드) ──
    std_msgs::msg::UInt8 btn_msg;
    btn_msg.data = (mode_cmd == MODE_MANUAL) ? btn : 0U;
    manual_btn_pub_->publish(btn_msg);

    // ── 스텝 발행 ──
    if (scan_step > 0U) {
      std_msgs::msg::UInt16 ss_msg;
      ss_msg.data = scan_step;
      scan_step_pub_->publish(ss_msg);
    }
    if (manual_step > 0U) {
      std_msgs::msg::UInt16 ms_msg;
      ms_msg.data = manual_step;
      manual_step_pub_->publish(ms_msg);
    }

    // ── TRACK 모드: pan/tilt 목표 각도 발행 ──
    if (mode_cmd == MODE_TRACK) {
      sentinel_interfaces::msg::MotorAngle angle_msg;
      angle_msg.pan  = pan;
      angle_msg.tilt = tilt;
      angle_set_pub_->publish(angle_msg);
    }
  }

  // ── 피드백 수신 → GUI로 36B UDP 전송 ──
  void rawMotorCallback(const std_msgs::msg::UInt8MultiArray::SharedPtr msg)
  {
    if (msg->data.size() < kFeedbackSize) return;
    std::copy_n(msg->data.begin(), kFeedbackSize, raw_feedback_.begin());
    raw_valid_ = true;
  }

  void sendMotorTelemetry()
  {
    if (!raw_valid_) return;

    boost::system::error_code ec;
    socket_.send_to(boost::asio::buffer(raw_feedback_), telemetry_endpoint_, 0, ec);
    if (ec) {
      RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 2000,
        "UDP TX error: %s", ec.message().c_str());
    }
  }

  // ── 파라미터 ──
  std::string listen_ip_;
  int         listen_port_;
  std::string gui_ip_;
  int         telemetry_port_;
  int         command_poll_ms_;
  int         motor_tlm_ms_;
  std::string system_mode_topic_;
  std::string angle_set_topic_;
  std::string scan_step_topic_;
  std::string manual_step_topic_;
  std::string manual_btn_topic_;
  std::string raw_motor_topic_;

  // ── 상태 ──
  uint8_t last_mode_cmd_{MODE_SCAN};
  std::array<uint8_t, kFeedbackSize> raw_feedback_{};
  bool raw_valid_{false};

  // ── ROS ──
  rclcpp::Publisher<std_msgs::msg::UInt8>::SharedPtr                      system_mode_pub_;
  rclcpp::Publisher<sentinel_interfaces::msg::MotorAngle>::SharedPtr      angle_set_pub_;
  rclcpp::Publisher<std_msgs::msg::UInt16>::SharedPtr                     scan_step_pub_;
  rclcpp::Publisher<std_msgs::msg::UInt16>::SharedPtr                     manual_step_pub_;
  rclcpp::Publisher<std_msgs::msg::UInt8>::SharedPtr                      manual_btn_pub_;
  rclcpp::Subscription<std_msgs::msg::UInt8MultiArray>::SharedPtr         raw_motor_sub_;
  rclcpp::TimerBase::SharedPtr cmd_timer_;
  rclcpp::TimerBase::SharedPtr tlm_timer_;

  // ── UDP ──
  boost::asio::io_context          io_context_;
  boost::asio::ip::udp::socket     socket_;
  boost::asio::ip::udp::endpoint   telemetry_endpoint_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<GuiInterfaceNode>());
  rclcpp::shutdown();
  return 0;
}
