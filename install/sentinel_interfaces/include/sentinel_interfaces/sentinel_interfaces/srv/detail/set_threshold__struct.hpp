// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from sentinel_interfaces:srv/SetThreshold.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/srv/set_threshold.hpp"


#ifndef SENTINEL_INTERFACES__SRV__DETAIL__SET_THRESHOLD__STRUCT_HPP_
#define SENTINEL_INTERFACES__SRV__DETAIL__SET_THRESHOLD__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__sentinel_interfaces__srv__SetThreshold_Request __attribute__((deprecated))
#else
# define DEPRECATED__sentinel_interfaces__srv__SetThreshold_Request __declspec(deprecated)
#endif

namespace sentinel_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetThreshold_Request_
{
  using Type = SetThreshold_Request_<ContainerAllocator>;

  explicit SetThreshold_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->threshold = 0.0f;
    }
  }

  explicit SetThreshold_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->threshold = 0.0f;
    }
  }

  // field types and members
  using _threshold_type =
    float;
  _threshold_type threshold;

  // setters for named parameter idiom
  Type & set__threshold(
    const float & _arg)
  {
    this->threshold = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sentinel_interfaces::srv::SetThreshold_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const sentinel_interfaces::srv::SetThreshold_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sentinel_interfaces::srv::SetThreshold_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sentinel_interfaces::srv::SetThreshold_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sentinel_interfaces::srv::SetThreshold_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sentinel_interfaces::srv::SetThreshold_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sentinel_interfaces::srv::SetThreshold_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sentinel_interfaces::srv::SetThreshold_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sentinel_interfaces::srv::SetThreshold_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sentinel_interfaces::srv::SetThreshold_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sentinel_interfaces__srv__SetThreshold_Request
    std::shared_ptr<sentinel_interfaces::srv::SetThreshold_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sentinel_interfaces__srv__SetThreshold_Request
    std::shared_ptr<sentinel_interfaces::srv::SetThreshold_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetThreshold_Request_ & other) const
  {
    if (this->threshold != other.threshold) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetThreshold_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetThreshold_Request_

// alias to use template instance with default allocator
using SetThreshold_Request =
  sentinel_interfaces::srv::SetThreshold_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace sentinel_interfaces


#ifndef _WIN32
# define DEPRECATED__sentinel_interfaces__srv__SetThreshold_Response __attribute__((deprecated))
#else
# define DEPRECATED__sentinel_interfaces__srv__SetThreshold_Response __declspec(deprecated)
#endif

namespace sentinel_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetThreshold_Response_
{
  using Type = SetThreshold_Response_<ContainerAllocator>;

  explicit SetThreshold_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit SetThreshold_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sentinel_interfaces::srv::SetThreshold_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const sentinel_interfaces::srv::SetThreshold_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sentinel_interfaces::srv::SetThreshold_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sentinel_interfaces::srv::SetThreshold_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sentinel_interfaces::srv::SetThreshold_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sentinel_interfaces::srv::SetThreshold_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sentinel_interfaces::srv::SetThreshold_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sentinel_interfaces::srv::SetThreshold_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sentinel_interfaces::srv::SetThreshold_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sentinel_interfaces::srv::SetThreshold_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sentinel_interfaces__srv__SetThreshold_Response
    std::shared_ptr<sentinel_interfaces::srv::SetThreshold_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sentinel_interfaces__srv__SetThreshold_Response
    std::shared_ptr<sentinel_interfaces::srv::SetThreshold_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetThreshold_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetThreshold_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetThreshold_Response_

// alias to use template instance with default allocator
using SetThreshold_Response =
  sentinel_interfaces::srv::SetThreshold_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace sentinel_interfaces


// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__sentinel_interfaces__srv__SetThreshold_Event __attribute__((deprecated))
#else
# define DEPRECATED__sentinel_interfaces__srv__SetThreshold_Event __declspec(deprecated)
#endif

namespace sentinel_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetThreshold_Event_
{
  using Type = SetThreshold_Event_<ContainerAllocator>;

  explicit SetThreshold_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit SetThreshold_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<sentinel_interfaces::srv::SetThreshold_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<sentinel_interfaces::srv::SetThreshold_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<sentinel_interfaces::srv::SetThreshold_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<sentinel_interfaces::srv::SetThreshold_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<sentinel_interfaces::srv::SetThreshold_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<sentinel_interfaces::srv::SetThreshold_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<sentinel_interfaces::srv::SetThreshold_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<sentinel_interfaces::srv::SetThreshold_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    sentinel_interfaces::srv::SetThreshold_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const sentinel_interfaces::srv::SetThreshold_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<sentinel_interfaces::srv::SetThreshold_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<sentinel_interfaces::srv::SetThreshold_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      sentinel_interfaces::srv::SetThreshold_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<sentinel_interfaces::srv::SetThreshold_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      sentinel_interfaces::srv::SetThreshold_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<sentinel_interfaces::srv::SetThreshold_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<sentinel_interfaces::srv::SetThreshold_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<sentinel_interfaces::srv::SetThreshold_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__sentinel_interfaces__srv__SetThreshold_Event
    std::shared_ptr<sentinel_interfaces::srv::SetThreshold_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__sentinel_interfaces__srv__SetThreshold_Event
    std::shared_ptr<sentinel_interfaces::srv::SetThreshold_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetThreshold_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetThreshold_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetThreshold_Event_

// alias to use template instance with default allocator
using SetThreshold_Event =
  sentinel_interfaces::srv::SetThreshold_Event_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace sentinel_interfaces

namespace sentinel_interfaces
{

namespace srv
{

struct SetThreshold
{
  using Request = sentinel_interfaces::srv::SetThreshold_Request;
  using Response = sentinel_interfaces::srv::SetThreshold_Response;
  using Event = sentinel_interfaces::srv::SetThreshold_Event;
};

}  // namespace srv

}  // namespace sentinel_interfaces

#endif  // SENTINEL_INTERFACES__SRV__DETAIL__SET_THRESHOLD__STRUCT_HPP_
