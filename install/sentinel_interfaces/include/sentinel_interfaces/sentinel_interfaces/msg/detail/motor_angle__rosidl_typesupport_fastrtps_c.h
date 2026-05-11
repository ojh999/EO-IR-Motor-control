// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from sentinel_interfaces:msg/MotorAngle.idl
// generated code does not contain a copyright notice
#ifndef SENTINEL_INTERFACES__MSG__DETAIL__MOTOR_ANGLE__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define SENTINEL_INTERFACES__MSG__DETAIL__MOTOR_ANGLE__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "sentinel_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "sentinel_interfaces/msg/detail/motor_angle__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_sentinel_interfaces
bool cdr_serialize_sentinel_interfaces__msg__MotorAngle(
  const sentinel_interfaces__msg__MotorAngle * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_sentinel_interfaces
bool cdr_deserialize_sentinel_interfaces__msg__MotorAngle(
  eprosima::fastcdr::Cdr &,
  sentinel_interfaces__msg__MotorAngle * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_sentinel_interfaces
size_t get_serialized_size_sentinel_interfaces__msg__MotorAngle(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_sentinel_interfaces
size_t max_serialized_size_sentinel_interfaces__msg__MotorAngle(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_sentinel_interfaces
bool cdr_serialize_key_sentinel_interfaces__msg__MotorAngle(
  const sentinel_interfaces__msg__MotorAngle * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_sentinel_interfaces
size_t get_serialized_size_key_sentinel_interfaces__msg__MotorAngle(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_sentinel_interfaces
size_t max_serialized_size_key_sentinel_interfaces__msg__MotorAngle(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_sentinel_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, sentinel_interfaces, msg, MotorAngle)();

#ifdef __cplusplus
}
#endif

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__MOTOR_ANGLE__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
