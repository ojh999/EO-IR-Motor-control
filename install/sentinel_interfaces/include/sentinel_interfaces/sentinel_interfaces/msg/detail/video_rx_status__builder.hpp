// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sentinel_interfaces:msg/VideoRxStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/video_rx_status.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__VIDEO_RX_STATUS__BUILDER_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__VIDEO_RX_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sentinel_interfaces/msg/detail/video_rx_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sentinel_interfaces
{

namespace msg
{

namespace builder
{

class Init_VideoRxStatus_published_frames
{
public:
  explicit Init_VideoRxStatus_published_frames(::sentinel_interfaces::msg::VideoRxStatus & msg)
  : msg_(msg)
  {}
  ::sentinel_interfaces::msg::VideoRxStatus published_frames(::sentinel_interfaces::msg::VideoRxStatus::_published_frames_type arg)
  {
    msg_.published_frames = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sentinel_interfaces::msg::VideoRxStatus msg_;
};

class Init_VideoRxStatus_video_path
{
public:
  explicit Init_VideoRxStatus_video_path(::sentinel_interfaces::msg::VideoRxStatus & msg)
  : msg_(msg)
  {}
  Init_VideoRxStatus_published_frames video_path(::sentinel_interfaces::msg::VideoRxStatus::_video_path_type arg)
  {
    msg_.video_path = std::move(arg);
    return Init_VideoRxStatus_published_frames(msg_);
  }

private:
  ::sentinel_interfaces::msg::VideoRxStatus msg_;
};

class Init_VideoRxStatus_message
{
public:
  explicit Init_VideoRxStatus_message(::sentinel_interfaces::msg::VideoRxStatus & msg)
  : msg_(msg)
  {}
  Init_VideoRxStatus_video_path message(::sentinel_interfaces::msg::VideoRxStatus::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_VideoRxStatus_video_path(msg_);
  }

private:
  ::sentinel_interfaces::msg::VideoRxStatus msg_;
};

class Init_VideoRxStatus_is_ok
{
public:
  explicit Init_VideoRxStatus_is_ok(::sentinel_interfaces::msg::VideoRxStatus & msg)
  : msg_(msg)
  {}
  Init_VideoRxStatus_message is_ok(::sentinel_interfaces::msg::VideoRxStatus::_is_ok_type arg)
  {
    msg_.is_ok = std::move(arg);
    return Init_VideoRxStatus_message(msg_);
  }

private:
  ::sentinel_interfaces::msg::VideoRxStatus msg_;
};

class Init_VideoRxStatus_stamp
{
public:
  Init_VideoRxStatus_stamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VideoRxStatus_is_ok stamp(::sentinel_interfaces::msg::VideoRxStatus::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_VideoRxStatus_is_ok(msg_);
  }

private:
  ::sentinel_interfaces::msg::VideoRxStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sentinel_interfaces::msg::VideoRxStatus>()
{
  return sentinel_interfaces::msg::builder::Init_VideoRxStatus_stamp();
}

}  // namespace sentinel_interfaces

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__VIDEO_RX_STATUS__BUILDER_HPP_
