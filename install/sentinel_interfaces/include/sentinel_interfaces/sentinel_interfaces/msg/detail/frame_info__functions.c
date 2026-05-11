// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sentinel_interfaces:msg/FrameInfo.idl
// generated code does not contain a copyright notice
#include "sentinel_interfaces/msg/detail/frame_info__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
sentinel_interfaces__msg__FrameInfo__init(sentinel_interfaces__msg__FrameInfo * msg)
{
  if (!msg) {
    return false;
  }
  // width
  // height
  // fps
  return true;
}

void
sentinel_interfaces__msg__FrameInfo__fini(sentinel_interfaces__msg__FrameInfo * msg)
{
  if (!msg) {
    return;
  }
  // width
  // height
  // fps
}

bool
sentinel_interfaces__msg__FrameInfo__are_equal(const sentinel_interfaces__msg__FrameInfo * lhs, const sentinel_interfaces__msg__FrameInfo * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // width
  if (lhs->width != rhs->width) {
    return false;
  }
  // height
  if (lhs->height != rhs->height) {
    return false;
  }
  // fps
  if (lhs->fps != rhs->fps) {
    return false;
  }
  return true;
}

bool
sentinel_interfaces__msg__FrameInfo__copy(
  const sentinel_interfaces__msg__FrameInfo * input,
  sentinel_interfaces__msg__FrameInfo * output)
{
  if (!input || !output) {
    return false;
  }
  // width
  output->width = input->width;
  // height
  output->height = input->height;
  // fps
  output->fps = input->fps;
  return true;
}

sentinel_interfaces__msg__FrameInfo *
sentinel_interfaces__msg__FrameInfo__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__msg__FrameInfo * msg = (sentinel_interfaces__msg__FrameInfo *)allocator.allocate(sizeof(sentinel_interfaces__msg__FrameInfo), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sentinel_interfaces__msg__FrameInfo));
  bool success = sentinel_interfaces__msg__FrameInfo__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sentinel_interfaces__msg__FrameInfo__destroy(sentinel_interfaces__msg__FrameInfo * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sentinel_interfaces__msg__FrameInfo__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sentinel_interfaces__msg__FrameInfo__Sequence__init(sentinel_interfaces__msg__FrameInfo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__msg__FrameInfo * data = NULL;

  if (size) {
    data = (sentinel_interfaces__msg__FrameInfo *)allocator.zero_allocate(size, sizeof(sentinel_interfaces__msg__FrameInfo), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sentinel_interfaces__msg__FrameInfo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sentinel_interfaces__msg__FrameInfo__fini(&data[i - 1]);
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
sentinel_interfaces__msg__FrameInfo__Sequence__fini(sentinel_interfaces__msg__FrameInfo__Sequence * array)
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
      sentinel_interfaces__msg__FrameInfo__fini(&array->data[i]);
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

sentinel_interfaces__msg__FrameInfo__Sequence *
sentinel_interfaces__msg__FrameInfo__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__msg__FrameInfo__Sequence * array = (sentinel_interfaces__msg__FrameInfo__Sequence *)allocator.allocate(sizeof(sentinel_interfaces__msg__FrameInfo__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sentinel_interfaces__msg__FrameInfo__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sentinel_interfaces__msg__FrameInfo__Sequence__destroy(sentinel_interfaces__msg__FrameInfo__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sentinel_interfaces__msg__FrameInfo__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sentinel_interfaces__msg__FrameInfo__Sequence__are_equal(const sentinel_interfaces__msg__FrameInfo__Sequence * lhs, const sentinel_interfaces__msg__FrameInfo__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sentinel_interfaces__msg__FrameInfo__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sentinel_interfaces__msg__FrameInfo__Sequence__copy(
  const sentinel_interfaces__msg__FrameInfo__Sequence * input,
  sentinel_interfaces__msg__FrameInfo__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sentinel_interfaces__msg__FrameInfo);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sentinel_interfaces__msg__FrameInfo * data =
      (sentinel_interfaces__msg__FrameInfo *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sentinel_interfaces__msg__FrameInfo__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sentinel_interfaces__msg__FrameInfo__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sentinel_interfaces__msg__FrameInfo__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
