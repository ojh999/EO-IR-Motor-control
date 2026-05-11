#ifndef SENTINEL_MOTOR__PACKET_DEF_HPP_
#define SENTINEL_MOTOR__PACKET_DEF_HPP_

#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace sentinel_motor
{

constexpr std::size_t kCommandPacketSize = 7;
constexpr std::size_t kFeedbackPacketSize = 36;

struct CommandPacket
{
  uint8_t mode{0};   // 0=SCAN, 1=TRACK
  uint16_t pan{0};   // TRACK: 목표 step 0~4095
  uint16_t tilt{0};  // TRACK: 목표 step 0~4095
  uint16_t step{0};  // SCAN: 스캔 step 0~4095, 0=현재값 유지
};

struct MotorFeedback
{
  uint8_t  moving{0};
  uint8_t  moving_status{0};
  uint16_t pwm{0};
  uint16_t current{0};
  uint32_t velocity{0};
  uint32_t position{0};   // raw 0~4095
  uint16_t voltage{0};
  uint8_t  temperature{0};
  uint8_t  hw_error{0};
};

struct FeedbackPacket
{
  MotorFeedback pan{};
  MotorFeedback tilt{};
};

inline void write_le16(uint16_t value, uint8_t * dst)
{
  dst[0] = static_cast<uint8_t>(value & 0xFFU);
  dst[1] = static_cast<uint8_t>((value >> 8U) & 0xFFU);
}

inline uint16_t read_le16(const uint8_t * src)
{
  return static_cast<uint16_t>(src[0]) |
         static_cast<uint16_t>(src[1] << 8U);
}

inline uint32_t read_le32(const uint8_t * src)
{
  return static_cast<uint32_t>(src[0]) |
         (static_cast<uint32_t>(src[1]) << 8U) |
         (static_cast<uint32_t>(src[2]) << 16U) |
         (static_cast<uint32_t>(src[3]) << 24U);
}

inline std::array<uint8_t, kCommandPacketSize> serialize_command(const CommandPacket & command)
{
  std::array<uint8_t, kCommandPacketSize> packet{};
  packet[0] = command.mode;
  write_le16(command.pan,  &packet[1]);
  write_le16(command.tilt, &packet[3]);
  write_le16(command.step, &packet[5]);
  return packet;
}

inline MotorFeedback parse_motor_feedback(const uint8_t * src)
{
  MotorFeedback fb{};
  fb.moving        = src[0];
  fb.moving_status = src[1];
  fb.pwm           = read_le16(&src[2]);
  fb.current       = read_le16(&src[4]);
  fb.velocity      = read_le32(&src[6]);
  fb.position      = read_le32(&src[10]);
  fb.voltage       = read_le16(&src[14]);
  fb.temperature   = src[16];
  fb.hw_error      = src[17];
  return fb;
}

inline FeedbackPacket parse_feedback(const std::array<uint8_t, kFeedbackPacketSize> & raw)
{
  FeedbackPacket feedback{};
  feedback.pan  = parse_motor_feedback(&raw[0]);
  feedback.tilt = parse_motor_feedback(&raw[18]);
  return feedback;
}

}  // namespace sentinel_motor

#endif  // SENTINEL_MOTOR__PACKET_DEF_HPP_
