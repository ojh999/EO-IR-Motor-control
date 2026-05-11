// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sentinel_interfaces:msg/ButtonInput.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/button_input.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__BUTTON_INPUT__BUILDER_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__BUTTON_INPUT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sentinel_interfaces/msg/detail/button_input__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sentinel_interfaces
{

namespace msg
{

namespace builder
{

class Init_ButtonInput_buttons
{
public:
  Init_ButtonInput_buttons()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::sentinel_interfaces::msg::ButtonInput buttons(::sentinel_interfaces::msg::ButtonInput::_buttons_type arg)
  {
    msg_.buttons = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sentinel_interfaces::msg::ButtonInput msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sentinel_interfaces::msg::ButtonInput>()
{
  return sentinel_interfaces::msg::builder::Init_ButtonInput_buttons();
}

}  // namespace sentinel_interfaces

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__BUTTON_INPUT__BUILDER_HPP_
