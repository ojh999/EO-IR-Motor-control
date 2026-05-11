// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from sentinel_interfaces:srv/SetThreshold.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "sentinel_interfaces/srv/set_threshold.h"


#ifndef SENTINEL_INTERFACES__SRV__DETAIL__SET_THRESHOLD__STRUCT_H_
#define SENTINEL_INTERFACES__SRV__DETAIL__SET_THRESHOLD__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/SetThreshold in the package sentinel_interfaces.
typedef struct sentinel_interfaces__srv__SetThreshold_Request
{
  float threshold;
} sentinel_interfaces__srv__SetThreshold_Request;

// Struct for a sequence of sentinel_interfaces__srv__SetThreshold_Request.
typedef struct sentinel_interfaces__srv__SetThreshold_Request__Sequence
{
  sentinel_interfaces__srv__SetThreshold_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sentinel_interfaces__srv__SetThreshold_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SetThreshold in the package sentinel_interfaces.
typedef struct sentinel_interfaces__srv__SetThreshold_Response
{
  bool success;
  rosidl_runtime_c__String message;
} sentinel_interfaces__srv__SetThreshold_Response;

// Struct for a sequence of sentinel_interfaces__srv__SetThreshold_Response.
typedef struct sentinel_interfaces__srv__SetThreshold_Response__Sequence
{
  sentinel_interfaces__srv__SetThreshold_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sentinel_interfaces__srv__SetThreshold_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  sentinel_interfaces__srv__SetThreshold_Event__request__MAX_SIZE = 1
};
// response
enum
{
  sentinel_interfaces__srv__SetThreshold_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/SetThreshold in the package sentinel_interfaces.
typedef struct sentinel_interfaces__srv__SetThreshold_Event
{
  service_msgs__msg__ServiceEventInfo info;
  sentinel_interfaces__srv__SetThreshold_Request__Sequence request;
  sentinel_interfaces__srv__SetThreshold_Response__Sequence response;
} sentinel_interfaces__srv__SetThreshold_Event;

// Struct for a sequence of sentinel_interfaces__srv__SetThreshold_Event.
typedef struct sentinel_interfaces__srv__SetThreshold_Event__Sequence
{
  sentinel_interfaces__srv__SetThreshold_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} sentinel_interfaces__srv__SetThreshold_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // SENTINEL_INTERFACES__SRV__DETAIL__SET_THRESHOLD__STRUCT_H_
