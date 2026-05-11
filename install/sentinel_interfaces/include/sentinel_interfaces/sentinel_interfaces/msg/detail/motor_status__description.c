// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from sentinel_interfaces:msg/MotorStatus.idl
// generated code does not contain a copyright notice

#include "sentinel_interfaces/msg/detail/motor_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_sentinel_interfaces
const rosidl_type_hash_t *
sentinel_interfaces__msg__MotorStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xe0, 0x5d, 0xfd, 0x53, 0xc2, 0xe4, 0x41, 0xe1,
      0x69, 0xf5, 0x92, 0xd5, 0x62, 0xb0, 0xd6, 0x9c,
      0x89, 0xa1, 0xf8, 0x93, 0x05, 0x93, 0xdb, 0x9c,
      0x8b, 0x83, 0x66, 0xcd, 0x0d, 0x87, 0xfa, 0x26,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "sentinel_interfaces/msg/detail/single_motor_status__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t sentinel_interfaces__msg__SingleMotorStatus__EXPECTED_HASH = {1, {
    0x76, 0xf4, 0x77, 0x16, 0x9d, 0x7c, 0x86, 0xdb,
    0xcd, 0x93, 0xeb, 0x6f, 0x24, 0xce, 0xa2, 0xc6,
    0x37, 0xbd, 0x80, 0x2e, 0x1d, 0x88, 0x4c, 0xd3,
    0xd9, 0xeb, 0xbc, 0x6d, 0x62, 0x8f, 0xf2, 0x67,
  }};
#endif

static char sentinel_interfaces__msg__MotorStatus__TYPE_NAME[] = "sentinel_interfaces/msg/MotorStatus";
static char sentinel_interfaces__msg__SingleMotorStatus__TYPE_NAME[] = "sentinel_interfaces/msg/SingleMotorStatus";

// Define type names, field names, and default values
static char sentinel_interfaces__msg__MotorStatus__FIELD_NAME__pan[] = "pan";
static char sentinel_interfaces__msg__MotorStatus__FIELD_NAME__tilt[] = "tilt";

static rosidl_runtime_c__type_description__Field sentinel_interfaces__msg__MotorStatus__FIELDS[] = {
  {
    {sentinel_interfaces__msg__MotorStatus__FIELD_NAME__pan, 3, 3},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {sentinel_interfaces__msg__SingleMotorStatus__TYPE_NAME, 41, 41},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__MotorStatus__FIELD_NAME__tilt, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {sentinel_interfaces__msg__SingleMotorStatus__TYPE_NAME, 41, 41},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription sentinel_interfaces__msg__MotorStatus__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {sentinel_interfaces__msg__SingleMotorStatus__TYPE_NAME, 41, 41},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
sentinel_interfaces__msg__MotorStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {sentinel_interfaces__msg__MotorStatus__TYPE_NAME, 35, 35},
      {sentinel_interfaces__msg__MotorStatus__FIELDS, 2, 2},
    },
    {sentinel_interfaces__msg__MotorStatus__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&sentinel_interfaces__msg__SingleMotorStatus__EXPECTED_HASH, sentinel_interfaces__msg__SingleMotorStatus__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = sentinel_interfaces__msg__SingleMotorStatus__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "SingleMotorStatus pan\n"
  "SingleMotorStatus tilt";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
sentinel_interfaces__msg__MotorStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {sentinel_interfaces__msg__MotorStatus__TYPE_NAME, 35, 35},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 45, 45},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
sentinel_interfaces__msg__MotorStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *sentinel_interfaces__msg__MotorStatus__get_individual_type_description_source(NULL),
    sources[1] = *sentinel_interfaces__msg__SingleMotorStatus__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
