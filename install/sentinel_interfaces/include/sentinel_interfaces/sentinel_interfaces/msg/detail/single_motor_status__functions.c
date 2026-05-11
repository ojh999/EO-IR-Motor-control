// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sentinel_interfaces:msg/SingleMotorStatus.idl
// generated code does not contain a copyright notice
#include "sentinel_interfaces/msg/detail/single_motor_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
sentinel_interfaces__msg__SingleMotorStatus__init(sentinel_interfaces__msg__SingleMotorStatus * msg)
{
  if (!msg) {
    return false;
  }
  // position
  // load
  // temperature
  // hw_error
  return true;
}

void
sentinel_interfaces__msg__SingleMotorStatus__fini(sentinel_interfaces__msg__SingleMotorStatus * msg)
{
  if (!msg) {
    return;
  }
  // position
  // load
  // temperature
  // hw_error
}

bool
sentinel_interfaces__msg__SingleMotorStatus__are_equal(const sentinel_interfaces__msg__SingleMotorStatus * lhs, const sentinel_interfaces__msg__SingleMotorStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // position
  if (lhs->position != rhs->position) {
    return false;
  }
  // load
  if (lhs->load != rhs->load) {
    return false;
  }
  // temperature
  if (lhs->temperature != rhs->temperature) {
    return false;
  }
  // hw_error
  if (lhs->hw_error != rhs->hw_error) {
    return false;
  }
  return true;
}

bool
sentinel_interfaces__msg__SingleMotorStatus__copy(
  const sentinel_interfaces__msg__SingleMotorStatus * input,
  sentinel_interfaces__msg__SingleMotorStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // position
  output->position = input->position;
  // load
  output->load = input->load;
  // temperature
  output->temperature = input->temperature;
  // hw_error
  output->hw_error = input->hw_error;
  return true;
}

sentinel_interfaces__msg__SingleMotorStatus *
sentinel_interfaces__msg__SingleMotorStatus__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__msg__SingleMotorStatus * msg = (sentinel_interfaces__msg__SingleMotorStatus *)allocator.allocate(sizeof(sentinel_interfaces__msg__SingleMotorStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sentinel_interfaces__msg__SingleMotorStatus));
  bool success = sentinel_interfaces__msg__SingleMotorStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sentinel_interfaces__msg__SingleMotorStatus__destroy(sentinel_interfaces__msg__SingleMotorStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sentinel_interfaces__msg__SingleMotorStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sentinel_interfaces__msg__SingleMotorStatus__Sequence__init(sentinel_interfaces__msg__SingleMotorStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__msg__SingleMotorStatus * data = NULL;

  if (size) {
    data = (sentinel_interfaces__msg__SingleMotorStatus *)allocator.zero_allocate(size, sizeof(sentinel_interfaces__msg__SingleMotorStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sentinel_interfaces__msg__SingleMotorStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sentinel_interfaces__msg__SingleMotorStatus__fini(&data[i - 1]);
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
sentinel_interfaces__msg__SingleMotorStatus__Sequence__fini(sentinel_interfaces__msg__SingleMotorStatus__Sequence * array)
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
      sentinel_interfaces__msg__SingleMotorStatus__fini(&array->data[i]);
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

sentinel_interfaces__msg__SingleMotorStatus__Sequence *
sentinel_interfaces__msg__SingleMotorStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__msg__SingleMotorStatus__Sequence * array = (sentinel_interfaces__msg__SingleMotorStatus__Sequence *)allocator.allocate(sizeof(sentinel_interfaces__msg__SingleMotorStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sentinel_interfaces__msg__SingleMotorStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sentinel_interfaces__msg__SingleMotorStatus__Sequence__destroy(sentinel_interfaces__msg__SingleMotorStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sentinel_interfaces__msg__SingleMotorStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sentinel_interfaces__msg__SingleMotorStatus__Sequence__are_equal(const sentinel_interfaces__msg__SingleMotorStatus__Sequence * lhs, const sentinel_interfaces__msg__SingleMotorStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sentinel_interfaces__msg__SingleMotorStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sentinel_interfaces__msg__SingleMotorStatus__Sequence__copy(
  const sentinel_interfaces__msg__SingleMotorStatus__Sequence * input,
  sentinel_interfaces__msg__SingleMotorStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sentinel_interfaces__msg__SingleMotorStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sentinel_interfaces__msg__SingleMotorStatus * data =
      (sentinel_interfaces__msg__SingleMotorStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sentinel_interfaces__msg__SingleMotorStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sentinel_interfaces__msg__SingleMotorStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sentinel_interfaces__msg__SingleMotorStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
