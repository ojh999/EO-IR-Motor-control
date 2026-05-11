#ifndef SENTINEL_MOTOR__PACKET_DEF_HPP_
#define SENTINEL_MOTOR__PACKET_DEF_HPP_

#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace sentinel_motor
{

// ─── Packet Sizes ────────────────────────────────────────────────────
constexpr std::size_t kCommandPacketSize  = 9;   // Jetson -> Zybo
constexpr std::size_t kMotorFeedbackSize  = 18;
constexpr std::size_t kFeedbackPacketSize = 36;  // Zybo -> Jetson (18B × 2)

// ─── Mode (scan=0, manual=1, scan+track=2, manual+track=3) ──────────
constexpr uint8_t kModeScan         = 0;
constexpr uint8_t kModeManual       = 1;
constexpr uint8_t kModeScanTrack    = 2;
constexpr uint8_t kModeManualTrack  = 3;

inline bool is_tracking(uint8_t mode)
{
  return mode == kModeScanTrack || mode == kModeManualTrack;
}

inline uint8_t base_mode(uint8_t mode)
{
  return (mode >= kModeScanTrack) ? static_cast<uint8_t>(mode - 2U) : mode;
}

// ─── Button Bitmask ──────────────────────────────────────────────────
constexpr uint8_t kButtonLeft   = 0x01;
constexpr uint8_t kButtonRight  = 0x02;
constexpr uint8_t kButtonUp     = 0x04;
constexpr uint8_t kButtonDown   = 0x08;
constexpr uint8_t kButtonCenter = 0x10;

// ─── Command Packet (Jetson -> Zybo, 9 bytes) ───────────────────────
//   Byte 0     : mode           (uint8, 0~3)
//   Byte 1     : scan_button    (uint8, bitmask)
//   Byte 2     : manual_button  (uint8, bitmask)
//   Byte 3..4  : pan            (uint16, LE, 0~4095)
//   Byte 5..6  : tilt           (uint16, LE, 0~4095)
//   Byte 7     : scan_step      (uint8)
//   Byte 8     : manual_step    (uint8)

struct CommandPacket
{
  uint8_t  mode{0};
  uint8_t  scan_button{0};
  uint8_t  manual_button{0};
  uint16_t pan{0};
  uint16_t tilt{0};
  uint8_t  scan_step{1};
  uint8_t  manual_step{1};
};

// ─── Motor Feedback (18 bytes per motor) ─────────────────────────────
//   Byte 0     : moving         (uint8)
//   Byte 1     : moving_status  (uint8)
//   Byte 2..3  : pwm            (uint16, LE)
//   Byte 4..5  : current        (uint16, LE)
//   Byte 6..9  : velocity       (uint32, LE)
//   Byte 10..13: position       (uint32, LE, 0~4095)
//   Byte 14..15: voltage        (uint16, LE)
//   Byte 16    : temperature    (uint8)
//   Byte 17    : hw_error       (uint8)

struct MotorFeedback
{
  uint8_t  moving{0};
  uint8_t  moving_status{0};
  uint16_t pwm{0};
  uint16_t current{0};
  uint32_t velocity{0};
  uint32_t position{0};
  uint16_t voltage{0};
  uint8_t  temperature{0};
  uint8_t  hw_error{0};
};

// ─── Feedback Packet (Zybo -> Jetson, 36 bytes) ─────────────────────
//   Byte 0..17 : pan  MotorFeedback
//   Byte 18..35: tilt MotorFeedback

struct FeedbackPacket
{
  MotorFeedback pan{};
  MotorFeedback tilt{};
};

// ─── Byte-order Helpers ──────────────────────────────────────────────

inline void write_le16(uint16_t value, uint8_t * dst)
{
  dst[0] = static_cast<uint8_t>(value & 0xFFU);
  dst[1] = static_cast<uint8_t>((value >> 8U) & 0xFFU);
}

inline uint16_t read_le16(const uint8_t * src)
{
  return static_cast<uint16_t>(src[0]) |
         static_cast<uint16_t>(static_cast<uint16_t>(src[1]) << 8U);
}

inline uint32_t read_le32(const uint8_t * src)
{
  return static_cast<uint32_t>(src[0])        |
         (static_cast<uint32_t>(src[1]) << 8U)  |
         (static_cast<uint32_t>(src[2]) << 16U) |
         (static_cast<uint32_t>(src[3]) << 24U);
}

// ─── Command Serialize / Parse ───────────────────────────────────────

inline std::array<uint8_t, kCommandPacketSize> serialize_command(const CommandPacket & cmd)
{
  std::array<uint8_t, kCommandPacketSize> packet{};
  packet[0] = cmd.mode;
  packet[1] = cmd.scan_button;
  packet[2] = cmd.manual_button;
  write_le16(cmd.pan,  &packet[3]);
  write_le16(cmd.tilt, &packet[5]);
  packet[7] = cmd.scan_step;
  packet[8] = cmd.manual_step;
  return packet;
}

inline CommandPacket parse_command(const uint8_t * data, std::size_t size)
{
  if (size < kCommandPacketSize) {
    throw std::runtime_error("invalid command packet size: expected 9 bytes");
  }
  CommandPacket cmd{};
  cmd.mode          = data[0];
  cmd.scan_button   = data[1];
  cmd.manual_button = data[2];
  cmd.pan           = read_le16(&data[3]);
  cmd.tilt          = read_le16(&data[5]);
  cmd.scan_step     = data[7];
  cmd.manual_step   = data[8];
  return cmd;
}

// ─── Feedback Parse / Serialize ──────────────────────────────────────

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

inline void write_motor_feedback(const MotorFeedback & fb, uint8_t * dst)
{
  dst[0] = fb.moving;
  dst[1] = fb.moving_status;
  write_le16(fb.pwm,     &dst[2]);
  write_le16(fb.current, &dst[4]);
  // velocity (4B LE)
  dst[6]  = static_cast<uint8_t>(fb.velocity & 0xFFU);
  dst[7]  = static_cast<uint8_t>((fb.velocity >> 8U) & 0xFFU);
  dst[8]  = static_cast<uint8_t>((fb.velocity >> 16U) & 0xFFU);
  dst[9]  = static_cast<uint8_t>((fb.velocity >> 24U) & 0xFFU);
  // position (4B LE)
  dst[10] = static_cast<uint8_t>(fb.position & 0xFFU);
  dst[11] = static_cast<uint8_t>((fb.position >> 8U) & 0xFFU);
  dst[12] = static_cast<uint8_t>((fb.position >> 16U) & 0xFFU);
  dst[13] = static_cast<uint8_t>((fb.position >> 24U) & 0xFFU);
  write_le16(fb.voltage, &dst[14]);
  dst[16] = fb.temperature;
  dst[17] = fb.hw_error;
}

inline FeedbackPacket parse_feedback(const std::array<uint8_t, kFeedbackPacketSize> & raw)
{
  FeedbackPacket feedback{};
  feedback.pan  = parse_motor_feedback(&raw[0]);
  feedback.tilt = parse_motor_feedback(&raw[kMotorFeedbackSize]);
  return feedback;
}

inline std::array<uint8_t, kFeedbackPacketSize> serialize_feedback(const FeedbackPacket & fb)
{
  std::array<uint8_t, kFeedbackPacketSize> packet{};
  write_motor_feedback(fb.pan,  &packet[0]);
  write_motor_feedback(fb.tilt, &packet[kMotorFeedbackSize]);
  return packet;
}

}  // namespace sentinel_motor

#endif  // SENTINEL_MOTOR__PACKET_DEF_HPP_
