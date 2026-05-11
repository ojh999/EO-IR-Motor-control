// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sentinel_interfaces:msg/YoloStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/yolo_status.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__YOLO_STATUS__STRUCT_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__YOLO_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__sentinel_interfaces__msg__YoloStatus __attribute__((deprecated))
#else
# define DEPRECATED__sentinel_interfaces__msg__YoloStatus __declspec(deprecated)
#endif

namespace sentinel_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct YoloStatus_
{
  using Type = YoloStatus_<ContainerAllocator>;

  explicit YoloStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->enabled = false;
      this->model_loaded = false;
      this->conf_threshold = 0.0f;
      this->last_error = "";
    }
  }

  explicit YoloStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : last_error(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->enabled = false;
      this->model_loaded = false;
      this->conf_threshold = 0.0f;
      this->last_error = "";
    }
  }

  // field types and members
  using _enabled_type =
    bool;
  _enabled_type enabled;
  using _model_loaded_type =
    bool;
  _model_loaded_type model_loaded;
  using _conf_threshold_type =
    float;
  _conf_threshold_type conf_threshold;
  using _last_error_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _last_error_type last_error;

  // setters for named parameter idiom
  Type & set__enabled(
    const bool & _arg)
  {
    this->enabled = _arg;
    return *this;
  }
  Type & set__model_loaded(
    const bool & _arg)
  {
    this->model_loaded = _arg;
    return *this;
  }
  Type & set__conf_threshold(
    const float & _arg)
  {
    this->conf_threshold = _arg;
    return *this;
  }
  Type & set__last_error(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->last_error = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sentinel_interfaces::msg::YoloStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const sentinel_interfaces::msg::YoloStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sentinel_interfaces::msg::YoloStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sentinel_interfaces::msg::YoloStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sentinel_interfaces::msg::YoloStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sentinel_interfaces::msg::YoloStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sentinel_interfaces::msg::YoloStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sentinel_interfaces::msg::YoloStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sentinel_interfaces::msg::YoloStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sentinel_interfaces::msg::YoloStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sentinel_interfaces__msg__YoloStatus
    std::shared_ptr<sentinel_interfaces::msg::YoloStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sentinel_interfaces__msg__YoloStatus
    std::shared_ptr<sentinel_interfaces::msg::YoloStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const YoloStatus_ & other) const
  {
    if (this->enabled != other.enabled) {
      return false;
    }
    if (this->model_loaded != other.model_loaded) {
      return false;
    }
    if (this->conf_threshold != other.conf_threshold) {
      return false;
    }
    if (this->last_error != other.last_error) {
      return false;
    }
    return true;
  }
  bool operator!=(const YoloStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct YoloStatus_

// alias to use template instance with default allocator
using YoloStatus =
  sentinel_interfaces::msg::YoloStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sentinel_interfaces

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__YOLO_STATUS__STRUCT_HPP_
