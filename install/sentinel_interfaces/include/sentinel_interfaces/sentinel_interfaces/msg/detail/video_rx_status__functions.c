// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sentinel_interfaces:msg/VideoRxStatus.idl
// generated code does not contain a copyright notice
#include "sentinel_interfaces/msg/detail/video_rx_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"
// Member `message`
// Member `video_path`
#include "rosidl_runtime_c/string_functions.h"

bool
sentinel_interfaces__msg__VideoRxStatus__init(sentinel_interfaces__msg__VideoRxStatus * msg)
{
  if (!msg) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    sentinel_interfaces__msg__VideoRxStatus__fini(msg);
    return false;
  }
  // is_ok
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    sentinel_interfaces__msg__VideoRxStatus__fini(msg);
    return false;
  }
  // video_path
  if (!rosidl_runtime_c__String__init(&msg->video_path)) {
    sentinel_interfaces__msg__VideoRxStatus__fini(msg);
    return false;
  }
  // published_frames
  return true;
}

void
sentinel_interfaces__msg__VideoRxStatus__fini(sentinel_interfaces__msg__VideoRxStatus * msg)
{
  if (!msg) {
    return;
  }
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
  // is_ok
  // message
  rosidl_runtime_c__String__fini(&msg->message);
  // video_path
  rosidl_runtime_c__String__fini(&msg->video_path);
  // published_frames
}

bool
sentinel_interfaces__msg__VideoRxStatus__are_equal(const sentinel_interfaces__msg__VideoRxStatus * lhs, const sentinel_interfaces__msg__VideoRxStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  // is_ok
  if (lhs->is_ok != rhs->is_ok) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  // video_path
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->video_path), &(rhs->video_path)))
  {
    return false;
  }
  // published_frames
  if (lhs->published_frames != rhs->published_frames) {
    return false;
  }
  return true;
}

bool
sentinel_interfaces__msg__VideoRxStatus__copy(
  const sentinel_interfaces__msg__VideoRxStatus * input,
  sentinel_interfaces__msg__VideoRxStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  // is_ok
  output->is_ok = input->is_ok;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  // video_path
  if (!rosidl_runtime_c__String__copy(
      &(input->video_path), &(output->video_path)))
  {
    return false;
  }
  // published_frames
  output->published_frames = input->published_frames;
  return true;
}

sentinel_interfaces__msg__VideoRxStatus *
sentinel_interfaces__msg__VideoRxStatus__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__msg__VideoRxStatus * msg = (sentinel_interfaces__msg__VideoRxStatus *)allocator.allocate(sizeof(sentinel_interfaces__msg__VideoRxStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sentinel_interfaces__msg__VideoRxStatus));
  bool success = sentinel_interfaces__msg__VideoRxStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sentinel_interfaces__msg__VideoRxStatus__destroy(sentinel_interfaces__msg__VideoRxStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sentinel_interfaces__msg__VideoRxStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sentinel_interfaces__msg__VideoRxStatus__Sequence__init(sentinel_interfaces__msg__VideoRxStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__msg__VideoRxStatus * data = NULL;

  if (size) {
    data = (sentinel_interfaces__msg__VideoRxStatus *)allocator.zero_allocate(size, sizeof(sentinel_interfaces__msg__VideoRxStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sentinel_interfaces__msg__VideoRxStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sentinel_interfaces__msg__VideoRxStatus__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
sentinel_interfaces__msg__VideoRxStatus__Sequence__fini(sentinel_interfaces__msg__VideoRxStatus__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      sentinel_interfaces__msg__VideoRxStatus__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

sentinel_interfaces__msg__VideoRxStatus__Sequence *
sentinel_interfaces__msg__VideoRxStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__msg__VideoRxStatus__Sequence * array = (sentinel_interfaces__msg__VideoRxStatus__Sequence *)allocator.allocate(sizeof(sentinel_interfaces__msg__VideoRxStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sentinel_interfaces__msg__VideoRxStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sentinel_interfaces__msg__VideoRxStatus__Sequence__destroy(sentinel_interfaces__msg__VideoRxStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sentinel_interfaces__msg__VideoRxStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sentinel_interfaces__msg__VideoRxStatus__Sequence__are_equal(const sentinel_interfaces__msg__VideoRxStatus__Sequence * lhs, const sentinel_interfaces__msg__VideoRxStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sentinel_interfaces__msg__VideoRxStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sentinel_interfaces__msg__VideoRxStatus__Sequence__copy(
  const sentinel_interfaces__msg__VideoRxStatus__Sequence * input,
  sentinel_interfaces__msg__VideoRxStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sentinel_interfaces__msg__VideoRxStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sentinel_interfaces__msg__VideoRxStatus * data =
      (sentinel_interfaces__msg__VideoRxStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sentinel_interfaces__msg__VideoRxStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sentinel_interfaces__msg__VideoRxStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sentinel_interfaces__msg__VideoRxStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
