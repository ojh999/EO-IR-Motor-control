// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sentinel_interfaces:msg/SingleMotorStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/single_motor_status.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__SINGLE_MOTOR_STATUS__STRUCT_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__SINGLE_MOTOR_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__sentinel_interfaces__msg__SingleMotorStatus __attribute__((deprecated))
#else
# define DEPRECATED__sentinel_interfaces__msg__SingleMotorStatus __declspec(deprecated)
#endif

namespace sentinel_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SingleMotorStatus_
{
  using Type = SingleMotorStatus_<ContainerAllocator>;

  explicit SingleMotorStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->position = 0;
      this->load = 0;
      this->temperature = 0;
      this->hw_error = 0;
    }
  }

  explicit SingleMotorStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->position = 0;
      this->load = 0;
      this->temperature = 0;
      this->hw_error = 0;
    }
  }

  // field types and members
  using _position_type =
    uint16_t;
  _position_type position;
  using _load_type =
    uint16_t;
  _load_type load;
  using _temperature_type =
    uint8_t;
  _temperature_type temperature;
  using _hw_error_type =
    uint8_t;
  _hw_error_type hw_error;

  // setters for named parameter idiom
  Type & set__position(
    const uint16_t & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__load(
    const uint16_t & _arg)
  {
    this->load = _arg;
    return *this;
  }
  Type & set__temperature(
    const uint8_t & _arg)
  {
    this->temperature = _arg;
    return *this;
  }
  Type & set__hw_error(
    const uint8_t & _arg)
  {
    this->hw_error = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sentinel_interfaces::msg::SingleMotorStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const sentinel_interfaces::msg::SingleMotorStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sentinel_interfaces::msg::SingleMotorStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sentinel_interfaces::msg::SingleMotorStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sentinel_interfaces::msg::SingleMotorStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sentinel_interfaces::msg::SingleMotorStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sentinel_interfaces::msg::SingleMotorStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sentinel_interfaces::msg::SingleMotorStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sentinel_interfaces::msg::SingleMotorStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sentinel_interfaces::msg::SingleMotorStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sentinel_interfaces__msg__SingleMotorStatus
    std::shared_ptr<sentinel_interfaces::msg::SingleMotorStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sentinel_interfaces__msg__SingleMotorStatus
    std::shared_ptr<sentinel_interfaces::msg::SingleMotorStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SingleMotorStatus_ & other) const
  {
    if (this->position != other.position) {
      return false;
    }
    if (this->load != other.load) {
      return false;
    }
    if (this->temperature != other.temperature) {
      return false;
    }
    if (this->hw_error != other.hw_error) {
      return false;
    }
    return true;
  }
  bool operator!=(const SingleMotorStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SingleMotorStatus_

// alias to use template instance with default allocator
using SingleMotorStatus =
  sentinel_interfaces::msg::SingleMotorStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sentinel_interfaces

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__SINGLE_MOTOR_STATUS__STRUCT_HPP_
