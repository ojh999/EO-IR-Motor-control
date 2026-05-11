// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sentinel_interfaces:msg/MotorStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/motor_status.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__MOTOR_STATUS__STRUCT_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__MOTOR_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'pan'
// Member 'tilt'
#include "sentinel_interfaces/msg/detail/single_motor_status__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__sentinel_interfaces__msg__MotorStatus __attribute__((deprecated))
#else
# define DEPRECATED__sentinel_interfaces__msg__MotorStatus __declspec(deprecated)
#endif

namespace sentinel_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct MotorStatus_
{
  using Type = MotorStatus_<ContainerAllocator>;

  explicit MotorStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pan(_init),
    tilt(_init)
  {
    (void)_init;
  }

  explicit MotorStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : pan(_alloc, _init),
    tilt(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _pan_type =
    sentinel_interfaces::msg::SingleMotorStatus_<ContainerAllocator>;
  _pan_type pan;
  using _tilt_type =
    sentinel_interfaces::msg::SingleMotorStatus_<ContainerAllocator>;
  _tilt_type tilt;

  // setters for named parameter idiom
  Type & set__pan(
    const sentinel_interfaces::msg::SingleMotorStatus_<ContainerAllocator> & _arg)
  {
    this->pan = _arg;
    return *this;
  }
  Type & set__tilt(
    const sentinel_interfaces::msg::SingleMotorStatus_<ContainerAllocator> & _arg)
  {
    this->tilt = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sentinel_interfaces::msg::MotorStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const sentinel_interfaces::msg::MotorStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sentinel_interfaces::msg::MotorStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sentinel_interfaces::msg::MotorStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sentinel_interfaces::msg::MotorStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sentinel_interfaces::msg::MotorStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sentinel_interfaces::msg::MotorStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sentinel_interfaces::msg::MotorStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sentinel_interfaces::msg::MotorStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sentinel_interfaces::msg::MotorStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sentinel_interfaces__msg__MotorStatus
    std::shared_ptr<sentinel_interfaces::msg::MotorStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sentinel_interfaces__msg__MotorStatus
    std::shared_ptr<sentinel_interfaces::msg::MotorStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const MotorStatus_ & other) const
  {
    if (this->pan != other.pan) {
      return false;
    }
    if (this->tilt != other.tilt) {
      return false;
    }
    return true;
  }
  bool operator!=(const MotorStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct MotorStatus_

// alias to use template instance with default allocator
using MotorStatus =
  sentinel_interfaces::msg::MotorStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sentinel_interfaces

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__MOTOR_STATUS__STRUCT_HPP_
