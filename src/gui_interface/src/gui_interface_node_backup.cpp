#include "gui_interface/Protocol.hpp"

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

#include <rclcpp/rclcpp.hpp>
#include <sentinel_interfaces/msg/button_input.hpp>
#include <sentinel_interfaces/msg/frame_info.hpp>
#include <sentinel_interfaces/msg/motor_angle.hpp>
#include <std_msgs/msg/u_int16.hpp>
#include <std_msgs/msg/u_int8.hpp>
#include <std_msgs/msg/u_int8_multi_array.hpp>

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using namespace std::chrono_literals;

class GuiInterfaceNode : public rclcpp::Node
{
public:
  GuiInterfaceNode()
  : Node("gui_interface_node"),
    socket_(io_context_)
  {
    listen_ip_ = this->declare_parameter<std::string>("listen_ip", "0.0.0.0");
    listen_port_ = this->declare_parameter<int>("listen_port", 3000);
    gui_ip_ = this->declare_parameter<std::string>("gui_ip", "10.42.0.1");
    telemetry_port_ = this->declare_parameter<int>("telemetry_port", 5001);
    command_poll_ms_ = this->declare_parameter<int>("command_poll_ms", 10);
    motor_tlm_period_ms_ = this->declare_parameter<int>("motor_tlm_period_ms", 50);
    system_tlm_period_ms_ = this->declare_parameter<int>("system_tlm_period_ms", 100);
    frame_tlm_period_ms_ = this->declare_parameter<int>("frame_tlm_period_ms", 1000);
    system_status_code_ = this->declare_parameter<int>("system_status_code", 0);

    pan_min_deg_ = this->declare_parameter<double>("pan_min_deg", 0.0);
    pan_max_deg_ = this->declare_parameter<double>("pan_max_deg", 360.0);
    tilt_min_deg_ = this->declare_parameter<double>("tilt_min_deg", 110.0);
    tilt_max_deg_ = this->declare_parameter<double>("tilt_max_deg", 250.0);
    pan_raw_per_deg_ = this->declare_parameter<double>("pan_raw_per_deg", 1.0);
    tilt_raw_per_deg_ = this->declare_parameter<double>("tilt_raw_per_deg", 1.0);
    pan_raw_offset_ = this->declare_parameter<double>("pan_raw_offset", 0.0);
    tilt_raw_offset_ = this->declare_parameter<double>("tilt_raw_offset", 0.0);
    step_size_ = this->declare_parameter<int>("step_size", 1);
    home_pan_ = this->declare_parameter<int>("home_pan", 180);
    home_tilt_ = this->declare_parameter<int>("home_tilt", 180);
    pan_min_raw_ = this->declare_parameter<int>("pan_min", 0);
    pan_max_raw_ = this->declare_parameter<int>("pan_max", 360);
    tilt_min_raw_ = this->declare_parameter<int>("tilt_min", 0);
    tilt_max_raw_ = this->declare_parameter<int>("tilt_max", 360);

    angle_get_topic_ = this->declare_parameter<std::string>("angle_get_topic", "/motor/angle/get");
    angle_set_topic_ = this->declare_parameter<std::string>("angle_set_topic", "/motor/angle/set");
    status_topic_ = this->declare_parameter<std::string>("status_topic", "/motor/status");
    system_mode_topic_ = this->declare_parameter<std::string>("system_mode_topic", "/system/mode");
    button_topic_ = this->declare_parameter<std::string>("button_topic", "/control/button");
    detection_center_x_topic_ = this->declare_parameter<std::string>(
      "detection_center_x_topic", "/detection/object/center_x");
    detection_center_y_topic_ = this->declare_parameter<std::string>(
      "detection_center_y_topic", "/detection/object/center_y");
    detection_count_topic_ = this->declare_parameter<std::string>(
      "detection_count_topic", "/detection/object/count");
    frame_info_topic_ = this->declare_parameter<std::string>("frame_info_topic", "/video/frame_info");
    raw_motor_topic_ = this->declare_parameter<std::string>("raw_motor_topic", "/motor/feedback/raw");

    openSocket();

    scan_step_topic_ = this->declare_parameter<std::string>("scan_step_topic", "/motor/scan_step");

    system_mode_pub_ = this->create_publisher<std_msgs::msg::UInt8>(system_mode_topic_, 10);
    angle_set_pub_ = this->create_publisher<sentinel_interfaces::msg::MotorAngle>(angle_set_topic_, 10);
    button_pub_ = this->create_publisher<sentinel_interfaces::msg::ButtonInput>(button_topic_, 10);
    scan_step_pub_ = this->create_publisher<std_msgs::msg::UInt16>(scan_step_topic_, 10);

    angle_sub_ = this->create_subscription<sentinel_interfaces::msg::MotorAngle>(
      angle_get_topic_, 10, std::bind(&GuiInterfaceNode::angleCallback, this, std::placeholders::_1));
    raw_motor_sub_ = this->create_subscription<std_msgs::msg::UInt8MultiArray>(
      raw_motor_topic_, 10,
      std::bind(&GuiInterfaceNode::rawMotorCallback, this, std::placeholders::_1));
    system_mode_sub_ = this->create_subscription<std_msgs::msg::UInt8>(
      system_mode_topic_, 10, std::bind(&GuiInterfaceNode::systemModeCallback, this, std::placeholders::_1));
    detection_center_x_sub_ = this->create_subscription<std_msgs::msg::UInt16>(
      detection_center_x_topic_, 10,
      std::bind(&GuiInterfaceNode::detectionCenterXCallback, this, std::placeholders::_1));
    detection_center_y_sub_ = this->create_subscription<std_msgs::msg::UInt16>(
      detection_center_y_topic_, 10,
      std::bind(&GuiInterfaceNode::detectionCenterYCallback, this, std::placeholders::_1));
    detection_count_sub_ = this->create_subscription<std_msgs::msg::UInt8>(
      detection_count_topic_, 10,
      std::bind(&GuiInterfaceNode::detectionCountCallback, this, std::placeholders::_1));
    frame_info_sub_ = this->create_subscription<sentinel_interfaces::msg::FrameInfo>(
      frame_info_topic_, 10, std::bind(&GuiInterfaceNode::frameInfoCallback, this, std::placeholders::_1));

    command_poll_timer_ = this->create_wall_timer(
      std::chrono::milliseconds(command_poll_ms_),
      std::bind(&GuiInterfaceNode::pollCommands, this));
    motor_tlm_timer_ = this->create_wall_timer(
      std::chrono::milliseconds(motor_tlm_period_ms_),
      std::bind(&GuiInterfaceNode::sendMotorTelemetry, this));
    system_tlm_timer_ = this->create_wall_timer(
      std::chrono::milliseconds(system_tlm_period_ms_),
      std::bind(&GuiInterfaceNode::sendSystemStatus, this));
    frame_tlm_timer_ = this->create_wall_timer(
      std::chrono::milliseconds(frame_tlm_period_ms_),
      std::bind(&GuiInterfaceNode::sendFrameInfo, this));

    RCLCPP_INFO(
      this->get_logger(),
      "gui_interface_node ready | listen=%s:%d gui=%s:%d",
      listen_ip_.c_str(), listen_port_, gui_ip_.c_str(), telemetry_port_);
  }

private:
  void openSocket()
  {
    const auto listen_address = boost::asio::ip::make_address(listen_ip_);
    socket_.open(boost::asio::ip::udp::v4());
    socket_.set_option(boost::asio::socket_base::reuse_address(true));
    socket_.bind(boost::asio::ip::udp::endpoint(listen_address, static_cast<uint16_t>(listen_port_)));
    socket_.non_blocking(true);

    telemetry_endpoint_ = boost::asio::ip::udp::endpoint(
      boost::asio::ip::make_address(gui_ip_), static_cast<uint16_t>(telemetry_port_));
  }

  void pollCommands()
  {
    for (;;) {
      std::array<uint8_t, 64> buffer{};
      boost::asio::ip::udp::endpoint sender;
      boost::system::error_code error_code;
      const auto bytes_received = socket_.receive_from(
        boost::asio::buffer(buffer), sender, 0, error_code);

      if (error_code == boost::asio::error::would_block ||
          error_code == boost::asio::error::try_again) {
        return;
      }

      if (error_code) {
        RCLCPP_WARN_THROTTLE(
          this->get_logger(), *this->get_clock(), 2000,
          "UDP command receive error: %s", error_code.message().c_str());
        return;
      }

      command_source_endpoint_ = sender;
      telemetry_endpoint_ = boost::asio::ip::udp::endpoint(
        sender.address(), static_cast<uint16_t>(telemetry_port_));

      if (bytes_received == 0U) {
        continue;
      }

      dispatchCommand(buffer.data(), bytes_received);
    }
  }

  void dispatchCommand(const uint8_t * data, std::size_t size)
  {
    const uint8_t packet_id = data[0];

    try {
      if (packet_id == gui_interface::kCmdModeChangeId) {
        const auto command = gui_interface::parse_mode_command(data, size);
        logCommandBytes("mode", data, size, command.payload_offset);
        handleModeCommand(command);
        return;
      }

      if (packet_id == gui_interface::kCmdButtonId) {
        const auto command = gui_interface::parse_button_command(data, size);
        logCommandBytes("button", data, size, command.payload_offset);
        handleButtonCommand(command);
        return;
      }

      RCLCPP_DEBUG(this->get_logger(), "Ignoring unknown GUI packet id=0x%02X", packet_id);
    } catch (const std::exception & ex) {
      RCLCPP_WARN(this->get_logger(), "Rejected GUI packet id=0x%02X: %s", packet_id, ex.what());
    }
  }

  void logCommandBytes(
    const char * label,
    const uint8_t * data,
    std::size_t size,
    std::size_t payload_offset)
  {
    std::ostringstream stream;
    stream << std::hex << std::uppercase;
    for (std::size_t i = 0; i < size; ++i) {
      if (i > 0U) {
        stream << ' ';
      }
      stream.width(2);
      stream.fill('0');
      stream << static_cast<int>(data[i]);
    }

    RCLCPP_INFO(
      this->get_logger(),
      "GUI %s packet | size=%zu payload_offset=%zu bytes=[%s]",
      label,
      size,
      payload_offset,
      stream.str().c_str());
  }

  void handleModeCommand(const gui_interface::ModeCommand & command)
{
  if (command.mode > kManualMode) {
    RCLCPP_WARN(this->get_logger(), "Invalid mode: %u", command.mode);
    return;
  }

  system_mode_ = command.mode;
  if (command.mode == kManualMode) {
    syncManualTargetToCurrentAngle();
  }

  std_msgs::msg::UInt8 mode_msg;
  mode_msg.data = system_mode_;
  system_mode_pub_->publish(mode_msg);

  RCLCPP_INFO(this->get_logger(), "GUI mode update | mode=%u", system_mode_);
}

  void handleButtonCommand(const gui_interface::ButtonCommand & command)
  {
    sentinel_interfaces::msg::ButtonInput button_msg;
    button_msg.buttons = command.buttons;
    button_pub_->publish(button_msg);

    // step은 모드 무관하게 항상 반영
    // - scan_step: SCAN 모드에서 Zybo로 전달
    // - step_size_: MANUAL 모드 버튼 이동량에도 동기화
    if (command.step > 0) {
      step_size_ = static_cast<int>(command.step);
    }
    std_msgs::msg::UInt16 step_msg;
    step_msg.data = command.step;
    scan_step_pub_->publish(step_msg);

    if (system_mode_ != kManualMode) {
      RCLCPP_INFO_THROTTLE(
        this->get_logger(), *this->get_clock(), 2000,
        "GUI button | mode=%u (non-manual) step=%u — angle cmd skipped",
        system_mode_, command.step);
      return;
    }

    RCLCPP_INFO(
      this->get_logger(),
      "GUI manual button | buttons=0x%02X step=%u",
      command.buttons, command.step);

    publishManualAngleCommand(command.buttons);
  }

  void angleCallback(const sentinel_interfaces::msg::MotorAngle::SharedPtr msg)
  {
    pan_current_raw_ = msg->pan;
    tilt_current_raw_ = msg->tilt;
    pan_current_deg_ = rawToDegree(msg->pan, pan_raw_per_deg_, pan_raw_offset_);
    tilt_current_deg_ = rawToDegree(msg->tilt, tilt_raw_per_deg_, tilt_raw_offset_);

    if (!manual_target_valid_) {
      manual_target_pan_raw_ = msg->pan;
      manual_target_tilt_raw_ = msg->tilt;
      manual_target_valid_ = true;
    }
  }

  void rawMotorCallback(const std_msgs::msg::UInt8MultiArray::SharedPtr msg)
  {
    if (msg->data.size() < gui_interface::kMotorRawPayloadSize) {
      return;
    }
    std::copy_n(msg->data.begin(), gui_interface::kMotorRawPayloadSize, raw_motor_feedback_.begin());
    raw_motor_valid_ = true;
  }

  void systemModeCallback(const std_msgs::msg::UInt8::SharedPtr msg)
  {
    system_mode_ = static_cast<uint8_t>(std::min<int>(msg->data, kManualMode));
  }

  void detectionCenterXCallback(const std_msgs::msg::UInt16::SharedPtr msg)
  {
    detection_center_x_ = msg->data;
    sendDetectionTelemetry();
  }

  void detectionCenterYCallback(const std_msgs::msg::UInt16::SharedPtr msg)
  {
    detection_center_y_ = msg->data;
  }

  void detectionCountCallback(const std_msgs::msg::UInt8::SharedPtr msg)
  {
    detection_count_ = msg->data;
  }

  void frameInfoCallback(const sentinel_interfaces::msg::FrameInfo::SharedPtr msg)
  {
    frame_width_ = static_cast<uint16_t>(std::min<int32_t>(msg->width, 65535));
    frame_height_ = static_cast<uint16_t>(std::min<int32_t>(msg->height, 65535));
    fps_ = msg->fps;
  }

  void sendSystemStatus()
  {
    const auto packet = gui_interface::build_system_status_packet(
      system_mode_,
      static_cast<uint8_t>(std::clamp(system_status_code_, 0, 255)));
    sendPacket(packet.data(), packet.size());
  }

  void sendMotorTelemetry()
  {
    if (!raw_motor_valid_) {
      return;
    }
    const auto packet = gui_interface::build_motor_telemetry_from_raw(raw_motor_feedback_.data());
    sendPacket(packet.data(), packet.size());
  }

  void sendDetectionTelemetry()
  {
    const auto packet = gui_interface::build_detection_packet(
      detection_count_,
      detection_center_x_,
      detection_center_y_,
      frame_width_,
      frame_height_);
    sendPacket(packet.data(), packet.size());
  }

  void sendFrameInfo()
  {
    const auto packet = gui_interface::build_frame_info_packet(
      frame_width_,
      frame_height_,
      fps_);
    sendPacket(packet.data(), packet.size());
  }

  void sendPacket(const uint8_t * data, std::size_t size)
  {
    boost::system::error_code error_code;
    const auto bytes_sent = socket_.send_to(boost::asio::buffer(data, size), telemetry_endpoint_, 0, error_code);
    if (error_code) {
      RCLCPP_WARN_THROTTLE(
        this->get_logger(), *this->get_clock(), 2000,
        "UDP telemetry send error: %s", error_code.message().c_str());
      return;
    }

    if (bytes_sent != size) {
      RCLCPP_WARN_THROTTLE(
        this->get_logger(), *this->get_clock(), 2000,
        "Short UDP telemetry send: expected %zu bytes, sent %zu bytes",
        size, bytes_sent);
    }
  }

  void publishManualAngleCommand(uint8_t buttons)
  {
    int pan = manual_target_pan_raw_;
    int tilt = manual_target_tilt_raw_;

    if ((buttons & kButtonCenter) != 0U) {
      pan = home_pan_;
      tilt = home_tilt_;
    } else {
      const bool left = (buttons & kButtonLeft) != 0U;
      const bool right = (buttons & kButtonRight) != 0U;
      const bool up = (buttons & kButtonUp) != 0U;
      const bool down = (buttons & kButtonDown) != 0U;

      if (left != right) {
        pan += left ? -step_size_ : step_size_;
      }
      if (up != down) {
        tilt += up ? step_size_ : -step_size_;
      }
    }

    manual_target_pan_raw_ = std::clamp(pan, pan_min_raw_, pan_max_raw_);
    manual_target_tilt_raw_ = std::clamp(tilt, tilt_min_raw_, tilt_max_raw_);
    manual_target_valid_ = true;

    sentinel_interfaces::msg::MotorAngle angle_msg;
    angle_msg.pan = static_cast<uint16_t>(manual_target_pan_raw_);
    angle_msg.tilt = static_cast<uint16_t>(manual_target_tilt_raw_);
    angle_set_pub_->publish(angle_msg);

    RCLCPP_INFO(
      this->get_logger(),
      "GUI manual angle | buttons=0x%02X cmd=(%u,%u)",
      buttons,
      angle_msg.pan,
      angle_msg.tilt);
  }

  void syncManualTargetToCurrentAngle()
  {
    if (isRawAngleValid(pan_current_raw_, pan_min_raw_, pan_max_raw_) &&
        isRawAngleValid(tilt_current_raw_, tilt_min_raw_, tilt_max_raw_))
    {
      manual_target_pan_raw_ = static_cast<int>(pan_current_raw_);
      manual_target_tilt_raw_ = static_cast<int>(tilt_current_raw_);
      manual_target_valid_ = true;
      return;
    }

    if (!manual_target_valid_) {
      manual_target_pan_raw_ = std::clamp(home_pan_, pan_min_raw_, pan_max_raw_);
      manual_target_tilt_raw_ = std::clamp(home_tilt_, tilt_min_raw_, tilt_max_raw_);
      manual_target_valid_ = true;
    }
  }

  static bool isRawAngleValid(uint16_t value, int min_raw, int max_raw)
  {
    return static_cast<int>(value) >= min_raw && static_cast<int>(value) <= max_raw;
  }

  static float rawToDegree(uint16_t raw, double raw_per_deg, double raw_offset)
  {
    if (std::abs(raw_per_deg) < std::numeric_limits<double>::epsilon()) {
      return 0.0F;
    }

    return static_cast<float>((static_cast<double>(raw) - raw_offset) / raw_per_deg);
  }

  std::string listen_ip_;
  int listen_port_;
  std::string gui_ip_;
  int telemetry_port_;
  int command_poll_ms_;
  int motor_tlm_period_ms_;
  int system_tlm_period_ms_;
  int frame_tlm_period_ms_;
  int system_status_code_;

  double pan_min_deg_;
  double pan_max_deg_;
  double tilt_min_deg_;
  double tilt_max_deg_;
  double pan_raw_per_deg_;
  double tilt_raw_per_deg_;
  double pan_raw_offset_;
  double tilt_raw_offset_;
  int step_size_;
  int home_pan_;
  int home_tilt_;
  int pan_min_raw_;
  int pan_max_raw_;
  int tilt_min_raw_;
  int tilt_max_raw_;

  std::string angle_set_topic_;
  std::string angle_get_topic_;
  std::string status_topic_;
  std::string scan_step_topic_;
  std::string raw_motor_topic_;
  std::string system_mode_topic_;
  std::string button_topic_;
  std::string detection_center_x_topic_;
  std::string detection_center_y_topic_;
  std::string detection_count_topic_;
  std::string frame_info_topic_;

  boost::asio::io_context io_context_;
  boost::asio::ip::udp::socket socket_;
  boost::asio::ip::udp::endpoint telemetry_endpoint_;
  boost::asio::ip::udp::endpoint command_source_endpoint_;

  rclcpp::Publisher<std_msgs::msg::UInt8>::SharedPtr system_mode_pub_;
  rclcpp::Publisher<sentinel_interfaces::msg::MotorAngle>::SharedPtr angle_set_pub_;
  rclcpp::Publisher<sentinel_interfaces::msg::ButtonInput>::SharedPtr button_pub_;
  rclcpp::Publisher<std_msgs::msg::UInt16>::SharedPtr scan_step_pub_;

  rclcpp::Subscription<sentinel_interfaces::msg::MotorAngle>::SharedPtr angle_sub_;
  rclcpp::Subscription<std_msgs::msg::UInt8MultiArray>::SharedPtr raw_motor_sub_;
  rclcpp::Subscription<std_msgs::msg::UInt8>::SharedPtr system_mode_sub_;
  rclcpp::Subscription<std_msgs::msg::UInt16>::SharedPtr detection_center_x_sub_;
  rclcpp::Subscription<std_msgs::msg::UInt16>::SharedPtr detection_center_y_sub_;
  rclcpp::Subscription<std_msgs::msg::UInt8>::SharedPtr detection_count_sub_;
  rclcpp::Subscription<sentinel_interfaces::msg::FrameInfo>::SharedPtr frame_info_sub_;

  rclcpp::TimerBase::SharedPtr command_poll_timer_;
  rclcpp::TimerBase::SharedPtr motor_tlm_timer_;
  rclcpp::TimerBase::SharedPtr system_tlm_timer_;
  rclcpp::TimerBase::SharedPtr frame_tlm_timer_;

  uint8_t system_mode_{kScanMode};
  uint16_t pan_current_raw_{180U};
  uint16_t tilt_current_raw_{180U};
  int manual_target_pan_raw_{180};
  int manual_target_tilt_raw_{180};
  bool manual_target_valid_{false};
  float pan_current_deg_{0.0F};
  float tilt_current_deg_{0.0F};
  std::array<uint8_t, gui_interface::kMotorRawPayloadSize> raw_motor_feedback_{};
  bool raw_motor_valid_{false};
  uint8_t detection_count_{0U};
  uint16_t detection_center_x_{0U};
  uint16_t detection_center_y_{0U};
  uint16_t frame_width_{0U};
  uint16_t frame_height_{0U};
  float fps_{0.0F};

  static constexpr uint8_t kButtonLeft = 1U << 0U;
  static constexpr uint8_t kButtonRight = 1U << 1U;
  static constexpr uint8_t kButtonUp = 1U << 2U;
  static constexpr uint8_t kButtonDown = 1U << 3U;
  static constexpr uint8_t kButtonCenter = 1U << 4U;
  static constexpr uint8_t kScanMode = 0U;
  static constexpr uint8_t kTrackingMode = 1U;
  static constexpr uint8_t kManualMode = 2U;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<GuiInterfaceNode>());
  rclcpp::shutdown();
  return 0;
}
