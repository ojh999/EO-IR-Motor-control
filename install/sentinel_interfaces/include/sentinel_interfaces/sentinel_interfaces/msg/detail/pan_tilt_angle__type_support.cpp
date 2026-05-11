// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from sentinel_interfaces:msg/PanTiltAngle.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "sentinel_interfaces/msg/detail/pan_tilt_angle__functions.h"
#include "sentinel_interfaces/msg/detail/pan_tilt_angle__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace sentinel_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void PanTiltAngle_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) sentinel_interfaces::msg::PanTiltAngle(_init);
}

void PanTiltAngle_fini_function(void * message_memory)
{
  auto typed_message = static_cast<sentinel_interfaces::msg::PanTiltAngle *>(message_memory);
  typed_message->~PanTiltAngle();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember PanTiltAngle_message_member_array[2] = {
  {
    "pan",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sentinel_interfaces::msg::PanTiltAngle, pan),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "tilt",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT16,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sentinel_interfaces::msg::PanTiltAngle, tilt),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers PanTiltAngle_message_members = {
  "sentinel_interfaces::msg",  // message namespace
  "PanTiltAngle",  // message name
  2,  // number of fields
  sizeof(sentinel_interfaces::msg::PanTiltAngle),
  false,  // has_any_key_member_
  PanTiltAngle_message_member_array,  // message members
  PanTiltAngle_init_function,  // function to initialize message memory (memory has to be allocated)
  PanTiltAngle_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t PanTiltAngle_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &PanTiltAngle_message_members,
  get_message_typesupport_handle_function,
  &sentinel_interfaces__msg__PanTiltAngle__get_type_hash,
  &sentinel_interfaces__msg__PanTiltAngle__get_type_description,
  &sentinel_interfaces__msg__PanTiltAngle__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace sentinel_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<sentinel_interfaces::msg::PanTiltAngle>()
{
  return &::sentinel_interfaces::msg::rosidl_typesupport_introspection_cpp::PanTiltAngle_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, sentinel_interfaces, msg, PanTiltAngle)() {
  return &::sentinel_interfaces::msg::rosidl_typesupport_introspection_cpp::PanTiltAngle_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
