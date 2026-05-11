// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sentinel_interfaces:msg/VideoRxStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/video_rx_status.hpp"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__VIDEO_RX_STATUS__STRUCT_HPP_
#define SENTINEL_INTERFACES__MSG__DETAIL__VIDEO_RX_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__sentinel_interfaces__msg__VideoRxStatus __attribute__((deprecated))
#else
# define DEPRECATED__sentinel_interfaces__msg__VideoRxStatus __declspec(deprecated)
#endif

namespace sentinel_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VideoRxStatus_
{
  using Type = VideoRxStatus_<ContainerAllocator>;

  explicit VideoRxStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->is_ok = false;
      this->message = "";
      this->video_path = "";
      this->published_frames = 0ul;
    }
  }

  explicit VideoRxStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init),
    message(_alloc),
    video_path(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->is_ok = false;
      this->message = "";
      this->video_path = "";
      this->published_frames = 0ul;
    }
  }

  // field types and members
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;
  using _is_ok_type =
    bool;
  _is_ok_type is_ok;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;
  using _video_path_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _video_path_type video_path;
  using _published_frames_type =
    uint32_t;
  _published_frames_type published_frames;

  // setters for named parameter idiom
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }
  Type & set__is_ok(
    const bool & _arg)
  {
    this->is_ok = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }
  Type & set__video_path(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->video_path = _arg;
    return *this;
  }
  Type & set__published_frames(
    const uint32_t & _arg)
  {
    this->published_frames = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sentinel_interfaces::msg::VideoRxStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const sentinel_interfaces::msg::VideoRxStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sentinel_interfaces::msg::VideoRxStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sentinel_interfaces::msg::VideoRxStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sentinel_interfaces::msg::VideoRxStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sentinel_interfaces::msg::VideoRxStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sentinel_interfaces::msg::VideoRxStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sentinel_interfaces::msg::VideoRxStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sentinel_interfaces::msg::VideoRxStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sentinel_interfaces::msg::VideoRxStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sentinel_interfaces__msg__VideoRxStatus
    std::shared_ptr<sentinel_interfaces::msg::VideoRxStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sentinel_interfaces__msg__VideoRxStatus
    std::shared_ptr<sentinel_interfaces::msg::VideoRxStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VideoRxStatus_ & other) const
  {
    if (this->stamp != other.stamp) {
      return false;
    }
    if (this->is_ok != other.is_ok) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    if (this->video_path != other.video_path) {
      return false;
    }
    if (this->published_frames != other.published_frames) {
      return false;
    }
    return true;
  }
  bool operator!=(const VideoRxStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VideoRxStatus_

// alias to use template instance with default allocator
using VideoRxStatus =
  sentinel_interfaces::msg::VideoRxStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace sentinel_interfaces

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__VIDEO_RX_STATUS__STRUCT_HPP_
