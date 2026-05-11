// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sentinel_interfaces:msg/FrameInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/frame_info.h"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__FRAME_INFO__STRUCT_H_
#define SENTINEL_INTERFACES__MSG__DETAIL__FRAME_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/FrameInfo in the package sentinel_interfaces.
/**
  * sentinel_interfaces/msg/FrameInfo.msg
 */
typedef struct sentinel_interfaces__msg__FrameInfo
{
  int32_t width;
  int32_t height;
  float fps;
} sentinel_interfaces__msg__FrameInfo;

// Struct for a sequence of sentinel_interfaces__msg__FrameInfo.
typedef struct sentinel_interfaces__msg__FrameInfo__Sequence
{
  sentinel_interfaces__msg__FrameInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sentinel_interfaces__msg__FrameInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__FRAME_INFO__STRUCT_H_
