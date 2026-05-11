#ifndef GUI_INTERFACE__PROTOCOL_HPP_
#define GUI_INTERFACE__PROTOCOL_HPP_

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace gui_interface
{

// ─── Packet Sizes ────────────────────────────────────────────────────
// GUI -> Jetson: 9 bytes  (no ID prefix)
// Jetson -> GUI: 36 bytes (no ID prefix)
constexpr std::size_t kCmdPacketSize = 9;
constexpr std::size_t kMotorFeedbackSize = 18;
constexpr std::size_t kTlmPacketSize = 36;  // kMotorFeedbackSize * 2

// ─── Button Bitmask ──────────────────────────────────────────────────
constexpr uint8_t kButtonLeft  = 0x01;
constexpr uint8_t kButtonRight = 0x02;
constexpr uint8_t kButtonUp    = 0x04;
constexpr uint8_t kButtonDown  = 0x08;
constexpr uint8_t kButtonCenter = 0x10;

// ─── System Mode (matches GUI: scan=0, manual=1, track=2) ───────────
enum SystemMode : uint8_t
{
  MODE_SCAN    = 0,
  MODE_MANUAL  = 1,
  MODE_TRACK   = 2,
};

// ─── Position Constants ──────────────────────────────────────────────
constexpr uint16_t kPanMin     = 0;
constexpr uint16_t kPanMax     = 4095;
constexpr uint16_t kTiltMin    = 0;
constexpr uint16_t kTiltMax    = 4095;
constexpr uint16_t kCenterPos  = 2048;

// ─── Command Packet (GUI -> Jetson, 9 bytes) ─────────────────────────
//   Byte 0     : mode           (uint8)
//   Byte 1     : scan_button    (uint8, bitmask)
//   Byte 2     : manual_button  (uint8, bitmask)
//   Byte 3..4  : pan_position   (uint16, little-endian)
//   Byte 5..6  : tilt_position  (uint16, little-endian)
//   Byte 7     : scan_step      (uint8)
//   Byte 8     : manual_step    (uint8)

struct CommandPacket
{
  uint8_t  mode{0U};
  uint8_t  scan_button{0U};
  uint8_t  manual_button{0U};
  uint16_t pan_position{kCenterPos};
  uint16_t tilt_position{kCenterPos};
  uint8_t  scan_step{1U};
  uint8_t  manual_step{1U};
};

// ─── Motor Feedback (18 bytes per motor) ─────────────────────────────
//   Byte 0     : moving         (uint8)
//   Byte 1     : moving_status  (uint8)
//   Byte 2..3  : pwm            (uint16, little-endian)
//   Byte 4..5  : current        (uint16, little-endian)
//   Byte 6..9  : velocity       (uint32, little-endian)
//   Byte 10..13: position       (uint32, little-endian)
//   Byte 14..15: voltage        (uint16, little-endian)
//   Byte 16    : temperature    (uint8)
//   Byte 17    : hw_error       (uint8)

struct MotorFeedback
{
  uint8_t  moving{0U};
  uint8_t  moving_status{0U};
  uint16_t pwm{0U};
  uint16_t current{0U};
  uint32_t velocity{0U};
  uint32_t position{0U};
  uint16_t voltage{0U};
  uint8_t  temperature{0U};
  uint8_t  hw_error{0U};
};

// ─── Telemetry Packet (Jetson -> GUI, 36 bytes) ──────────────────────
//   Byte 0..17 : pan  MotorFeedback (18B)
//   Byte 18..35: tilt MotorFeedback (18B)

struct TelemetryPacket
{
  MotorFeedback pan{};
  MotorFeedback tilt{};
};

// ─── Byte-order Helpers ──────────────────────────────────────────────

inline uint16_t read_le16(const uint8_t * src)
{
  return static_cast<uint16_t>(src[0]) |
         static_cast<uint16_t>(static_cast<uint16_t>(src[1]) << 8U);
}

inline void write_le16(uint16_t value, uint8_t * dst)
{
  dst[0] = static_cast<uint8_t>(value & 0xFFU);
  dst[1] = static_cast<uint8_t>((value >> 8U) & 0xFFU);
}

inline uint32_t read_le32(const uint8_t * src)
{
  return static_cast<uint32_t>(src[0])        |
         (static_cast<uint32_t>(src[1]) << 8U)  |
         (static_cast<uint32_t>(src[2]) << 16U) |
         (static_cast<uint32_t>(src[3]) << 24U);
}

inline void write_le32(uint32_t value, uint8_t * dst)
{
  dst[0] = static_cast<uint8_t>(value & 0xFFU);
  dst[1] = static_cast<uint8_t>((value >> 8U) & 0xFFU);
  dst[2] = static_cast<uint8_t>((value >> 16U) & 0xFFU);
  dst[3] = static_cast<uint8_t>((value >> 24U) & 0xFFU);
}

// ─── Command Parsing (GUI -> Jetson) ─────────────────────────────────

inline CommandPacket parse_command(const uint8_t * data, std::size_t size)
{
  if (size < kCmdPacketSize) {
    throw std::runtime_error("invalid command packet size: expected 9 bytes");
  }
  CommandPacket cmd{};
  cmd.mode          = data[0];
  cmd.scan_button   = data[1];
  cmd.manual_button = data[2];
  cmd.pan_position  = read_le16(&data[3]);
  cmd.tilt_position = read_le16(&data[5]);
  cmd.scan_step     = data[7];
  cmd.manual_step   = data[8];
  return cmd;
}

inline std::array<uint8_t, kCmdPacketSize> build_command(const CommandPacket & cmd)
{
  std::array<uint8_t, kCmdPacketSize> pkt{};
  pkt[0] = cmd.mode;
  pkt[1] = cmd.scan_button;
  pkt[2] = cmd.manual_button;
  write_le16(cmd.pan_position,  &pkt[3]);
  write_le16(cmd.tilt_position, &pkt[5]);
  pkt[7] = cmd.scan_step;
  pkt[8] = cmd.manual_step;
  return pkt;
}

// ─── Motor Feedback Parsing ──────────────────────────────────────────

inline MotorFeedback parse_motor_feedback(const uint8_t * data)
{
  MotorFeedback fb{};
  fb.moving        = data[0];
  fb.moving_status = data[1];
  fb.pwm           = read_le16(&data[2]);
  fb.current       = read_le16(&data[4]);
  fb.velocity      = read_le32(&data[6]);
  fb.position      = read_le32(&data[10]);
  fb.voltage       = read_le16(&data[14]);
  fb.temperature   = data[16];
  fb.hw_error      = data[17];
  return fb;
}

inline void write_motor_feedback(const MotorFeedback & fb, uint8_t * dst)
{
  dst[0] = fb.moving;
  dst[1] = fb.moving_status;
  write_le16(fb.pwm,     &dst[2]);
  write_le16(fb.current, &dst[4]);
  write_le32(fb.velocity, &dst[6]);
  write_le32(fb.position, &dst[10]);
  write_le16(fb.voltage, &dst[14]);
  dst[16] = fb.temperature;
  dst[17] = fb.hw_error;
}

// ─── Telemetry Build / Parse (Jetson -> GUI) ─────────────────────────

inline TelemetryPacket parse_telemetry(const uint8_t * data, std::size_t size)
{
  if (size < kTlmPacketSize) {
    throw std::runtime_error("invalid telemetry packet size: expected 36 bytes");
  }
  TelemetryPacket tlm{};
  tlm.pan  = parse_motor_feedback(&data[0]);
  tlm.tilt = parse_motor_feedback(&data[kMotorFeedbackSize]);
  return tlm;
}

inline std::array<uint8_t, kTlmPacketSize> build_telemetry(const TelemetryPacket & tlm)
{
  std::array<uint8_t, kTlmPacketSize> pkt{};
  write_motor_feedback(tlm.pan,  &pkt[0]);
  write_motor_feedback(tlm.tilt, &pkt[kMotorFeedbackSize]);
  return pkt;
}

inline std::array<uint8_t, kTlmPacketSize> build_telemetry_from_raw(const uint8_t * raw)
{
  std::array<uint8_t, kTlmPacketSize> pkt{};
  std::memcpy(pkt.data(), raw, kTlmPacketSize);
  return pkt;
}

}  // namespace gui_interface

#endif  // GUI_INTERFACE__PROTOCOL_HPP_
