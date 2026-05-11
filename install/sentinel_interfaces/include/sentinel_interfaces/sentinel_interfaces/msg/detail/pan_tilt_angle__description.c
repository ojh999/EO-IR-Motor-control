// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from sentinel_interfaces:msg/PanTiltAngle.idl
// generated code does not contain a copyright notice

#include "sentinel_interfaces/msg/detail/pan_tilt_angle__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_sentinel_interfaces
const rosidl_type_hash_t *
sentinel_interfaces__msg__PanTiltAngle__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xf9, 0xd9, 0xad, 0xa7, 0xff, 0xaf, 0x22, 0x77,
      0xef, 0xce, 0xa1, 0xf1, 0xaa, 0x0e, 0xf3, 0xc8,
      0x2a, 0x33, 0x7d, 0x1e, 0x04, 0x76, 0x53, 0xce,
      0x90, 0xd4, 0xfb, 0x85, 0x68, 0xd3, 0x59, 0x12,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char sentinel_interfaces__msg__PanTiltAngle__TYPE_NAME[] = "sentinel_interfaces/msg/PanTiltAngle";

// Define type names, field names, and default values
static char sentinel_interfaces__msg__PanTiltAngle__FIELD_NAME__pan[] = "pan";
static char sentinel_interfaces__msg__PanTiltAngle__FIELD_NAME__tilt[] = "tilt";

static rosidl_runtime_c__type_description__Field sentinel_interfaces__msg__PanTiltAngle__FIELDS[] = {
  {
    {sentinel_interfaces__msg__PanTiltAngle__FIELD_NAME__pan, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__PanTiltAngle__FIELD_NAME__tilt, 4, 4},
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
sentinel_interfaces__msg__PanTiltAngle__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {sentinel_interfaces__msg__PanTiltAngle__TYPE_NAME, 36, 36},
      {sentinel_interfaces__msg__PanTiltAngle__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# sentinel_interfaces/msg/PanTiltAngle.msg\n"
  "uint16 pan\n"
  "uint16 tilt";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
sentinel_interfaces__msg__PanTiltAngle__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {sentinel_interfaces__msg__PanTiltAngle__TYPE_NAME, 36, 36},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 65, 65},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
sentinel_interfaces__msg__PanTiltAngle__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *sentinel_interfaces__msg__PanTiltAngle__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
