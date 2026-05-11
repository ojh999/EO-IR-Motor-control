// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sentinel_interfaces:msg/YoloStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/yolo_status.h"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__YOLO_STATUS__STRUCT_H_
#define SENTINEL_INTERFACES__MSG__DETAIL__YOLO_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'last_error'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/YoloStatus in the package sentinel_interfaces.
typedef struct sentinel_interfaces__msg__YoloStatus
{
  bool enabled;
  bool model_loaded;
  float conf_threshold;
  rosidl_runtime_c__String last_error;
} sentinel_interfaces__msg__YoloStatus;

// Struct for a sequence of sentinel_interfaces__msg__YoloStatus.
typedef struct sentinel_interfaces__msg__YoloStatus__Sequence
{
  sentinel_interfaces__msg__YoloStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sentinel_interfaces__msg__YoloStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__YOLO_STATUS__STRUCT_H_
