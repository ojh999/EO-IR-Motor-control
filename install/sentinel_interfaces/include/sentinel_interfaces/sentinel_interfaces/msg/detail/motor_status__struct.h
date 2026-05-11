// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sentinel_interfaces:msg/MotorStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/motor_status.h"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__MOTOR_STATUS__STRUCT_H_
#define SENTINEL_INTERFACES__MSG__DETAIL__MOTOR_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'pan'
// Member 'tilt'
#include "sentinel_interfaces/msg/detail/single_motor_status__struct.h"

/// Struct defined in msg/MotorStatus in the package sentinel_interfaces.
typedef struct sentinel_interfaces__msg__MotorStatus
{
  sentinel_interfaces__msg__SingleMotorStatus pan;
  sentinel_interfaces__msg__SingleMotorStatus tilt;
} sentinel_interfaces__msg__MotorStatus;

// Struct for a sequence of sentinel_interfaces__msg__MotorStatus.
typedef struct sentinel_interfaces__msg__MotorStatus__Sequence
{
  sentinel_interfaces__msg__MotorStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sentinel_interfaces__msg__MotorStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__MOTOR_STATUS__STRUCT_H_
