// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sentinel_interfaces:msg/MotorAngle.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/motor_angle.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__MOTOR_ANGLE__BUILDER_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__MOTOR_ANGLE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sentinel_interfaces/msg/detail/motor_angle__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sentinel_interfaces
{

namespace msg
{

namespace builder
{

class Init_MotorAngle_tilt
{
public:
  explicit Init_MotorAngle_tilt(::sentinel_interfaces::msg::MotorAngle & msg)
  : msg_(msg)
  {}
  ::sentinel_interfaces::msg::MotorAngle tilt(::sentinel_interfaces::msg::MotorAngle::_tilt_type arg)
  {
    msg_.tilt = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sentinel_interfaces::msg::MotorAngle msg_;
};

class Init_MotorAngle_pan
{
public:
  Init_MotorAngle_pan()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MotorAngle_tilt pan(::sentinel_interfaces::msg::MotorAngle::_pan_type arg)
  {
    msg_.pan = std::move(arg);
    return Init_MotorAngle_tilt(msg_);
  }

private:
  ::sentinel_interfaces::msg::MotorAngle msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sentinel_interfaces::msg::MotorAngle>()
{
  return sentinel_interfaces::msg::builder::Init_MotorAngle_pan();
}

}  // namespace sentinel_interfaces

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__MOTOR_ANGLE__BUILDER_HPP_
