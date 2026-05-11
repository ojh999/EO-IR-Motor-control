// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from sentinel_interfaces:srv/SetThreshold.idl
// generated code does not contain a copyright notice

#include "sentinel_interfaces/srv/detail/set_threshold__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_sentinel_interfaces
const rosidl_type_hash_t *
sentinel_interfaces__srv__SetThreshold__get_type_hash(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x3e, 0x0e, 0x98, 0xd8, 0xb1, 0x9c, 0x89, 0x93,
      0x8d, 0x28, 0x56, 0x8d, 0x38, 0xe2, 0x04, 0x22,
      0x4e, 0xee, 0x07, 0x07, 0x8a, 0x0b, 0xe1, 0xbf,
      0x65, 0xa9, 0x6e, 0x59, 0x0a, 0x4d, 0x15, 0xbb,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_sentinel_interfaces
const rosidl_type_hash_t *
sentinel_interfaces__srv__SetThreshold_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x93, 0x06, 0x2f, 0x1d, 0xe9, 0x36, 0x07, 0xd0,
      0xf4, 0x1e, 0xfb, 0x15, 0xbe, 0x68, 0x60, 0xd5,
      0x2e, 0x0e, 0x8d, 0x0e, 0x5c, 0xbd, 0xda, 0x0e,
      0xad, 0xfc, 0x71, 0x3f, 0xbb, 0x28, 0xb6, 0x7e,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_sentinel_interfaces
const rosidl_type_hash_t *
sentinel_interfaces__srv__SetThreshold_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xea, 0x0c, 0xb7, 0x88, 0x3e, 0x97, 0xe1, 0xa8,
      0xd1, 0x09, 0x9b, 0xa2, 0x6f, 0x23, 0xc4, 0xef,
      0x9e, 0x17, 0x64, 0x8a, 0x29, 0xac, 0xf6, 0xf7,
      0x11, 0x62, 0x35, 0x8d, 0xb4, 0x06, 0x3b, 0xd0,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_sentinel_interfaces
const rosidl_type_hash_t *
sentinel_interfaces__srv__SetThreshold_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x1f, 0x25, 0xfe, 0xbc, 0xf2, 0x0e, 0x97, 0xc5,
      0x89, 0x32, 0x70, 0x4a, 0xd4, 0x33, 0x8b, 0x4c,
      0x57, 0xe4, 0xb4, 0x55, 0x7e, 0x47, 0x33, 0x9b,
      0xcd, 0x29, 0x2f, 0x37, 0x16, 0xf5, 0x77, 0x58,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "service_msgs/msg/detail/service_event_info__functions.h"
#include "builtin_interfaces/msg/detail/time__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t service_msgs__msg__ServiceEventInfo__EXPECTED_HASH = {1, {
    0x41, 0xbc, 0xbb, 0xe0, 0x7a, 0x75, 0xc9, 0xb5,
    0x2b, 0xc9, 0x6b, 0xfd, 0x5c, 0x24, 0xd7, 0xf0,
    0xfc, 0x0a, 0x08, 0xc0, 0xcb, 0x79, 0x21, 0xb3,
    0x37, 0x3c, 0x57, 0x32, 0x34, 0x5a, 0x6f, 0x45,
  }};
#endif

static char sentinel_interfaces__srv__SetThreshold__TYPE_NAME[] = "sentinel_interfaces/srv/SetThreshold";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char sentinel_interfaces__srv__SetThreshold_Event__TYPE_NAME[] = "sentinel_interfaces/srv/SetThreshold_Event";
static char sentinel_interfaces__srv__SetThreshold_Request__TYPE_NAME[] = "sentinel_interfaces/srv/SetThreshold_Request";
static char sentinel_interfaces__srv__SetThreshold_Response__TYPE_NAME[] = "sentinel_interfaces/srv/SetThreshold_Response";
static char service_msgs__msg__ServiceEventInfo__TYPE_NAME[] = "service_msgs/msg/ServiceEventInfo";

// Define type names, field names, and default values
static char sentinel_interfaces__srv__SetThreshold__FIELD_NAME__request_message[] = "request_message";
static char sentinel_interfaces__srv__SetThreshold__FIELD_NAME__response_message[] = "response_message";
static char sentinel_interfaces__srv__SetThreshold__FIELD_NAME__event_message[] = "event_message";

static rosidl_runtime_c__type_description__Field sentinel_interfaces__srv__SetThreshold__FIELDS[] = {
  {
    {sentinel_interfaces__srv__SetThreshold__FIELD_NAME__request_message, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {sentinel_interfaces__srv__SetThreshold_Request__TYPE_NAME, 44, 44},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__srv__SetThreshold__FIELD_NAME__response_message, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {sentinel_interfaces__srv__SetThreshold_Response__TYPE_NAME, 45, 45},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__srv__SetThreshold__FIELD_NAME__event_message, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {sentinel_interfaces__srv__SetThreshold_Event__TYPE_NAME, 42, 42},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription sentinel_interfaces__srv__SetThreshold__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__srv__SetThreshold_Event__TYPE_NAME, 42, 42},
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__srv__SetThreshold_Request__TYPE_NAME, 44, 44},
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__srv__SetThreshold_Response__TYPE_NAME, 45, 45},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
sentinel_interfaces__srv__SetThreshold__get_type_description(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {sentinel_interfaces__srv__SetThreshold__TYPE_NAME, 36, 36},
      {sentinel_interfaces__srv__SetThreshold__FIELDS, 3, 3},
    },
    {sentinel_interfaces__srv__SetThreshold__REFERENCED_TYPE_DESCRIPTIONS, 5, 5},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[1].fields = sentinel_interfaces__srv__SetThreshold_Event__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = sentinel_interfaces__srv__SetThreshold_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = sentinel_interfaces__srv__SetThreshold_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[4].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char sentinel_interfaces__srv__SetThreshold_Request__FIELD_NAME__threshold[] = "threshold";

static rosidl_runtime_c__type_description__Field sentinel_interfaces__srv__SetThreshold_Request__FIELDS[] = {
  {
    {sentinel_interfaces__srv__SetThreshold_Request__FIELD_NAME__threshold, 9, 9},
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
sentinel_interfaces__srv__SetThreshold_Request__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {sentinel_interfaces__srv__SetThreshold_Request__TYPE_NAME, 44, 44},
      {sentinel_interfaces__srv__SetThreshold_Request__FIELDS, 1, 1},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char sentinel_interfaces__srv__SetThreshold_Response__FIELD_NAME__success[] = "success";
static char sentinel_interfaces__srv__SetThreshold_Response__FIELD_NAME__message[] = "message";

static rosidl_runtime_c__type_description__Field sentinel_interfaces__srv__SetThreshold_Response__FIELDS[] = {
  {
    {sentinel_interfaces__srv__SetThreshold_Response__FIELD_NAME__success, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__srv__SetThreshold_Response__FIELD_NAME__message, 7, 7},
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
sentinel_interfaces__srv__SetThreshold_Response__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {sentinel_interfaces__srv__SetThreshold_Response__TYPE_NAME, 45, 45},
      {sentinel_interfaces__srv__SetThreshold_Response__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char sentinel_interfaces__srv__SetThreshold_Event__FIELD_NAME__info[] = "info";
static char sentinel_interfaces__srv__SetThreshold_Event__FIELD_NAME__request[] = "request";
static char sentinel_interfaces__srv__SetThreshold_Event__FIELD_NAME__response[] = "response";

static rosidl_runtime_c__type_description__Field sentinel_interfaces__srv__SetThreshold_Event__FIELDS[] = {
  {
    {sentinel_interfaces__srv__SetThreshold_Event__FIELD_NAME__info, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__srv__SetThreshold_Event__FIELD_NAME__request, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {sentinel_interfaces__srv__SetThreshold_Request__TYPE_NAME, 44, 44},
    },
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__srv__SetThreshold_Event__FIELD_NAME__response, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {sentinel_interfaces__srv__SetThreshold_Response__TYPE_NAME, 45, 45},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription sentinel_interfaces__srv__SetThreshold_Event__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__srv__SetThreshold_Request__TYPE_NAME, 44, 44},
    {NULL, 0, 0},
  },
  {
    {sentinel_interfaces__srv__SetThreshold_Response__TYPE_NAME, 45, 45},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
sentinel_interfaces__srv__SetThreshold_Event__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {sentinel_interfaces__srv__SetThreshold_Event__TYPE_NAME, 42, 42},
      {sentinel_interfaces__srv__SetThreshold_Event__FIELDS, 3, 3},
    },
    {sentinel_interfaces__srv__SetThreshold_Event__REFERENCED_TYPE_DESCRIPTIONS, 4, 4},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[1].fields = sentinel_interfaces__srv__SetThreshold_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = sentinel_interfaces__srv__SetThreshold_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[3].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "float32 threshold\n"
  "---\n"
  "bool success\n"
  "string message";

static char srv_encoding[] = "srv";
static char implicit_encoding[] = "implicit";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
sentinel_interfaces__srv__SetThreshold__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {sentinel_interfaces__srv__SetThreshold__TYPE_NAME, 36, 36},
    {srv_encoding, 3, 3},
    {toplevel_type_raw_source, 49, 49},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
sentinel_interfaces__srv__SetThreshold_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {sentinel_interfaces__srv__SetThreshold_Request__TYPE_NAME, 44, 44},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
sentinel_interfaces__srv__SetThreshold_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {sentinel_interfaces__srv__SetThreshold_Response__TYPE_NAME, 45, 45},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
sentinel_interfaces__srv__SetThreshold_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {sentinel_interfaces__srv__SetThreshold_Event__TYPE_NAME, 42, 42},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
sentinel_interfaces__srv__SetThreshold__get_type_description_sources(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[6];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 6, 6};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *sentinel_interfaces__srv__SetThreshold__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *sentinel_interfaces__srv__SetThreshold_Event__get_individual_type_description_source(NULL);
    sources[3] = *sentinel_interfaces__srv__SetThreshold_Request__get_individual_type_description_source(NULL);
    sources[4] = *sentinel_interfaces__srv__SetThreshold_Response__get_individual_type_description_source(NULL);
    sources[5] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
sentinel_interfaces__srv__SetThreshold_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *sentinel_interfaces__srv__SetThreshold_Request__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
sentinel_interfaces__srv__SetThreshold_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *sentinel_interfaces__srv__SetThreshold_Response__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
sentinel_interfaces__srv__SetThreshold_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[5];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 5, 5};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *sentinel_interfaces__srv__SetThreshold_Event__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *sentinel_interfaces__srv__SetThreshold_Request__get_individual_type_description_source(NULL);
    sources[3] = *sentinel_interfaces__srv__SetThreshold_Response__get_individual_type_description_source(NULL);
    sources[4] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
