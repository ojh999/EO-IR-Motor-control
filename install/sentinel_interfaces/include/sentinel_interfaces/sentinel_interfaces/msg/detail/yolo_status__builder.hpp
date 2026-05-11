// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sentinel_interfaces:msg/YoloStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/yolo_status.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__YOLO_STATUS__BUILDER_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__YOLO_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sentinel_interfaces/msg/detail/yolo_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sentinel_interfaces
{

namespace msg
{

namespace builder
{

class Init_YoloStatus_last_error
{
public:
  explicit Init_YoloStatus_last_error(::sentinel_interfaces::msg::YoloStatus & msg)
  : msg_(msg)
  {}
  ::sentinel_interfaces::msg::YoloStatus last_error(::sentinel_interfaces::msg::YoloStatus::_last_error_type arg)
  {
    msg_.last_error = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sentinel_interfaces::msg::YoloStatus msg_;
};

class Init_YoloStatus_conf_threshold
{
public:
  explicit Init_YoloStatus_conf_threshold(::sentinel_interfaces::msg::YoloStatus & msg)
  : msg_(msg)
  {}
  Init_YoloStatus_last_error conf_threshold(::sentinel_interfaces::msg::YoloStatus::_conf_threshold_type arg)
  {
    msg_.conf_threshold = std::move(arg);
    return Init_YoloStatus_last_error(msg_);
  }

private:
  ::sentinel_interfaces::msg::YoloStatus msg_;
};

class Init_YoloStatus_model_loaded
{
public:
  explicit Init_YoloStatus_model_loaded(::sentinel_interfaces::msg::YoloStatus & msg)
  : msg_(msg)
  {}
  Init_YoloStatus_conf_threshold model_loaded(::sentinel_interfaces::msg::YoloStatus::_model_loaded_type arg)
  {
    msg_.model_loaded = std::move(arg);
    return Init_YoloStatus_conf_threshold(msg_);
  }

private:
  ::sentinel_interfaces::msg::YoloStatus msg_;
};

class Init_YoloStatus_enabled
{
public:
  Init_YoloStatus_enabled()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_YoloStatus_model_loaded enabled(::sentinel_interfaces::msg::YoloStatus::_enabled_type arg)
  {
    msg_.enabled = std::move(arg);
    return Init_YoloStatus_model_loaded(msg_);
  }

private:
  ::sentinel_interfaces::msg::YoloStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sentinel_interfaces::msg::YoloStatus>()
{
  return sentinel_interfaces::msg::builder::Init_YoloStatus_enabled();
}

}  // namespace sentinel_interfaces

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__YOLO_STATUS__BUILDER_HPP_
