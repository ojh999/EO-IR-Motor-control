// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sentinel_interfaces:msg/MotorAngle.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/motor_angle.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__MOTOR_ANGLE__STRUCT_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__MOTOR_ANGLE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__sentinel_interfaces__msg__MotorAngle __attribute__((deprecated))
#else
# define DEPRECATED__sentinel_interfaces__msg__MotorAngle __declspec(deprecated)
#endif

namespace sentinel_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MotorAngle_
{
  using Type = MotorAngle_<ContainerAllocator>;

  explicit MotorAngle_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pan = 0;
      this->tilt = 0;
    }
  }

  explicit MotorAngle_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pan = 0;
      this->tilt = 0;
    }
  }

  // field types and members
  using _pan_type =
    uint16_t;
  _pan_type pan;
  using _tilt_type =
    uint16_t;
  _tilt_type tilt;

  // setters for named parameter idiom
  Type & set__pan(
    const uint16_t & _arg)
  {
    this->pan = _arg;
    return *this;
  }
  Type & set__tilt(
    const uint16_t & _arg)
  {
    this->tilt = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sentinel_interfaces::msg::MotorAngle_<ContainerAllocator> *;
  using ConstRawPtr =
    const sentinel_interfaces::msg::MotorAngle_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sentinel_interfaces::msg::MotorAngle_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sentinel_interfaces::msg::MotorAngle_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sentinel_interfaces::msg::MotorAngle_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sentinel_interfaces::msg::MotorAngle_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sentinel_interfaces::msg::MotorAngle_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sentinel_interfaces::msg::MotorAngle_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sentinel_interfaces::msg::MotorAngle_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sentinel_interfaces::msg::MotorAngle_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sentinel_interfaces__msg__MotorAngle
    std::shared_ptr<sentinel_interfaces::msg::MotorAngle_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sentinel_interfaces__msg__MotorAngle
    std::shared_ptr<sentinel_interfaces::msg::MotorAngle_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MotorAngle_ & other) const
  {
    if (this->pan != other.pan) {
      return false;
    }
    if (this->tilt != other.tilt) {
      return false;
    }
    return true;
  }
  bool operator!=(const MotorAngle_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MotorAngle_

// alias to use template instance with default allocator
using MotorAngle =
  sentinel_interfaces::msg::MotorAngle_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sentinel_interfaces

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__MOTOR_ANGLE__STRUCT_HPP_
