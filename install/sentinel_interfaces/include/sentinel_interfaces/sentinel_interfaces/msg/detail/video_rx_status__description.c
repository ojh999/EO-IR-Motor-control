// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from sentinel_interfaces:msg/VideoRxStatus.idl
// generated code does not contain a copyright notice

#include "sentinel_interfaces/msg/detail/video_rx_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_sentinel_interfaces
const rosidl_type_hash_t *
sentinel_interfaces__msg__VideoRxStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xbc, 0x5a, 0x53, 0xc7, 0x2d, 0x63, 0xcd, 0xbf,
      0x8c, 0xe3, 0x80, 0xe8, 0x46, 0x91, 0xce, 0x12,
      0x34, 0xb9, 0x00, 0x5d, 0x76, 0x73, 0x07, 0x49,
      0xd2, 0x0a, 0x01, 0x26, 0xff, 0xce, 0x67, 0x40,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
#endif

static char sentinel_interfaces__msg__VideoRxStatus__TYPE_NAME[] = "sentinel_interfaces/msg/VideoRxStatus";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";

// Define type names, field names, and default values
static char sentinel_interfaces__msg__VideoRxStatus__FIELD_NAME__stamp[] = "stamp";
static char sentinel_interfaces__msg__VideoRxStatus__FIELD_NAME__is_ok[] = "is_ok";
static char sentinel_interfaces__msg__VideoRxStatus__FIELD_NAME__message[] = "message";
static char sentinel_interfaces__msg__VideoRxStatus__FIELD_NAME__video_path[] = "video_path";
static char sentinel_interfaces__msg__VideoRxStatus__FIELD_NAME__published_frames[] = "published_frames";

static rosidl_runtime_c__type_description__Field sentinel_interfaces__msg__VideoRxStatus__FIELDS[] = {
  {
    {sentinel_interfaces__msg__VideoRxStatus__FIELD_NAME__stamp, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__VideoRxStatus__FIELD_NAME__is_ok, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__VideoRxStatus__FIELD_NAME__message, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__VideoRxStatus__FIELD_NAME__video_path, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__VideoRxStatus__FIELD_NAME__published_frames, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT32,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription sentinel_interfaces__msg__VideoRxStatus__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
sentinel_interfaces__msg__VideoRxStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {sentinel_interfaces__msg__VideoRxStatus__TYPE_NAME, 37, 37},
      {sentinel_interfaces__msg__VideoRxStatus__FIELDS, 5, 5},
    },
    {sentinel_interfaces__msg__VideoRxStatus__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "builtin_interfaces/Time stamp\n"
  "bool is_ok\n"
  "string message\n"
  "string video_path\n"
  "uint32 published_frames";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
sentinel_interfaces__msg__VideoRxStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {sentinel_interfaces__msg__VideoRxStatus__TYPE_NAME, 37, 37},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 98, 98},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
sentinel_interfaces__msg__VideoRxStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *sentinel_interfaces__msg__VideoRxStatus__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
