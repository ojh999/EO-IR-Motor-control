#ifndef GUI_INTERFACE__PROTOCOL_HPP_
#define GUI_INTERFACE__PROTOCOL_HPP_

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace gui_interface
{

constexpr std::size_t kCmdModeChangeSize = 2;
constexpr std::size_t kCmdButtonSize = 4;  // [id, buttons, step_L, step_H]
constexpr std::size_t kTlmSystemStatusSize = 3;
constexpr std::size_t kMotorRawPayloadSize = 36;
constexpr std::size_t kTlmMotorSize = 37;  // 1 (header) + 36 (raw payload)
constexpr std::size_t kTlmDetectionSize = 10;
constexpr std::size_t kTlmFrameInfoSize = 9;

constexpr uint8_t kCmdModeChangeId = 0x01;
constexpr uint8_t kCmdButtonId = 0x02;
constexpr uint8_t kTlmSystemStatusId = 0x81;
constexpr uint8_t kTlmMotorId = 0x82;
constexpr uint8_t kTlmDetectionId = 0x83;
constexpr uint8_t kTlmFrameInfoId = 0x84;

enum SystemMode : uint8_t
{
  MODE_SCAN = 0,
  TRACKING = 1,
  MANUAL = 2,
};

struct ModeCommand
{
  uint8_t mode{0U};           // 0=Scan, 1=Tracking, 2=Manual
  std::size_t payload_offset{1U};
};

struct ButtonCommand
{
  uint8_t  buttons{0U};
  uint16_t step{0U};           // SCAN step (0~4095, 0=현재값 유지)
  std::size_t payload_offset{1U};
};

inline uint16_t read_le16(const uint8_t * src)
{
  return static_cast<uint16_t>(src[0]) |
         static_cast<uint16_t>(src[1] << 8U);
}

inline void write_le16(uint16_t value, uint8_t * dst)
{
  dst[0] = static_cast<uint8_t>(value & 0xFFU);
  dst[1] = static_cast<uint8_t>((value >> 8U) & 0xFFU);
}

inline float read_le_float32(const uint8_t * src)
{
  float value{};
  std::memcpy(&value, src, sizeof(float));
  return value;
}

inline void write_le_float32(float value, uint8_t * dst)
{
  std::memcpy(dst, &value, sizeof(float));
}

inline ModeCommand parse_mode_command(const uint8_t * data, std::size_t size)
{
  if (size < kCmdModeChangeSize) {
    throw std::runtime_error("invalid mode command packet size");
  }
  return ModeCommand{data[1], 1U};
}

inline ButtonCommand parse_button_command(const uint8_t * data, std::size_t size)
{
  if (size < kCmdButtonSize) {
    throw std::runtime_error("invalid button command packet size");
  }
  const uint16_t step = static_cast<uint16_t>(data[2]) |
                        (static_cast<uint16_t>(data[3]) << 8U);
  return ButtonCommand{data[1], step, 1U};
}

inline std::array<uint8_t, kTlmMotorSize> build_motor_telemetry_from_raw(const uint8_t * raw)
{
  std::array<uint8_t, kTlmMotorSize> packet{};
  packet[0] = kTlmMotorId;
  std::memcpy(&packet[1], raw, kMotorRawPayloadSize);
  return packet;
}

inline std::array<uint8_t, kTlmSystemStatusSize> build_system_status_packet(
  uint8_t system_mode,
  uint8_t system_status)
{
  std::array<uint8_t, kTlmSystemStatusSize> packet{};
  packet[0] = kTlmSystemStatusId;
  packet[1] = system_mode;
  packet[2] = system_status;
  return packet;
}

inline std::array<uint8_t, kTlmMotorSize> build_motor_telemetry_packet(
  uint16_t pan_deg,
  uint16_t pan_load,
  uint8_t pan_temp,
  uint8_t pan_err,
  uint16_t tilt_deg,
  uint16_t tilt_load,
  uint8_t tilt_temp,
  uint8_t tilt_err)
{
  std::array<uint8_t, kTlmMotorSize> packet{};
  packet[0] = kTlmMotorId;
  write_le16(pan_deg, &packet[1]);
  write_le16(pan_load, &packet[3]);
  packet[5] = pan_temp;
  packet[6] = pan_err;
  write_le16(tilt_deg, &packet[7]);
  write_le16(tilt_load, &packet[9]);
  packet[11] = tilt_temp;
  packet[12] = tilt_err;
  return packet;
}

inline std::array<uint8_t, kTlmDetectionSize> build_detection_packet(
  uint8_t det_count,
  uint16_t center_x,
  uint16_t center_y,
  uint16_t frame_w,
  uint16_t frame_h)
{
  std::array<uint8_t, kTlmDetectionSize> packet{};
  packet[0] = kTlmDetectionId;
  packet[1] = det_count;
  write_le16(center_x, &packet[2]);
  write_le16(center_y, &packet[4]);
  write_le16(frame_w, &packet[6]);
  write_le16(frame_h, &packet[8]);
  return packet;
}

inline std::array<uint8_t, kTlmFrameInfoSize> build_frame_info_packet(
  uint16_t frame_w,
  uint16_t frame_h,
  float fps)
{
  std::array<uint8_t, kTlmFrameInfoSize> packet{};
  packet[0] = kTlmFrameInfoId;
  write_le16(frame_w, &packet[1]);
  write_le16(frame_h, &packet[3]);
  write_le_float32(fps, &packet[5]);
  return packet;
}

}  // namespace gui_interface

#endif  // GUI_INTERFACE__PROTOCOL_HPP_
