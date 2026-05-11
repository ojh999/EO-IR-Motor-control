// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sentinel_interfaces:msg/ObjectCenter.idl
// generated code does not contain a copyright notice
#include "sentinel_interfaces/msg/detail/object_center__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
sentinel_interfaces__msg__ObjectCenter__init(sentinel_interfaces__msg__ObjectCenter * msg)
{
  if (!msg) {
    return false;
  }
  // center_x
  // center_y
  return true;
}

void
sentinel_interfaces__msg__ObjectCenter__fini(sentinel_interfaces__msg__ObjectCenter * msg)
{
  if (!msg) {
    return;
  }
  // center_x
  // center_y
}

bool
sentinel_interfaces__msg__ObjectCenter__are_equal(const sentinel_interfaces__msg__ObjectCenter * lhs, const sentinel_interfaces__msg__ObjectCenter * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // center_x
  if (lhs->center_x != rhs->center_x) {
    return false;
  }
  // center_y
  if (lhs->center_y != rhs->center_y) {
    return false;
  }
  return true;
}

bool
sentinel_interfaces__msg__ObjectCenter__copy(
  const sentinel_interfaces__msg__ObjectCenter * input,
  sentinel_interfaces__msg__ObjectCenter * output)
{
  if (!input || !output) {
    return false;
  }
  // center_x
  output->center_x = input->center_x;
  // center_y
  output->center_y = input->center_y;
  return true;
}

sentinel_interfaces__msg__ObjectCenter *
sentinel_interfaces__msg__ObjectCenter__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__msg__ObjectCenter * msg = (sentinel_interfaces__msg__ObjectCenter *)allocator.allocate(sizeof(sentinel_interfaces__msg__ObjectCenter), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sentinel_interfaces__msg__ObjectCenter));
  bool success = sentinel_interfaces__msg__ObjectCenter__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sentinel_interfaces__msg__ObjectCenter__destroy(sentinel_interfaces__msg__ObjectCenter * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sentinel_interfaces__msg__ObjectCenter__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sentinel_interfaces__msg__ObjectCenter__Sequence__init(sentinel_interfaces__msg__ObjectCenter__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__msg__ObjectCenter * data = NULL;

  if (size) {
    data = (sentinel_interfaces__msg__ObjectCenter *)allocator.zero_allocate(size, sizeof(sentinel_interfaces__msg__ObjectCenter), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sentinel_interfaces__msg__ObjectCenter__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sentinel_interfaces__msg__ObjectCenter__fini(&data[i - 1]);
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
sentinel_interfaces__msg__ObjectCenter__Sequence__fini(sentinel_interfaces__msg__ObjectCenter__Sequence * array)
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
      sentinel_interfaces__msg__ObjectCenter__fini(&array->data[i]);
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

sentinel_interfaces__msg__ObjectCenter__Sequence *
sentinel_interfaces__msg__ObjectCenter__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__msg__ObjectCenter__Sequence * array = (sentinel_interfaces__msg__ObjectCenter__Sequence *)allocator.allocate(sizeof(sentinel_interfaces__msg__ObjectCenter__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sentinel_interfaces__msg__ObjectCenter__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sentinel_interfaces__msg__ObjectCenter__Sequence__destroy(sentinel_interfaces__msg__ObjectCenter__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sentinel_interfaces__msg__ObjectCenter__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sentinel_interfaces__msg__ObjectCenter__Sequence__are_equal(const sentinel_interfaces__msg__ObjectCenter__Sequence * lhs, const sentinel_interfaces__msg__ObjectCenter__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sentinel_interfaces__msg__ObjectCenter__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sentinel_interfaces__msg__ObjectCenter__Sequence__copy(
  const sentinel_interfaces__msg__ObjectCenter__Sequence * input,
  sentinel_interfaces__msg__ObjectCenter__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sentinel_interfaces__msg__ObjectCenter);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sentinel_interfaces__msg__ObjectCenter * data =
      (sentinel_interfaces__msg__ObjectCenter *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sentinel_interfaces__msg__ObjectCenter__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sentinel_interfaces__msg__ObjectCenter__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sentinel_interfaces__msg__ObjectCenter__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
