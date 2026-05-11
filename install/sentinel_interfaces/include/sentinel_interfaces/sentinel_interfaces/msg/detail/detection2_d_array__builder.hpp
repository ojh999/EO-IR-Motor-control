// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sentinel_interfaces:msg/Detection2DArray.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/detection2_d_array.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__DETECTION2_D_ARRAY__BUILDER_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__DETECTION2_D_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sentinel_interfaces/msg/detail/detection2_d_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sentinel_interfaces
{

namespace msg
{

namespace builder
{

class Init_Detection2DArray_detections
{
public:
  explicit Init_Detection2DArray_detections(::sentinel_interfaces::msg::Detection2DArray & msg)
  : msg_(msg)
  {}
  ::sentinel_interfaces::msg::Detection2DArray detections(::sentinel_interfaces::msg::Detection2DArray::_detections_type arg)
  {
    msg_.detections = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sentinel_interfaces::msg::Detection2DArray msg_;
};

class Init_Detection2DArray_frame_id
{
public:
  explicit Init_Detection2DArray_frame_id(::sentinel_interfaces::msg::Detection2DArray & msg)
  : msg_(msg)
  {}
  Init_Detection2DArray_detections frame_id(::sentinel_interfaces::msg::Detection2DArray::_frame_id_type arg)
  {
    msg_.frame_id = std::move(arg);
    return Init_Detection2DArray_detections(msg_);
  }

private:
  ::sentinel_interfaces::msg::Detection2DArray msg_;
};

class Init_Detection2DArray_stamp
{
public:
  Init_Detection2DArray_stamp()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Detection2DArray_frame_id stamp(::sentinel_interfaces::msg::Detection2DArray::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return Init_Detection2DArray_frame_id(msg_);
  }

private:
  ::sentinel_interfaces::msg::Detection2DArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::sentinel_interfaces::msg::Detection2DArray>()
{
  return sentinel_interfaces::msg::builder::Init_Detection2DArray_stamp();
}

}  // namespace sentinel_interfaces

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__DETECTION2_D_ARRAY__BUILDER_HPP_
