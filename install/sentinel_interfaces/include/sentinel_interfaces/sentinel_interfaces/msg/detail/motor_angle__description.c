// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from sentinel_interfaces:msg/MotorAngle.idl
// generated code does not contain a copyright notice

#include "sentinel_interfaces/msg/detail/motor_angle__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_sentinel_interfaces
const rosidl_type_hash_t *
sentinel_interfaces__msg__MotorAngle__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x83, 0xf1, 0x2a, 0x1b, 0xa9, 0x63, 0xf6, 0x18,
      0xb0, 0xa2, 0x87, 0x87, 0x52, 0x59, 0x13, 0xb5,
      0xaa, 0xb0, 0x01, 0x2b, 0x5d, 0x90, 0x08, 0xb1,
      0x6b, 0xc1, 0xfa, 0xd0, 0xd8, 0x34, 0x85, 0xaf,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char sentinel_interfaces__msg__MotorAngle__TYPE_NAME[] = "sentinel_interfaces/msg/MotorAngle";

// Define type names, field names, and default values
static char sentinel_interfaces__msg__MotorAngle__FIELD_NAME__pan[] = "pan";
static char sentinel_interfaces__msg__MotorAngle__FIELD_NAME__tilt[] = "tilt";

static rosidl_runtime_c__type_description__Field sentinel_interfaces__msg__MotorAngle__FIELDS[] = {
  {
    {sentinel_interfaces__msg__MotorAngle__FIELD_NAME__pan, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__MotorAngle__FIELD_NAME__tilt, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
sentinel_interfaces__msg__MotorAngle__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {sentinel_interfaces__msg__MotorAngle__TYPE_NAME, 34, 34},
      {sentinel_interfaces__msg__MotorAngle__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "uint16 pan\n"
  "uint16 tilt";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
sentinel_interfaces__msg__MotorAngle__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {sentinel_interfaces__msg__MotorAngle__TYPE_NAME, 34, 34},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 23, 23},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
sentinel_interfaces__msg__MotorAngle__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *sentinel_interfaces__msg__MotorAngle__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
