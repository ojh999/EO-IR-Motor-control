// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sentinel_interfaces:msg/VideoRxStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/video_rx_status.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__VIDEO_RX_STATUS__TRAITS_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__VIDEO_RX_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sentinel_interfaces/msg/detail/video_rx_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace sentinel_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const VideoRxStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
    out << ", ";
  }

  // member: is_ok
  {
    out << "is_ok: ";
    rosidl_generator_traits::value_to_yaml(msg.is_ok, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << ", ";
  }

  // member: video_path
  {
    out << "video_path: ";
    rosidl_generator_traits::value_to_yaml(msg.video_path, out);
    out << ", ";
  }

  // member: published_frames
  {
    out << "published_frames: ";
    rosidl_generator_traits::value_to_yaml(msg.published_frames, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const VideoRxStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }

  // member: is_ok
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_ok: ";
    rosidl_generator_traits::value_to_yaml(msg.is_ok, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }

  // member: video_path
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "video_path: ";
    rosidl_generator_traits::value_to_yaml(msg.video_path, out);
    out << "\n";
  }

  // member: published_frames
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "published_frames: ";
    rosidl_generator_traits::value_to_yaml(msg.published_frames, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const VideoRxStatus & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace sentinel_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use sentinel_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const sentinel_interfaces::msg::VideoRxStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  sentinel_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sentinel_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const sentinel_interfaces::msg::VideoRxStatus & msg)
{
  return sentinel_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sentinel_interfaces::msg::VideoRxStatus>()
{
  return "sentinel_interfaces::msg::VideoRxStatus";
}

template<>
inline const char * name<sentinel_interfaces::msg::VideoRxStatus>()
{
  return "sentinel_interfaces/msg/VideoRxStatus";
}

template<>
struct has_fixed_size<sentinel_interfaces::msg::VideoRxStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<sentinel_interfaces::msg::VideoRxStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<sentinel_interfaces::msg::VideoRxStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__VIDEO_RX_STATUS__TRAITS_HPP_
