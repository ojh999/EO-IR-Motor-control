// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sentinel_interfaces:msg/ButtonInput.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/button_input.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__BUTTON_INPUT__STRUCT_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__BUTTON_INPUT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__sentinel_interfaces__msg__ButtonInput __attribute__((deprecated))
#else
# define DEPRECATED__sentinel_interfaces__msg__ButtonInput __declspec(deprecated)
#endif

namespace sentinel_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ButtonInput_
{
  using Type = ButtonInput_<ContainerAllocator>;

  explicit ButtonInput_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->buttons = 0;
    }
  }

  explicit ButtonInput_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->buttons = 0;
    }
  }

  // field types and members
  using _buttons_type =
    uint8_t;
  _buttons_type buttons;

  // setters for named parameter idiom
  Type & set__buttons(
    const uint8_t & _arg)
  {
    this->buttons = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sentinel_interfaces::msg::ButtonInput_<ContainerAllocator> *;
  using ConstRawPtr =
    const sentinel_interfaces::msg::ButtonInput_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sentinel_interfaces::msg::ButtonInput_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sentinel_interfaces::msg::ButtonInput_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sentinel_interfaces::msg::ButtonInput_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sentinel_interfaces::msg::ButtonInput_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sentinel_interfaces::msg::ButtonInput_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sentinel_interfaces::msg::ButtonInput_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sentinel_interfaces::msg::ButtonInput_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sentinel_interfaces::msg::ButtonInput_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sentinel_interfaces__msg__ButtonInput
    std::shared_ptr<sentinel_interfaces::msg::ButtonInput_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sentinel_interfaces__msg__ButtonInput
    std::shared_ptr<sentinel_interfaces::msg::ButtonInput_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ButtonInput_ & other) const
  {
    if (this->buttons != other.buttons) {
      return false;
    }
    return true;
  }
  bool operator!=(const ButtonInput_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ButtonInput_

// alias to use template instance with default allocator
using ButtonInput =
  sentinel_interfaces::msg::ButtonInput_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sentinel_interfaces

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__BUTTON_INPUT__STRUCT_HPP_
