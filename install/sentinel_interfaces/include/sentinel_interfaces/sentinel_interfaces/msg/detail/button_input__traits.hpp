// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sentinel_interfaces:msg/ButtonInput.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/button_input.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__BUTTON_INPUT__TRAITS_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__BUTTON_INPUT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sentinel_interfaces/msg/detail/button_input__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace sentinel_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const ButtonInput & msg,
  std::ostream & out)
{
  out << "{";
  // member: buttons
  {
    out << "buttons: ";
    rosidl_generator_traits::value_to_yaml(msg.buttons, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ButtonInput & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: buttons
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "buttons: ";
    rosidl_generator_traits::value_to_yaml(msg.buttons, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ButtonInput & msg, bool use_flow_style = false)
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
  const sentinel_interfaces::msg::ButtonInput & msg,
  std::ostream & out, size_t indentation = 0)
{
  sentinel_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sentinel_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const sentinel_interfaces::msg::ButtonInput & msg)
{
  return sentinel_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sentinel_interfaces::msg::ButtonInput>()
{
  return "sentinel_interfaces::msg::ButtonInput";
}

template<>
inline const char * name<sentinel_interfaces::msg::ButtonInput>()
{
  return "sentinel_interfaces/msg/ButtonInput";
}

template<>
struct has_fixed_size<sentinel_interfaces::msg::ButtonInput>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<sentinel_interfaces::msg::ButtonInput>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<sentinel_interfaces::msg::ButtonInput>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__BUTTON_INPUT__TRAITS_HPP_
