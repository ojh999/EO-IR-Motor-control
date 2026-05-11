// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sentinel_interfaces:msg/ButtonInput.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/msg/button_input.h"


#ifndef SENTINEL_INTERFACES__MSG__DETAIL__BUTTON_INPUT__STRUCT_H_
#define SENTINEL_INTERFACES__MSG__DETAIL__BUTTON_INPUT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Struct defined in msg/ButtonInput in the package sentinel_interfaces.
typedef struct sentinel_interfaces__msg__ButtonInput
{
  uint8_t buttons;
} sentinel_interfaces__msg__ButtonInput;

// Struct for a sequence of sentinel_interfaces__msg__ButtonInput.
typedef struct sentinel_interfaces__msg__ButtonInput__Sequence
{
  sentinel_interfaces__msg__ButtonInput * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sentinel_interfaces__msg__ButtonInput__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SENTINEL_INTERFACES__MSG__DETAIL__BUTTON_INPUT__STRUCT_H_
