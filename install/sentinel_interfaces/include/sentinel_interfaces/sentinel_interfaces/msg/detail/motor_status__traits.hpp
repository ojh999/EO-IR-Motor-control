// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sentinel_interfaces:msg/MotorStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/motor_status.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__MOTOR_STATUS__TRAITS_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__MOTOR_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sentinel_interfaces/msg/detail/motor_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'pan'
// Member 'tilt'
#include "sentinel_interfaces/msg/detail/single_motor_status__traits.hpp"

namespace sentinel_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const MotorStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: pan
  {
    out << "pan: ";
    to_flow_style_yaml(msg.pan, out);
    out << ", ";
  }

  // member: tilt
  {
    out << "tilt: ";
    to_flow_style_yaml(msg.tilt, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const MotorStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: pan
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pan:\n";
    to_block_style_yaml(msg.pan, out, indentation + 2);
  }

  // member: tilt
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "tilt:\n";
    to_block_style_yaml(msg.tilt, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const MotorStatus & msg, bool use_flow_style = false)
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
  const sentinel_interfaces::msg::MotorStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  sentinel_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sentinel_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const sentinel_interfaces::msg::MotorStatus & msg)
{
  return sentinel_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sentinel_interfaces::msg::MotorStatus>()
{
  return "sentinel_interfaces::msg::MotorStatus";
}

template<>
inline const char * name<sentinel_interfaces::msg::MotorStatus>()
{
  return "sentinel_interfaces/msg/MotorStatus";
}

template<>
struct has_fixed_size<sentinel_interfaces::msg::MotorStatus>
  : std::integral_constant<bool, has_fixed_size<sentinel_interfaces::msg::SingleMotorStatus>::value> {};

template<>
struct has_bounded_size<sentinel_interfaces::msg::MotorStatus>
  : std::integral_constant<bool, has_bounded_size<sentinel_interfaces::msg::SingleMotorStatus>::value> {};

template<>
struct is_message<sentinel_interfaces::msg::MotorStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__MOTOR_STATUS__TRAITS_HPP_
