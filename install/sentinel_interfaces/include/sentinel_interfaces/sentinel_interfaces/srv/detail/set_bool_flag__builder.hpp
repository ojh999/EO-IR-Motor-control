// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from sentinel_interfaces:srv/SetBoolFlag.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/srv/set_bool_flag.hpp"


#ifndef SENTINEL_INTERFACES__SRV__DETAIL__SET_BOOL_FLAG__BUILDER_HPP_
#define SENTINEL_INTERFACES__SRV__DETAIL__SET_BOOL_FLAG__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "sentinel_interfaces/srv/detail/set_bool_flag__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace sentinel_interfaces
{

namespace srv
{

namespace builder
{

class Init_SetBoolFlag_Request_data
{
public:
  Init_SetBoolFlag_Request_data()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::sentinel_interfaces::srv::SetBoolFlag_Request data(::sentinel_interfaces::srv::SetBoolFlag_Request::_data_type arg)
  {
    msg_.data = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sentinel_interfaces::srv::SetBoolFlag_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::sentinel_interfaces::srv::SetBoolFlag_Request>()
{
  return sentinel_interfaces::srv::builder::Init_SetBoolFlag_Request_data();
}

}  // namespace sentinel_interfaces


namespace sentinel_interfaces
{

namespace srv
{

namespace builder
{

class Init_SetBoolFlag_Response_message
{
public:
  explicit Init_SetBoolFlag_Response_message(::sentinel_interfaces::srv::SetBoolFlag_Response & msg)
  : msg_(msg)
  {}
  ::sentinel_interfaces::srv::SetBoolFlag_Response message(::sentinel_interfaces::srv::SetBoolFlag_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sentinel_interfaces::srv::SetBoolFlag_Response msg_;
};

class Init_SetBoolFlag_Response_success
{
public:
  Init_SetBoolFlag_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetBoolFlag_Response_message success(::sentinel_interfaces::srv::SetBoolFlag_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SetBoolFlag_Response_message(msg_);
  }

private:
  ::sentinel_interfaces::srv::SetBoolFlag_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::sentinel_interfaces::srv::SetBoolFlag_Response>()
{
  return sentinel_interfaces::srv::builder::Init_SetBoolFlag_Response_success();
}

}  // namespace sentinel_interfaces


namespace sentinel_interfaces
{

namespace srv
{

namespace builder
{

class Init_SetBoolFlag_Event_response
{
public:
  explicit Init_SetBoolFlag_Event_response(::sentinel_interfaces::srv::SetBoolFlag_Event & msg)
  : msg_(msg)
  {}
  ::sentinel_interfaces::srv::SetBoolFlag_Event response(::sentinel_interfaces::srv::SetBoolFlag_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::sentinel_interfaces::srv::SetBoolFlag_Event msg_;
};

class Init_SetBoolFlag_Event_request
{
public:
  explicit Init_SetBoolFlag_Event_request(::sentinel_interfaces::srv::SetBoolFlag_Event & msg)
  : msg_(msg)
  {}
  Init_SetBoolFlag_Event_response request(::sentinel_interfaces::srv::SetBoolFlag_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_SetBoolFlag_Event_response(msg_);
  }

private:
  ::sentinel_interfaces::srv::SetBoolFlag_Event msg_;
};

class Init_SetBoolFlag_Event_info
{
public:
  Init_SetBoolFlag_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetBoolFlag_Event_request info(::sentinel_interfaces::srv::SetBoolFlag_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_SetBoolFlag_Event_request(msg_);
  }

private:
  ::sentinel_interfaces::srv::SetBoolFlag_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::sentinel_interfaces::srv::SetBoolFlag_Event>()
{
  return sentinel_interfaces::srv::builder::Init_SetBoolFlag_Event_info();
}

}  // namespace sentinel_interfaces

#endif  // SENTINEL_INTERFACES__SRV__DETAIL__SET_BOOL_FLAG__BUILDER_HPP_
