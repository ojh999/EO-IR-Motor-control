// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sentinel_interfaces:msg/SingleMotorStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/single_motor_status.h"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__SINGLE_MOTOR_STATUS__STRUCT_H_
#define SENTINEL_INTERFACES__MSG__DETAIL__SINGLE_MOTOR_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/SingleMotorStatus in the package sentinel_interfaces.
typedef struct sentinel_interfaces__msg__SingleMotorStatus
{
  uint16_t position;
  uint16_t load;
  uint8_t temperature;
  uint8_t hw_error;
} sentinel_interfaces__msg__SingleMotorStatus;

// Struct for a sequence of sentinel_interfaces__msg__SingleMotorStatus.
typedef struct sentinel_interfaces__msg__SingleMotorStatus__Sequence
{
  sentinel_interfaces__msg__SingleMotorStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sentinel_interfaces__msg__SingleMotorStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__SINGLE_MOTOR_STATUS__STRUCT_H_
