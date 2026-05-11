// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sentinel_interfaces:msg/Detection.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/detection.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__DETECTION__TRAITS_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__DETECTION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sentinel_interfaces/msg/detail/detection__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace sentinel_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Detection & msg,
  std::ostream & out)
{
  out << "{";
  // member: cx
  {
    out << "cx: ";
    rosidl_generator_traits::value_to_yaml(msg.cx, out);
    out << ", ";
  }

  // member: cy
  {
    out << "cy: ";
    rosidl_generator_traits::value_to_yaml(msg.cy, out);
    out << ", ";
  }

  // member: frame_w
  {
    out << "frame_w: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_w, out);
    out << ", ";
  }

  // member: frame_h
  {
    out << "frame_h: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_h, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Detection & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: cx
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cx: ";
    rosidl_generator_traits::value_to_yaml(msg.cx, out);
    out << "\n";
  }

  // member: cy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "cy: ";
    rosidl_generator_traits::value_to_yaml(msg.cy, out);
    out << "\n";
  }

  // member: frame_w
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "frame_w: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_w, out);
    out << "\n";
  }

  // member: frame_h
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "frame_h: ";
    rosidl_generator_traits::value_to_yaml(msg.frame_h, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Detection & msg, bool use_flow_style = false)
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
  const sentinel_interfaces::msg::Detection & msg,
  std::ostream & out, size_t indentation = 0)
{
  sentinel_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sentinel_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const sentinel_interfaces::msg::Detection & msg)
{
  return sentinel_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sentinel_interfaces::msg::Detection>()
{
  return "sentinel_interfaces::msg::Detection";
}

template<>
inline const char * name<sentinel_interfaces::msg::Detection>()
{
  return "sentinel_interfaces/msg/Detection";
}

template<>
struct has_fixed_size<sentinel_interfaces::msg::Detection>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<sentinel_interfaces::msg::Detection>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<sentinel_interfaces::msg::Detection>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__DETECTION__TRAITS_HPP_
