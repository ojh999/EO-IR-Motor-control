// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sentinel_interfaces:msg/SingleMotorStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/single_motor_status.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__SINGLE_MOTOR_STATUS__BUILDER_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__SINGLE_MOTOR_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sentinel_interfaces/msg/detail/single_motor_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sentinel_interfaces
{

namespace msg
{

namespace builder
{

class Init_SingleMotorStatus_hw_error
{
public:
  explicit Init_SingleMotorStatus_hw_error(::sentinel_interfaces::msg::SingleMotorStatus & msg)
  : msg_(msg)
  {}
  ::sentinel_interfaces::msg::SingleMotorStatus hw_error(::sentinel_interfaces::msg::SingleMotorStatus::_hw_error_type arg)
  {
    msg_.hw_error = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sentinel_interfaces::msg::SingleMotorStatus msg_;
};

class Init_SingleMotorStatus_temperature
{
public:
  explicit Init_SingleMotorStatus_temperature(::sentinel_interfaces::msg::SingleMotorStatus & msg)
  : msg_(msg)
  {}
  Init_SingleMotorStatus_hw_error temperature(::sentinel_interfaces::msg::SingleMotorStatus::_temperature_type arg)
  {
    msg_.temperature = std::move(arg);
    return Init_SingleMotorStatus_hw_error(msg_);
  }

private:
  ::sentinel_interfaces::msg::SingleMotorStatus msg_;
};

class Init_SingleMotorStatus_load
{
public:
  explicit Init_SingleMotorStatus_load(::sentinel_interfaces::msg::SingleMotorStatus & msg)
  : msg_(msg)
  {}
  Init_SingleMotorStatus_temperature load(::sentinel_interfaces::msg::SingleMotorStatus::_load_type arg)
  {
    msg_.load = std::move(arg);
    return Init_SingleMotorStatus_temperature(msg_);
  }

private:
  ::sentinel_interfaces::msg::SingleMotorStatus msg_;
};

class Init_SingleMotorStatus_position
{
public:
  Init_SingleMotorStatus_position()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SingleMotorStatus_load position(::sentinel_interfaces::msg::SingleMotorStatus::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_SingleMotorStatus_load(msg_);
  }

private:
  ::sentinel_interfaces::msg::SingleMotorStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sentinel_interfaces::msg::SingleMotorStatus>()
{
  return sentinel_interfaces::msg::builder::Init_SingleMotorStatus_position();
}

}  // namespace sentinel_interfaces

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__SINGLE_MOTOR_STATUS__BUILDER_HPP_
