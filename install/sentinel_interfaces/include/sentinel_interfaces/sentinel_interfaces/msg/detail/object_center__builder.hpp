// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sentinel_interfaces:msg/ObjectCenter.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/object_center.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__OBJECT_CENTER__BUILDER_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__OBJECT_CENTER__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sentinel_interfaces/msg/detail/object_center__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sentinel_interfaces
{

namespace msg
{

namespace builder
{

class Init_ObjectCenter_center_y
{
public:
  explicit Init_ObjectCenter_center_y(::sentinel_interfaces::msg::ObjectCenter & msg)
  : msg_(msg)
  {}
  ::sentinel_interfaces::msg::ObjectCenter center_y(::sentinel_interfaces::msg::ObjectCenter::_center_y_type arg)
  {
    msg_.center_y = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sentinel_interfaces::msg::ObjectCenter msg_;
};

class Init_ObjectCenter_center_x
{
public:
  Init_ObjectCenter_center_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ObjectCenter_center_y center_x(::sentinel_interfaces::msg::ObjectCenter::_center_x_type arg)
  {
    msg_.center_x = std::move(arg);
    return Init_ObjectCenter_center_y(msg_);
  }

private:
  ::sentinel_interfaces::msg::ObjectCenter msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sentinel_interfaces::msg::ObjectCenter>()
{
  return sentinel_interfaces::msg::builder::Init_ObjectCenter_center_x();
}

}  // namespace sentinel_interfaces

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__OBJECT_CENTER__BUILDER_HPP_
