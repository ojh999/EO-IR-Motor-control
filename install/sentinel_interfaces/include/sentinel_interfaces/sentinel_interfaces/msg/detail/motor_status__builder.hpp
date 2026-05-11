// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sentinel_interfaces:msg/MotorStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/motor_status.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__MOTOR_STATUS__BUILDER_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__MOTOR_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sentinel_interfaces/msg/detail/motor_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sentinel_interfaces
{

namespace msg
{

namespace builder
{

class Init_MotorStatus_tilt
{
public:
  explicit Init_MotorStatus_tilt(::sentinel_interfaces::msg::MotorStatus & msg)
  : msg_(msg)
  {}
  ::sentinel_interfaces::msg::MotorStatus tilt(::sentinel_interfaces::msg::MotorStatus::_tilt_type arg)
  {
    msg_.tilt = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sentinel_interfaces::msg::MotorStatus msg_;
};

class Init_MotorStatus_pan
{
public:
  Init_MotorStatus_pan()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorStatus_tilt pan(::sentinel_interfaces::msg::MotorStatus::_pan_type arg)
  {
    msg_.pan = std::move(arg);
    return Init_MotorStatus_tilt(msg_);
  }

private:
  ::sentinel_interfaces::msg::MotorStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sentinel_interfaces::msg::MotorStatus>()
{
  return sentinel_interfaces::msg::builder::Init_MotorStatus_pan();
}

}  // namespace sentinel_interfaces

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__MOTOR_STATUS__BUILDER_HPP_
