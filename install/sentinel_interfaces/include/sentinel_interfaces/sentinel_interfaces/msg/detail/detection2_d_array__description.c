// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from sentinel_interfaces:msg/Detection2DArray.idl
// generated code does not contain a copyright notice

#include "sentinel_interfaces/msg/detail/detection2_d_array__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_sentinel_interfaces
const rosidl_type_hash_t *
sentinel_interfaces__msg__Detection2DArray__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x86, 0x2d, 0x26, 0x9e, 0xea, 0xc1, 0xc2, 0x57,
      0x46, 0xfb, 0x50, 0xe8, 0x27, 0xcc, 0xd7, 0xc2,
      0x52, 0xe6, 0xe2, 0xcf, 0x0a, 0xe0, 0x3b, 0xee,
      0x95, 0x4a, 0xc6, 0xcd, 0x95, 0x45, 0x51, 0x9c,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "sentinel_interfaces/msg/detail/detection2_d__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t sentinel_interfaces__msg__Detection2D__EXPECTED_HASH = {1, {
    0x84, 0x72, 0x29, 0x2d, 0x6c, 0x71, 0x58, 0x1c,
    0xcc, 0x41, 0xaa, 0xd7, 0xdb, 0x28, 0x06, 0x68,
    0xfa, 0x4f, 0x16, 0x24, 0x2f, 0x12, 0xe7, 0x91,
    0x3b, 0x8e, 0x73, 0x1d, 0xe7, 0x11, 0x4d, 0x71,
  }};
#endif

static char sentinel_interfaces__msg__Detection2DArray__TYPE_NAME[] = "sentinel_interfaces/msg/Detection2DArray";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char sentinel_interfaces__msg__Detection2D__TYPE_NAME[] = "sentinel_interfaces/msg/Detection2D";

// Define type names, field names, and default values
static char sentinel_interfaces__msg__Detection2DArray__FIELD_NAME__stamp[] = "stamp";
static char sentinel_interfaces__msg__Detection2DArray__FIELD_NAME__frame_id[] = "frame_id";
static char sentinel_interfaces__msg__Detection2DArray__FIELD_NAME__detections[] = "detections";

static rosidl_runtime_c__type_description__Field sentinel_interfaces__msg__Detection2DArray__FIELDS[] = {
  {
    {sentinel_interfaces__msg__Detection2DArray__FIELD_NAME__stamp, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__Detection2DArray__FIELD_NAME__frame_id, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__Detection2DArray__FIELD_NAME__detections, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {sentinel_interfaces__msg__Detection2D__TYPE_NAME, 35, 35},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription sentinel_interfaces__msg__Detection2DArray__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__Detection2D__TYPE_NAME, 35, 35},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
sentinel_interfaces__msg__Detection2DArray__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {sentinel_interfaces__msg__Detection2DArray__TYPE_NAME, 40, 40},
      {sentinel_interfaces__msg__Detection2DArray__FIELDS, 3, 3},
    },
    {sentinel_interfaces__msg__Detection2DArray__REFERENCED_TYPE_DESCRIPTIONS, 2, 2},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&sentinel_interfaces__msg__Detection2D__EXPECTED_HASH, sentinel_interfaces__msg__Detection2D__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = sentinel_interfaces__msg__Detection2D__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "builtin_interfaces/Time stamp\n"
  "uint32 frame_id\n"
  "Detection2D[] detections";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
sentinel_interfaces__msg__Detection2DArray__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {sentinel_interfaces__msg__Detection2DArray__TYPE_NAME, 40, 40},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 70, 70},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
sentinel_interfaces__msg__Detection2DArray__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[3];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 3, 3};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *sentinel_interfaces__msg__Detection2DArray__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *sentinel_interfaces__msg__Detection2D__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
