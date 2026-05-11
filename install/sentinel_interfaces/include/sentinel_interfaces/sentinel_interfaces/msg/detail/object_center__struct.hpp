// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sentinel_interfaces:msg/ObjectCenter.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/object_center.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__OBJECT_CENTER__STRUCT_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__OBJECT_CENTER__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__sentinel_interfaces__msg__ObjectCenter __attribute__((deprecated))
#else
# define DEPRECATED__sentinel_interfaces__msg__ObjectCenter __declspec(deprecated)
#endif

namespace sentinel_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ObjectCenter_
{
  using Type = ObjectCenter_<ContainerAllocator>;

  explicit ObjectCenter_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->center_x = 0.0;
      this->center_y = 0.0;
    }
  }

  explicit ObjectCenter_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->center_x = 0.0;
      this->center_y = 0.0;
    }
  }

  // field types and members
  using _center_x_type =
    double;
  _center_x_type center_x;
  using _center_y_type =
    double;
  _center_y_type center_y;

  // setters for named parameter idiom
  Type & set__center_x(
    const double & _arg)
  {
    this->center_x = _arg;
    return *this;
  }
  Type & set__center_y(
    const double & _arg)
  {
    this->center_y = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sentinel_interfaces::msg::ObjectCenter_<ContainerAllocator> *;
  using ConstRawPtr =
    const sentinel_interfaces::msg::ObjectCenter_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sentinel_interfaces::msg::ObjectCenter_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sentinel_interfaces::msg::ObjectCenter_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sentinel_interfaces::msg::ObjectCenter_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sentinel_interfaces::msg::ObjectCenter_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sentinel_interfaces::msg::ObjectCenter_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sentinel_interfaces::msg::ObjectCenter_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sentinel_interfaces::msg::ObjectCenter_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sentinel_interfaces::msg::ObjectCenter_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sentinel_interfaces__msg__ObjectCenter
    std::shared_ptr<sentinel_interfaces::msg::ObjectCenter_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sentinel_interfaces__msg__ObjectCenter
    std::shared_ptr<sentinel_interfaces::msg::ObjectCenter_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ObjectCenter_ & other) const
  {
    if (this->center_x != other.center_x) {
      return false;
    }
    if (this->center_y != other.center_y) {
      return false;
    }
    return true;
  }
  bool operator!=(const ObjectCenter_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ObjectCenter_

// alias to use template instance with default allocator
using ObjectCenter =
  sentinel_interfaces::msg::ObjectCenter_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sentinel_interfaces

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__OBJECT_CENTER__STRUCT_HPP_
