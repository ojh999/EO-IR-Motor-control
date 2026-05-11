// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from sentinel_interfaces:msg/ObjectCenter.idl
// generated code does not contain a copyright notice

#include "sentinel_interfaces/msg/detail/object_center__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_sentinel_interfaces
const rosidl_type_hash_t *
sentinel_interfaces__msg__ObjectCenter__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x6b, 0x24, 0x74, 0x03, 0x13, 0x83, 0xde, 0xc4,
      0x34, 0x7c, 0x86, 0xe4, 0xea, 0x14, 0x89, 0x2c,
      0xa1, 0x96, 0x80, 0x7d, 0xb9, 0x35, 0xbb, 0xb6,
      0xc1, 0x1c, 0x51, 0xbe, 0x4f, 0x09, 0x3c, 0x6f,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char sentinel_interfaces__msg__ObjectCenter__TYPE_NAME[] = "sentinel_interfaces/msg/ObjectCenter";

// Define type names, field names, and default values
static char sentinel_interfaces__msg__ObjectCenter__FIELD_NAME__center_x[] = "center_x";
static char sentinel_interfaces__msg__ObjectCenter__FIELD_NAME__center_y[] = "center_y";

static rosidl_runtime_c__type_description__Field sentinel_interfaces__msg__ObjectCenter__FIELDS[] = {
  {
    {sentinel_interfaces__msg__ObjectCenter__FIELD_NAME__center_x, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__ObjectCenter__FIELD_NAME__center_y, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
sentinel_interfaces__msg__ObjectCenter__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {sentinel_interfaces__msg__ObjectCenter__TYPE_NAME, 36, 36},
      {sentinel_interfaces__msg__ObjectCenter__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# sentinel_interfaces/msg/ObjectCenter.msg\n"
  "float64 center_x\n"
  "float64 center_y";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
sentinel_interfaces__msg__ObjectCenter__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {sentinel_interfaces__msg__ObjectCenter__TYPE_NAME, 36, 36},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 76, 76},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
sentinel_interfaces__msg__ObjectCenter__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *sentinel_interfaces__msg__ObjectCenter__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
