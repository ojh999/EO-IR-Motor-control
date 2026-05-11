// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from sentinel_interfaces:msg/FrameInfo.idl
// generated code does not contain a copyright notice

#include "sentinel_interfaces/msg/detail/frame_info__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_sentinel_interfaces
const rosidl_type_hash_t *
sentinel_interfaces__msg__FrameInfo__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xf6, 0x5d, 0x23, 0x08, 0xb4, 0x30, 0x75, 0x16,
      0x71, 0x01, 0xcd, 0xdd, 0x3d, 0xdf, 0xe5, 0x73,
      0x65, 0xa0, 0xb8, 0x44, 0x96, 0xa8, 0x1c, 0xb3,
      0xf9, 0xa2, 0x61, 0x47, 0x75, 0xe3, 0xf5, 0x63,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char sentinel_interfaces__msg__FrameInfo__TYPE_NAME[] = "sentinel_interfaces/msg/FrameInfo";

// Define type names, field names, and default values
static char sentinel_interfaces__msg__FrameInfo__FIELD_NAME__width[] = "width";
static char sentinel_interfaces__msg__FrameInfo__FIELD_NAME__height[] = "height";
static char sentinel_interfaces__msg__FrameInfo__FIELD_NAME__fps[] = "fps";

static rosidl_runtime_c__type_description__Field sentinel_interfaces__msg__FrameInfo__FIELDS[] = {
  {
    {sentinel_interfaces__msg__FrameInfo__FIELD_NAME__width, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__FrameInfo__FIELD_NAME__height, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_INT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__FrameInfo__FIELD_NAME__fps, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
sentinel_interfaces__msg__FrameInfo__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {sentinel_interfaces__msg__FrameInfo__TYPE_NAME, 33, 33},
      {sentinel_interfaces__msg__FrameInfo__FIELDS, 3, 3},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# sentinel_interfaces/msg/FrameInfo.msg\n"
  "int32 width\n"
  "int32 height\n"
  "float32 fps";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
sentinel_interfaces__msg__FrameInfo__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {sentinel_interfaces__msg__FrameInfo__TYPE_NAME, 33, 33},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 77, 77},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
sentinel_interfaces__msg__FrameInfo__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *sentinel_interfaces__msg__FrameInfo__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
