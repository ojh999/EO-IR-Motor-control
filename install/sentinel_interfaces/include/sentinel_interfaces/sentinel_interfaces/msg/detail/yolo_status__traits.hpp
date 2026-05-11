// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sentinel_interfaces:msg/YoloStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/yolo_status.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__YOLO_STATUS__TRAITS_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__YOLO_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sentinel_interfaces/msg/detail/yolo_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace sentinel_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const YoloStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: enabled
  {
    out << "enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.enabled, out);
    out << ", ";
  }

  // member: model_loaded
  {
    out << "model_loaded: ";
    rosidl_generator_traits::value_to_yaml(msg.model_loaded, out);
    out << ", ";
  }

  // member: conf_threshold
  {
    out << "conf_threshold: ";
    rosidl_generator_traits::value_to_yaml(msg.conf_threshold, out);
    out << ", ";
  }

  // member: last_error
  {
    out << "last_error: ";
    rosidl_generator_traits::value_to_yaml(msg.last_error, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const YoloStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: enabled
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "enabled: ";
    rosidl_generator_traits::value_to_yaml(msg.enabled, out);
    out << "\n";
  }

  // member: model_loaded
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "model_loaded: ";
    rosidl_generator_traits::value_to_yaml(msg.model_loaded, out);
    out << "\n";
  }

  // member: conf_threshold
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "conf_threshold: ";
    rosidl_generator_traits::value_to_yaml(msg.conf_threshold, out);
    out << "\n";
  }

  // member: last_error
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "last_error: ";
    rosidl_generator_traits::value_to_yaml(msg.last_error, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const YoloStatus & msg, bool use_flow_style = false)
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
  const sentinel_interfaces::msg::YoloStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  sentinel_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sentinel_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const sentinel_interfaces::msg::YoloStatus & msg)
{
  return sentinel_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sentinel_interfaces::msg::YoloStatus>()
{
  return "sentinel_interfaces::msg::YoloStatus";
}

template<>
inline const char * name<sentinel_interfaces::msg::YoloStatus>()
{
  return "sentinel_interfaces/msg/YoloStatus";
}

template<>
struct has_fixed_size<sentinel_interfaces::msg::YoloStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<sentinel_interfaces::msg::YoloStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<sentinel_interfaces::msg::YoloStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__YOLO_STATUS__TRAITS_HPP_
