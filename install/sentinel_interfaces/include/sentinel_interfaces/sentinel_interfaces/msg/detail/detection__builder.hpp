// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sentinel_interfaces:msg/Detection.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/detection.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__DETECTION__BUILDER_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__DETECTION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sentinel_interfaces/msg/detail/detection__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sentinel_interfaces
{

namespace msg
{

namespace builder
{

class Init_Detection_frame_h
{
public:
  explicit Init_Detection_frame_h(::sentinel_interfaces::msg::Detection & msg)
  : msg_(msg)
  {}
  ::sentinel_interfaces::msg::Detection frame_h(::sentinel_interfaces::msg::Detection::_frame_h_type arg)
  {
    msg_.frame_h = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sentinel_interfaces::msg::Detection msg_;
};

class Init_Detection_frame_w
{
public:
  explicit Init_Detection_frame_w(::sentinel_interfaces::msg::Detection & msg)
  : msg_(msg)
  {}
  Init_Detection_frame_h frame_w(::sentinel_interfaces::msg::Detection::_frame_w_type arg)
  {
    msg_.frame_w = std::move(arg);
    return Init_Detection_frame_h(msg_);
  }

private:
  ::sentinel_interfaces::msg::Detection msg_;
};

class Init_Detection_cy
{
public:
  explicit Init_Detection_cy(::sentinel_interfaces::msg::Detection & msg)
  : msg_(msg)
  {}
  Init_Detection_frame_w cy(::sentinel_interfaces::msg::Detection::_cy_type arg)
  {
    msg_.cy = std::move(arg);
    return Init_Detection_frame_w(msg_);
  }

private:
  ::sentinel_interfaces::msg::Detection msg_;
};

class Init_Detection_cx
{
public:
  Init_Detection_cx()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Detection_cy cx(::sentinel_interfaces::msg::Detection::_cx_type arg)
  {
    msg_.cx = std::move(arg);
    return Init_Detection_cy(msg_);
  }

private:
  ::sentinel_interfaces::msg::Detection msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sentinel_interfaces::msg::Detection>()
{
  return sentinel_interfaces::msg::builder::Init_Detection_cx();
}

}  // namespace sentinel_interfaces

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__DETECTION__BUILDER_HPP_
