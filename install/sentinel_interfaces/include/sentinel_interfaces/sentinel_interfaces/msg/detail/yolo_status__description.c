// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from sentinel_interfaces:msg/YoloStatus.idl
// generated code does not contain a copyright notice

#include "sentinel_interfaces/msg/detail/yolo_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_sentinel_interfaces
const rosidl_type_hash_t *
sentinel_interfaces__msg__YoloStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x07, 0x86, 0x47, 0xb6, 0xc7, 0x1f, 0x19, 0xfc,
      0x47, 0x59, 0x8f, 0xc1, 0x1b, 0xf6, 0x1b, 0xca,
      0x97, 0x59, 0xb4, 0x14, 0x50, 0xf2, 0x69, 0x3d,
      0xf3, 0xb8, 0xb6, 0xd7, 0x7a, 0x7a, 0xa9, 0x37,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char sentinel_interfaces__msg__YoloStatus__TYPE_NAME[] = "sentinel_interfaces/msg/YoloStatus";

// Define type names, field names, and default values
static char sentinel_interfaces__msg__YoloStatus__FIELD_NAME__enabled[] = "enabled";
static char sentinel_interfaces__msg__YoloStatus__FIELD_NAME__model_loaded[] = "model_loaded";
static char sentinel_interfaces__msg__YoloStatus__FIELD_NAME__conf_threshold[] = "conf_threshold";
static char sentinel_interfaces__msg__YoloStatus__FIELD_NAME__last_error[] = "last_error";

static rosidl_runtime_c__type_description__Field sentinel_interfaces__msg__YoloStatus__FIELDS[] = {
  {
    {sentinel_interfaces__msg__YoloStatus__FIELD_NAME__enabled, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__YoloStatus__FIELD_NAME__model_loaded, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__YoloStatus__FIELD_NAME__conf_threshold, 14, 14},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__YoloStatus__FIELD_NAME__last_error, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
sentinel_interfaces__msg__YoloStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {sentinel_interfaces__msg__YoloStatus__TYPE_NAME, 34, 34},
      {sentinel_interfaces__msg__YoloStatus__FIELDS, 4, 4},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "bool enabled\n"
  "bool model_loaded\n"
  "float32 conf_threshold\n"
  "string last_error";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
sentinel_interfaces__msg__YoloStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {sentinel_interfaces__msg__YoloStatus__TYPE_NAME, 34, 34},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 71, 71},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
sentinel_interfaces__msg__YoloStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *sentinel_interfaces__msg__YoloStatus__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
