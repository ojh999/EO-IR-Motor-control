// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from sentinel_interfaces:msg/SingleMotorStatus.idl
// generated code does not contain a copyright notice

#include "sentinel_interfaces/msg/detail/single_motor_status__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_sentinel_interfaces
const rosidl_type_hash_t *
sentinel_interfaces__msg__SingleMotorStatus__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x76, 0xf4, 0x77, 0x16, 0x9d, 0x7c, 0x86, 0xdb,
      0xcd, 0x93, 0xeb, 0x6f, 0x24, 0xce, 0xa2, 0xc6,
      0x37, 0xbd, 0x80, 0x2e, 0x1d, 0x88, 0x4c, 0xd3,
      0xd9, 0xeb, 0xbc, 0x6d, 0x62, 0x8f, 0xf2, 0x67,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types

// Hashes for external referenced types
#ifndef NDEBUG
#endif

static char sentinel_interfaces__msg__SingleMotorStatus__TYPE_NAME[] = "sentinel_interfaces/msg/SingleMotorStatus";

// Define type names, field names, and default values
static char sentinel_interfaces__msg__SingleMotorStatus__FIELD_NAME__position[] = "position";
static char sentinel_interfaces__msg__SingleMotorStatus__FIELD_NAME__load[] = "load";
static char sentinel_interfaces__msg__SingleMotorStatus__FIELD_NAME__temperature[] = "temperature";
static char sentinel_interfaces__msg__SingleMotorStatus__FIELD_NAME__hw_error[] = "hw_error";

static rosidl_runtime_c__type_description__Field sentinel_interfaces__msg__SingleMotorStatus__FIELDS[] = {
  {
    {sentinel_interfaces__msg__SingleMotorStatus__FIELD_NAME__position, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__SingleMotorStatus__FIELD_NAME__load, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT16,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__SingleMotorStatus__FIELD_NAME__temperature, 11, 11},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__msg__SingleMotorStatus__FIELD_NAME__hw_error, 8, 8},
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
sentinel_interfaces__msg__SingleMotorStatus__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {sentinel_interfaces__msg__SingleMotorStatus__TYPE_NAME, 41, 41},
      {sentinel_interfaces__msg__SingleMotorStatus__FIELDS, 4, 4},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "uint16 position\n"
  "uint16 load\n"
  "uint8 temperature\n"
  "uint8 hw_error";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
sentinel_interfaces__msg__SingleMotorStatus__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {sentinel_interfaces__msg__SingleMotorStatus__TYPE_NAME, 41, 41},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 61, 61},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
sentinel_interfaces__msg__SingleMotorStatus__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *sentinel_interfaces__msg__SingleMotorStatus__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}
