#ifndef SENTINEL_MOTOR__PACKET_DEF_HPP_
#define SENTINEL_MOTOR__PACKET_DEF_HPP_

#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

namespace sentinel_motor
{

// ─── Packet Sizes ────────────────────────────────────────────────────
// Thor → Zybo: 8B [mode][btn][pan(2)][tilt(2)][scan_step][manual_step]
// Zybo → Thor: 36B [PAN(18B)][TILT(18B)]
constexpr std::size_t kCommandPacketSize  = 8;   // Thor → Zybo
constexpr std::size_t kMotorFeedbackSize  = 18;
constexpr std::size_t kFeedbackPacketSize = 36;  // Zybo → Thor (18B × 2)

// ─── Mode ────────────────────────────────────────────────────────────
// GUI: auto_manual(0/1) + tracking(0/1) 조합
// gui_interface 노드가 아래 mode_cmd(0/1/2)로 변환 후 /system/mode 발행
constexpr uint8_t kModeScan   = 0;  // auto_manual=0, tracking=0
constexpr uint8_t kModeManual = 1;  // auto_manual=1, tracking=0
constexpr uint8_t kModeTrack  = 2;  // auto_manual=1, tracking=1

// ─── Button Bitmask (MANUAL 모드 전용) ───────────────────────────────
// GUI BUTTON_L/R/U/D와 동일하게 맞춰야 함
constexpr uint8_t kButtonPanMinus  = 0x01;  // 팬 - (좌)
constexpr uint8_t kButtonPanPlus   = 0x02;  // 팬 + (우)
constexpr uint8_t kButtonTiltPlus  = 0x04;  // 틸트 + (업)
constexpr uint8_t kButtonTiltMinus = 0x08;  // 틸트 - (다운)
constexpr uint8_t kButtonCenter    = 0x10;  // 홈/센터

// ─── Command Packet (Thor → Zybo, 8B) ───────────────────────────────
//   Byte 0    : mode        (uint8, 0=SCAN / 1=MANUAL / 2=TRACK)
//   Byte 1    : btn         (uint8, 버튼 비트마스크, MANUAL 모드 전용)
//   Byte 2..3 : pan         (uint16, LE, 0~4095)
//   Byte 4..5 : tilt        (uint16, LE, 0~4095)
//   Byte 6    : scan_step   (uint8, 1~10)
//   Byte 7    : manual_step (uint8, 1~10)
//
// 모드별 유효 필드:
//   SCAN   : mode=0, btn=0,   pan=0,      tilt=0,      scan_step, manual_step
//   MANUAL : mode=1, btn=비트마스크, pan=0, tilt=0,    scan_step, manual_step
//   TRACK  : mode=2, btn=0,   pan=step값, tilt=step값, scan_step, manual_step

struct CommandPacket
{
  uint8_t  mode{kModeScan};
  uint8_t  btn{0};
  uint16_t pan{0};
  uint16_t tilt{0};
  uint8_t  scan_step{1};
  uint8_t  man_step{1};
};

// ─── Motor Feedback (18B per motor) ──────────────────────────────────
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

// ─── Feedback Packet (Zybo → Thor, 36B) ──────────────────────────────
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
  return static_cast<uint32_t>(src[0])         |
         (static_cast<uint32_t>(src[1]) << 8U)  |
         (static_cast<uint32_t>(src[2]) << 16U) |
         (static_cast<uint32_t>(src[3]) << 24U);
}

// ─── Command Serialize / Parse ───────────────────────────────────────

inline std::array<uint8_t, kCommandPacketSize> serialize_command(const CommandPacket & cmd)
{
  std::array<uint8_t, kCommandPacketSize> packet{};
  packet[0] = cmd.mode;
  packet[1] = cmd.btn;
  write_le16(cmd.pan,  &packet[2]);
  write_le16(cmd.tilt, &packet[4]);
  packet[6] = cmd.scan_step;
  packet[7] = cmd.man_step;
  return packet;
}

inline CommandPacket parse_command(const uint8_t * data, std::size_t size)
{
  if (size < kCommandPacketSize) {
    throw std::runtime_error("invalid command packet size: expected 8 bytes");
  }
  CommandPacket cmd{};
  cmd.mode      = data[0];
  cmd.btn       = data[1];
  cmd.pan       = read_le16(&data[2]);
  cmd.tilt      = read_le16(&data[4]);
  cmd.scan_step = data[6];
  cmd.man_step  = data[7];
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
  dst[6]  = static_cast<uint8_t>(fb.velocity & 0xFFU);
  dst[7]  = static_cast<uint8_t>((fb.velocity >> 8U)  & 0xFFU);
  dst[8]  = static_cast<uint8_t>((fb.velocity >> 16U) & 0xFFU);
  dst[9]  = static_cast<uint8_t>((fb.velocity >> 24U) & 0xFFU);
  dst[10] = static_cast<uint8_t>(fb.position & 0xFFU);
  dst[11] = static_cast<uint8_t>((fb.position >> 8U)  & 0xFFU);
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