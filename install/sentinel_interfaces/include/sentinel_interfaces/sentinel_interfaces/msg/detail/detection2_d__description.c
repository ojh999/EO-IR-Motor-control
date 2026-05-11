// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from sentinel_interfaces:msg/Detection2D.idl
// generated code does not contain a copyright notice

#include "sentinel_interfaces/msg/detail/detection2_d__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_sentinel_interfaces
const rosidl_type_hash_t *
sentinel_interfaces__msg__Detection2D__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x84, 0x72, 0x29, 0x2d, 0x6c, 0x71, 0x58, 0x1c,
      0xcc, 0x41, 0xaa, 0xd7, 0xdb, 0x28, 0x06, 0x68,
      0xfa, 0x4f, 0x16, 0x24, 0x2f, 0x12, 0xe7, 0x91,
      0x3b, 0x8e, 0x73, 0x1d, 0xe7, 0x11, 0x4d, 0x71,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char sentinel_interfaces__msg__Detection2D__TYPE_NAME[] = "sentinel_interfaces/msg/Detection2D";

// Define type names, field names, and default values
static char sentinel_interfaces__msg__Detection2D__FIELD_NAME__class_name[] = "class_name";
static char sentinel_interfaces__msg__Detection2D__FIELD_NAME__score[] = "score";
static char sentinel_interfaces__msg__Detection2D__FIELD_NAME__x1[] = "x1";
static char sentinel_interfaces__msg__Detection2D__FIELD_NAME__y1[] = "y1";
static char sentinel_interfaces__msg__Detection2D__FIELD_NAME__x2[] = "x2";
static char sentinel_interfaces__msg__Detection2D__FIELD_NAME__y2[] = "y2";

static rosidl_runtime_c__type_description__Field sentinel_interfaces__msg__Detection2D__FIELDS[] = {
  {
    {sentinel_interfaces__msg__Detection2D__FIELD_NAME__class_name, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__Detection2D__FIELD_NAME__score, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__Detection2D__FIELD_NAME__x1, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__Detection2D__FIELD_NAME__y1, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__Detection2D__FIELD_NAME__x2, 2, 2},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__Detection2D__FIELD_NAME__y2, 2, 2},
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
sentinel_interfaces__msg__Detection2D__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {sentinel_interfaces__msg__Detection2D__TYPE_NAME, 35, 35},
      {sentinel_interfaces__msg__Detection2D__FIELDS, 6, 6},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "string class_name\n"
  "float32 score\n"
  "float32 x1\n"
  "float32 y1\n"
  "float32 x2\n"
  "float32 y2";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
sentinel_interfaces__msg__Detection2D__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {sentinel_interfaces__msg__Detection2D__TYPE_NAME, 35, 35},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 75, 75},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
sentinel_interfaces__msg__Detection2D__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *sentinel_interfaces__msg__Detection2D__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
