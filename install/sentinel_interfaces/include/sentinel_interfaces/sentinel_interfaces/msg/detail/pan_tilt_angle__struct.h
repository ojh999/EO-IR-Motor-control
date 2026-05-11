// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sentinel_interfaces:msg/PanTiltAngle.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/pan_tilt_angle.h"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__PAN_TILT_ANGLE__STRUCT_H_
#define SENTINEL_INTERFACES__MSG__DETAIL__PAN_TILT_ANGLE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/PanTiltAngle in the package sentinel_interfaces.
/**
  * sentinel_interfaces/msg/PanTiltAngle.msg
 */
typedef struct sentinel_interfaces__msg__PanTiltAngle
{
  uint16_t pan;
  uint16_t tilt;
} sentinel_interfaces__msg__PanTiltAngle;

// Struct for a sequence of sentinel_interfaces__msg__PanTiltAngle.
typedef struct sentinel_interfaces__msg__PanTiltAngle__Sequence
{
  sentinel_interfaces__msg__PanTiltAngle * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sentinel_interfaces__msg__PanTiltAngle__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__PAN_TILT_ANGLE__STRUCT_H_
