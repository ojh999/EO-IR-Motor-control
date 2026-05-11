// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sentinel_interfaces:msg/YoloStatus.idl
// generated code does not contain a copyright notice
#include "sentinel_interfaces/msg/detail/yolo_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `last_error`
#include "rosidl_runtime_c/string_functions.h"

bool
sentinel_interfaces__msg__YoloStatus__init(sentinel_interfaces__msg__YoloStatus * msg)
{
  if (!msg) {
    return false;
  }
  // enabled
  // model_loaded
  // conf_threshold
  // last_error
  if (!rosidl_runtime_c__String__init(&msg->last_error)) {
    sentinel_interfaces__msg__YoloStatus__fini(msg);
    return false;
  }
  return true;
}

void
sentinel_interfaces__msg__YoloStatus__fini(sentinel_interfaces__msg__YoloStatus * msg)
{
  if (!msg) {
    return;
  }
  // enabled
  // model_loaded
  // conf_threshold
  // last_error
  rosidl_runtime_c__String__fini(&msg->last_error);
}

bool
sentinel_interfaces__msg__YoloStatus__are_equal(const sentinel_interfaces__msg__YoloStatus * lhs, const sentinel_interfaces__msg__YoloStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // enabled
  if (lhs->enabled != rhs->enabled) {
    return false;
  }
  // model_loaded
  if (lhs->model_loaded != rhs->model_loaded) {
    return false;
  }
  // conf_threshold
  if (lhs->conf_threshold != rhs->conf_threshold) {
    return false;
  }
  // last_error
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->last_error), &(rhs->last_error)))
  {
    return false;
  }
  return true;
}

bool
sentinel_interfaces__msg__YoloStatus__copy(
  const sentinel_interfaces__msg__YoloStatus * input,
  sentinel_interfaces__msg__YoloStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // enabled
  output->enabled = input->enabled;
  // model_loaded
  output->model_loaded = input->model_loaded;
  // conf_threshold
  output->conf_threshold = input->conf_threshold;
  // last_error
  if (!rosidl_runtime_c__String__copy(
      &(input->last_error), &(output->last_error)))
  {
    return false;
  }
  return true;
}

sentinel_interfaces__msg__YoloStatus *
sentinel_interfaces__msg__YoloStatus__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__msg__YoloStatus * msg = (sentinel_interfaces__msg__YoloStatus *)allocator.allocate(sizeof(sentinel_interfaces__msg__YoloStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sentinel_interfaces__msg__YoloStatus));
  bool success = sentinel_interfaces__msg__YoloStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sentinel_interfaces__msg__YoloStatus__destroy(sentinel_interfaces__msg__YoloStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sentinel_interfaces__msg__YoloStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sentinel_interfaces__msg__YoloStatus__Sequence__init(sentinel_interfaces__msg__YoloStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__msg__YoloStatus * data = NULL;

  if (size) {
    data = (sentinel_interfaces__msg__YoloStatus *)allocator.zero_allocate(size, sizeof(sentinel_interfaces__msg__YoloStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sentinel_interfaces__msg__YoloStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sentinel_interfaces__msg__YoloStatus__fini(&data[i - 1]);
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
sentinel_interfaces__msg__YoloStatus__Sequence__fini(sentinel_interfaces__msg__YoloStatus__Sequence * array)
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
      sentinel_interfaces__msg__YoloStatus__fini(&array->data[i]);
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

sentinel_interfaces__msg__YoloStatus__Sequence *
sentinel_interfaces__msg__YoloStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__msg__YoloStatus__Sequence * array = (sentinel_interfaces__msg__YoloStatus__Sequence *)allocator.allocate(sizeof(sentinel_interfaces__msg__YoloStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sentinel_interfaces__msg__YoloStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sentinel_interfaces__msg__YoloStatus__Sequence__destroy(sentinel_interfaces__msg__YoloStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sentinel_interfaces__msg__YoloStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sentinel_interfaces__msg__YoloStatus__Sequence__are_equal(const sentinel_interfaces__msg__YoloStatus__Sequence * lhs, const sentinel_interfaces__msg__YoloStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sentinel_interfaces__msg__YoloStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sentinel_interfaces__msg__YoloStatus__Sequence__copy(
  const sentinel_interfaces__msg__YoloStatus__Sequence * input,
  sentinel_interfaces__msg__YoloStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sentinel_interfaces__msg__YoloStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sentinel_interfaces__msg__YoloStatus * data =
      (sentinel_interfaces__msg__YoloStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sentinel_interfaces__msg__YoloStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sentinel_interfaces__msg__YoloStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sentinel_interfaces__msg__YoloStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
