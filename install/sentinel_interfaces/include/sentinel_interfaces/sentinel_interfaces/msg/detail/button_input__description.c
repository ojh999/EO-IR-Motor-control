// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from sentinel_interfaces:msg/ButtonInput.idl
// generated code does not contain a copyright notice

#include "sentinel_interfaces/msg/detail/button_input__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_sentinel_interfaces
const rosidl_type_hash_t *
sentinel_interfaces__msg__ButtonInput__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xaf, 0x4d, 0x17, 0x5b, 0xf1, 0x6b, 0x9d, 0x6d,
      0x2c, 0xc7, 0x85, 0xce, 0x5c, 0xfc, 0xa7, 0xbb,
      0x76, 0x07, 0xf9, 0x10, 0x2a, 0xdb, 0x6d, 0x2e,
      0x2d, 0x4e, 0x1b, 0x05, 0x43, 0xa5, 0xe4, 0xb0,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char sentinel_interfaces__msg__ButtonInput__TYPE_NAME[] = "sentinel_interfaces/msg/ButtonInput";

// Define type names, field names, and default values
static char sentinel_interfaces__msg__ButtonInput__FIELD_NAME__buttons[] = "buttons";

static rosidl_runtime_c__type_description__Field sentinel_interfaces__msg__ButtonInput__FIELDS[] = {
  {
    {sentinel_interfaces__msg__ButtonInput__FIELD_NAME__buttons, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
sentinel_interfaces__msg__ButtonInput__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {sentinel_interfaces__msg__ButtonInput__TYPE_NAME, 35, 35},
      {sentinel_interfaces__msg__ButtonInput__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "uint8 buttons";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
sentinel_interfaces__msg__ButtonInput__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {sentinel_interfaces__msg__ButtonInput__TYPE_NAME, 35, 35},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 14, 14},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
sentinel_interfaces__msg__ButtonInput__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *sentinel_interfaces__msg__ButtonInput__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
