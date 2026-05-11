// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sentinel_interfaces:msg/Detection.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/detection.h"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__DETECTION__STRUCT_H_
#define SENTINEL_INTERFACES__MSG__DETAIL__DETECTION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/Detection in the package sentinel_interfaces.
typedef struct sentinel_interfaces__msg__Detection
{
  float cx;
  float cy;
  uint16_t frame_w;
  uint16_t frame_h;
} sentinel_interfaces__msg__Detection;

// Struct for a sequence of sentinel_interfaces__msg__Detection.
typedef struct sentinel_interfaces__msg__Detection__Sequence
{
  sentinel_interfaces__msg__Detection * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sentinel_interfaces__msg__Detection__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__DETECTION__STRUCT_H_
