// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sentinel_interfaces:msg/SingleMotorStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/single_motor_status.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__SINGLE_MOTOR_STATUS__TRAITS_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__SINGLE_MOTOR_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sentinel_interfaces/msg/detail/single_motor_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace sentinel_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const SingleMotorStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: position
  {
    out << "position: ";
    rosidl_generator_traits::value_to_yaml(msg.position, out);
    out << ", ";
  }

  // member: load
  {
    out << "load: ";
    rosidl_generator_traits::value_to_yaml(msg.load, out);
    out << ", ";
  }

  // member: temperature
  {
    out << "temperature: ";
    rosidl_generator_traits::value_to_yaml(msg.temperature, out);
    out << ", ";
  }

  // member: hw_error
  {
    out << "hw_error: ";
    rosidl_generator_traits::value_to_yaml(msg.hw_error, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SingleMotorStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position: ";
    rosidl_generator_traits::value_to_yaml(msg.position, out);
    out << "\n";
  }

  // member: load
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "load: ";
    rosidl_generator_traits::value_to_yaml(msg.load, out);
    out << "\n";
  }

  // member: temperature
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "temperature: ";
    rosidl_generator_traits::value_to_yaml(msg.temperature, out);
    out << "\n";
  }

  // member: hw_error
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "hw_error: ";
    rosidl_generator_traits::value_to_yaml(msg.hw_error, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SingleMotorStatus & msg, bool use_flow_style = false)
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
  const sentinel_interfaces::msg::SingleMotorStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  sentinel_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sentinel_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const sentinel_interfaces::msg::SingleMotorStatus & msg)
{
  return sentinel_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sentinel_interfaces::msg::SingleMotorStatus>()
{
  return "sentinel_interfaces::msg::SingleMotorStatus";
}

template<>
inline const char * name<sentinel_interfaces::msg::SingleMotorStatus>()
{
  return "sentinel_interfaces/msg/SingleMotorStatus";
}

template<>
struct has_fixed_size<sentinel_interfaces::msg::SingleMotorStatus>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<sentinel_interfaces::msg::SingleMotorStatus>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<sentinel_interfaces::msg::SingleMotorStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__SINGLE_MOTOR_STATUS__TRAITS_HPP_
