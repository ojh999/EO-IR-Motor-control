// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sentinel_interfaces:msg/ObjectCenter.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/object_center.h"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__OBJECT_CENTER__STRUCT_H_
#define SENTINEL_INTERFACES__MSG__DETAIL__OBJECT_CENTER__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/ObjectCenter in the package sentinel_interfaces.
/**
  * sentinel_interfaces/msg/ObjectCenter.msg
 */
typedef struct sentinel_interfaces__msg__ObjectCenter
{
  double center_x;
  double center_y;
} sentinel_interfaces__msg__ObjectCenter;

// Struct for a sequence of sentinel_interfaces__msg__ObjectCenter.
typedef struct sentinel_interfaces__msg__ObjectCenter__Sequence
{
  sentinel_interfaces__msg__ObjectCenter * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sentinel_interfaces__msg__ObjectCenter__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__OBJECT_CENTER__STRUCT_H_
