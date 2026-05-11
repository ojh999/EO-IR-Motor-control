// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from sentinel_interfaces:msg/Detection2DArray.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "sentinel_interfaces/msg/detail/detection2_d_array__functions.h"
#include "sentinel_interfaces/msg/detail/detection2_d_array__struct.hpp"
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

void Detection2DArray_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) sentinel_interfaces::msg::Detection2DArray(_init);
}

void Detection2DArray_fini_function(void * message_memory)
{
  auto typed_message = static_cast<sentinel_interfaces::msg::Detection2DArray *>(message_memory);
  typed_message->~Detection2DArray();
}

size_t size_function__Detection2DArray__detections(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<sentinel_interfaces::msg::Detection2D> *>(untyped_member);
  return member->size();
}

const void * get_const_function__Detection2DArray__detections(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<sentinel_interfaces::msg::Detection2D> *>(untyped_member);
  return &member[index];
}

void * get_function__Detection2DArray__detections(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<sentinel_interfaces::msg::Detection2D> *>(untyped_member);
  return &member[index];
}

void fetch_function__Detection2DArray__detections(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const sentinel_interfaces::msg::Detection2D *>(
    get_const_function__Detection2DArray__detections(untyped_member, index));
  auto & value = *reinterpret_cast<sentinel_interfaces::msg::Detection2D *>(untyped_value);
  value = item;
}

void assign_function__Detection2DArray__detections(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<sentinel_interfaces::msg::Detection2D *>(
    get_function__Detection2DArray__detections(untyped_member, index));
  const auto & value = *reinterpret_cast<const sentinel_interfaces::msg::Detection2D *>(untyped_value);
  item = value;
}

void resize_function__Detection2DArray__detections(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<sentinel_interfaces::msg::Detection2D> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember Detection2DArray_message_member_array[3] = {
  {
    "stamp",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<builtin_interfaces::msg::Time>(),  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sentinel_interfaces::msg::Detection2DArray, stamp),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "frame_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sentinel_interfaces::msg::Detection2DArray, frame_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "detections",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<sentinel_interfaces::msg::Detection2D>(),  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(sentinel_interfaces::msg::Detection2DArray, detections),  // bytes offset in struct
    nullptr,  // default value
    size_function__Detection2DArray__detections,  // size() function pointer
    get_const_function__Detection2DArray__detections,  // get_const(index) function pointer
    get_function__Detection2DArray__detections,  // get(index) function pointer
    fetch_function__Detection2DArray__detections,  // fetch(index, &value) function pointer
    assign_function__Detection2DArray__detections,  // assign(index, value) function pointer
    resize_function__Detection2DArray__detections  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers Detection2DArray_message_members = {
  "sentinel_interfaces::msg",  // message namespace
  "Detection2DArray",  // message name
  3,  // number of fields
  sizeof(sentinel_interfaces::msg::Detection2DArray),
  false,  // has_any_key_member_
  Detection2DArray_message_member_array,  // message members
  Detection2DArray_init_function,  // function to initialize message memory (memory has to be allocated)
  Detection2DArray_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t Detection2DArray_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &Detection2DArray_message_members,
  get_message_typesupport_handle_function,
  &sentinel_interfaces__msg__Detection2DArray__get_type_hash,
  &sentinel_interfaces__msg__Detection2DArray__get_type_description,
  &sentinel_interfaces__msg__Detection2DArray__get_type_description_sources,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace sentinel_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<sentinel_interfaces::msg::Detection2DArray>()
{
  return &::sentinel_interfaces::msg::rosidl_typesupport_introspection_cpp::Detection2DArray_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, sentinel_interfaces, msg, Detection2DArray)() {
  return &::sentinel_interfaces::msg::rosidl_typesupport_introspection_cpp::Detection2DArray_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
