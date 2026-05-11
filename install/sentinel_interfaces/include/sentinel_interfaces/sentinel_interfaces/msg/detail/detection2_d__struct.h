// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sentinel_interfaces:msg/Detection2D.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/detection2_d.h"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__DETECTION2_D__STRUCT_H_
#define SENTINEL_INTERFACES__MSG__DETAIL__DETECTION2_D__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'class_name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/Detection2D in the package sentinel_interfaces.
typedef struct sentinel_interfaces__msg__Detection2D
{
  rosidl_runtime_c__String class_name;
  float score;
  float x1;
  float y1;
  float x2;
  float y2;
} sentinel_interfaces__msg__Detection2D;

// Struct for a sequence of sentinel_interfaces__msg__Detection2D.
typedef struct sentinel_interfaces__msg__Detection2D__Sequence
{
  sentinel_interfaces__msg__Detection2D * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sentinel_interfaces__msg__Detection2D__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__DETECTION2_D__STRUCT_H_
