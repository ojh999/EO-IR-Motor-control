// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from sentinel_interfaces:msg/Detection2D.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/detection2_d.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__DETECTION2_D__TRAITS_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__DETECTION2_D__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "sentinel_interfaces/msg/detail/detection2_d__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace sentinel_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Detection2D & msg,
  std::ostream & out)
{
  out << "{";
  // member: class_name
  {
    out << "class_name: ";
    rosidl_generator_traits::value_to_yaml(msg.class_name, out);
    out << ", ";
  }

  // member: score
  {
    out << "score: ";
    rosidl_generator_traits::value_to_yaml(msg.score, out);
    out << ", ";
  }

  // member: x1
  {
    out << "x1: ";
    rosidl_generator_traits::value_to_yaml(msg.x1, out);
    out << ", ";
  }

  // member: y1
  {
    out << "y1: ";
    rosidl_generator_traits::value_to_yaml(msg.y1, out);
    out << ", ";
  }

  // member: x2
  {
    out << "x2: ";
    rosidl_generator_traits::value_to_yaml(msg.x2, out);
    out << ", ";
  }

  // member: y2
  {
    out << "y2: ";
    rosidl_generator_traits::value_to_yaml(msg.y2, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Detection2D & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: class_name
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "class_name: ";
    rosidl_generator_traits::value_to_yaml(msg.class_name, out);
    out << "\n";
  }

  // member: score
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "score: ";
    rosidl_generator_traits::value_to_yaml(msg.score, out);
    out << "\n";
  }

  // member: x1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x1: ";
    rosidl_generator_traits::value_to_yaml(msg.x1, out);
    out << "\n";
  }

  // member: y1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y1: ";
    rosidl_generator_traits::value_to_yaml(msg.y1, out);
    out << "\n";
  }

  // member: x2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x2: ";
    rosidl_generator_traits::value_to_yaml(msg.x2, out);
    out << "\n";
  }

  // member: y2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y2: ";
    rosidl_generator_traits::value_to_yaml(msg.y2, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Detection2D & msg, bool use_flow_style = false)
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
  const sentinel_interfaces::msg::Detection2D & msg,
  std::ostream & out, size_t indentation = 0)
{
  sentinel_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use sentinel_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const sentinel_interfaces::msg::Detection2D & msg)
{
  return sentinel_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<sentinel_interfaces::msg::Detection2D>()
{
  return "sentinel_interfaces::msg::Detection2D";
}

template<>
inline const char * name<sentinel_interfaces::msg::Detection2D>()
{
  return "sentinel_interfaces/msg/Detection2D";
}

template<>
struct has_fixed_size<sentinel_interfaces::msg::Detection2D>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<sentinel_interfaces::msg::Detection2D>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<sentinel_interfaces::msg::Detection2D>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__DETECTION2_D__TRAITS_HPP_
