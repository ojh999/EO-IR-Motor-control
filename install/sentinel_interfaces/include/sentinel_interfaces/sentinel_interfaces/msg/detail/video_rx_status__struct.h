// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sentinel_interfaces:msg/VideoRxStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/video_rx_status.h"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__VIDEO_RX_STATUS__STRUCT_H_
#define SENTINEL_INTERFACES__MSG__DETAIL__VIDEO_RX_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"
// Member 'message'
// Member 'video_path'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/VideoRxStatus in the package sentinel_interfaces.
typedef struct sentinel_interfaces__msg__VideoRxStatus
{
  builtin_interfaces__msg__Time stamp;
  bool is_ok;
  rosidl_runtime_c__String message;
  rosidl_runtime_c__String video_path;
  uint32_t published_frames;
} sentinel_interfaces__msg__VideoRxStatus;

// Struct for a sequence of sentinel_interfaces__msg__VideoRxStatus.
typedef struct sentinel_interfaces__msg__VideoRxStatus__Sequence
{
  sentinel_interfaces__msg__VideoRxStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sentinel_interfaces__msg__VideoRxStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__VIDEO_RX_STATUS__STRUCT_H_
