// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from sentinel_interfaces:srv/SetBoolFlag.idl
// generated code does not contain a copyright notice
#include "sentinel_interfaces/srv/detail/set_bool_flag__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
sentinel_interfaces__srv__SetBoolFlag_Request__init(sentinel_interfaces__srv__SetBoolFlag_Request * msg)
{
  if (!msg) {
    return false;
  }
  // data
  return true;
}

void
sentinel_interfaces__srv__SetBoolFlag_Request__fini(sentinel_interfaces__srv__SetBoolFlag_Request * msg)
{
  if (!msg) {
    return;
  }
  // data
}

bool
sentinel_interfaces__srv__SetBoolFlag_Request__are_equal(const sentinel_interfaces__srv__SetBoolFlag_Request * lhs, const sentinel_interfaces__srv__SetBoolFlag_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // data
  if (lhs->data != rhs->data) {
    return false;
  }
  return true;
}

bool
sentinel_interfaces__srv__SetBoolFlag_Request__copy(
  const sentinel_interfaces__srv__SetBoolFlag_Request * input,
  sentinel_interfaces__srv__SetBoolFlag_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // data
  output->data = input->data;
  return true;
}

sentinel_interfaces__srv__SetBoolFlag_Request *
sentinel_interfaces__srv__SetBoolFlag_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__srv__SetBoolFlag_Request * msg = (sentinel_interfaces__srv__SetBoolFlag_Request *)allocator.allocate(sizeof(sentinel_interfaces__srv__SetBoolFlag_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sentinel_interfaces__srv__SetBoolFlag_Request));
  bool success = sentinel_interfaces__srv__SetBoolFlag_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sentinel_interfaces__srv__SetBoolFlag_Request__destroy(sentinel_interfaces__srv__SetBoolFlag_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sentinel_interfaces__srv__SetBoolFlag_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sentinel_interfaces__srv__SetBoolFlag_Request__Sequence__init(sentinel_interfaces__srv__SetBoolFlag_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__srv__SetBoolFlag_Request * data = NULL;

  if (size) {
    data = (sentinel_interfaces__srv__SetBoolFlag_Request *)allocator.zero_allocate(size, sizeof(sentinel_interfaces__srv__SetBoolFlag_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sentinel_interfaces__srv__SetBoolFlag_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sentinel_interfaces__srv__SetBoolFlag_Request__fini(&data[i - 1]);
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
sentinel_interfaces__srv__SetBoolFlag_Request__Sequence__fini(sentinel_interfaces__srv__SetBoolFlag_Request__Sequence * array)
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
      sentinel_interfaces__srv__SetBoolFlag_Request__fini(&array->data[i]);
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

sentinel_interfaces__srv__SetBoolFlag_Request__Sequence *
sentinel_interfaces__srv__SetBoolFlag_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__srv__SetBoolFlag_Request__Sequence * array = (sentinel_interfaces__srv__SetBoolFlag_Request__Sequence *)allocator.allocate(sizeof(sentinel_interfaces__srv__SetBoolFlag_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sentinel_interfaces__srv__SetBoolFlag_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sentinel_interfaces__srv__SetBoolFlag_Request__Sequence__destroy(sentinel_interfaces__srv__SetBoolFlag_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sentinel_interfaces__srv__SetBoolFlag_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sentinel_interfaces__srv__SetBoolFlag_Request__Sequence__are_equal(const sentinel_interfaces__srv__SetBoolFlag_Request__Sequence * lhs, const sentinel_interfaces__srv__SetBoolFlag_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sentinel_interfaces__srv__SetBoolFlag_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sentinel_interfaces__srv__SetBoolFlag_Request__Sequence__copy(
  const sentinel_interfaces__srv__SetBoolFlag_Request__Sequence * input,
  sentinel_interfaces__srv__SetBoolFlag_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sentinel_interfaces__srv__SetBoolFlag_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sentinel_interfaces__srv__SetBoolFlag_Request * data =
      (sentinel_interfaces__srv__SetBoolFlag_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sentinel_interfaces__srv__SetBoolFlag_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sentinel_interfaces__srv__SetBoolFlag_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sentinel_interfaces__srv__SetBoolFlag_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

bool
sentinel_interfaces__srv__SetBoolFlag_Response__init(sentinel_interfaces__srv__SetBoolFlag_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    sentinel_interfaces__srv__SetBoolFlag_Response__fini(msg);
    return false;
  }
  return true;
}

void
sentinel_interfaces__srv__SetBoolFlag_Response__fini(sentinel_interfaces__srv__SetBoolFlag_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
sentinel_interfaces__srv__SetBoolFlag_Response__are_equal(const sentinel_interfaces__srv__SetBoolFlag_Response * lhs, const sentinel_interfaces__srv__SetBoolFlag_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
sentinel_interfaces__srv__SetBoolFlag_Response__copy(
  const sentinel_interfaces__srv__SetBoolFlag_Response * input,
  sentinel_interfaces__srv__SetBoolFlag_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

sentinel_interfaces__srv__SetBoolFlag_Response *
sentinel_interfaces__srv__SetBoolFlag_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__srv__SetBoolFlag_Response * msg = (sentinel_interfaces__srv__SetBoolFlag_Response *)allocator.allocate(sizeof(sentinel_interfaces__srv__SetBoolFlag_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sentinel_interfaces__srv__SetBoolFlag_Response));
  bool success = sentinel_interfaces__srv__SetBoolFlag_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sentinel_interfaces__srv__SetBoolFlag_Response__destroy(sentinel_interfaces__srv__SetBoolFlag_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sentinel_interfaces__srv__SetBoolFlag_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sentinel_interfaces__srv__SetBoolFlag_Response__Sequence__init(sentinel_interfaces__srv__SetBoolFlag_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__srv__SetBoolFlag_Response * data = NULL;

  if (size) {
    data = (sentinel_interfaces__srv__SetBoolFlag_Response *)allocator.zero_allocate(size, sizeof(sentinel_interfaces__srv__SetBoolFlag_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sentinel_interfaces__srv__SetBoolFlag_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sentinel_interfaces__srv__SetBoolFlag_Response__fini(&data[i - 1]);
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
sentinel_interfaces__srv__SetBoolFlag_Response__Sequence__fini(sentinel_interfaces__srv__SetBoolFlag_Response__Sequence * array)
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
      sentinel_interfaces__srv__SetBoolFlag_Response__fini(&array->data[i]);
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

sentinel_interfaces__srv__SetBoolFlag_Response__Sequence *
sentinel_interfaces__srv__SetBoolFlag_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__srv__SetBoolFlag_Response__Sequence * array = (sentinel_interfaces__srv__SetBoolFlag_Response__Sequence *)allocator.allocate(sizeof(sentinel_interfaces__srv__SetBoolFlag_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sentinel_interfaces__srv__SetBoolFlag_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sentinel_interfaces__srv__SetBoolFlag_Response__Sequence__destroy(sentinel_interfaces__srv__SetBoolFlag_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sentinel_interfaces__srv__SetBoolFlag_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sentinel_interfaces__srv__SetBoolFlag_Response__Sequence__are_equal(const sentinel_interfaces__srv__SetBoolFlag_Response__Sequence * lhs, const sentinel_interfaces__srv__SetBoolFlag_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sentinel_interfaces__srv__SetBoolFlag_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sentinel_interfaces__srv__SetBoolFlag_Response__Sequence__copy(
  const sentinel_interfaces__srv__SetBoolFlag_Response__Sequence * input,
  sentinel_interfaces__srv__SetBoolFlag_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sentinel_interfaces__srv__SetBoolFlag_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sentinel_interfaces__srv__SetBoolFlag_Response * data =
      (sentinel_interfaces__srv__SetBoolFlag_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sentinel_interfaces__srv__SetBoolFlag_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sentinel_interfaces__srv__SetBoolFlag_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sentinel_interfaces__srv__SetBoolFlag_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "sentinel_interfaces/srv/detail/set_bool_flag__functions.h"

bool
sentinel_interfaces__srv__SetBoolFlag_Event__init(sentinel_interfaces__srv__SetBoolFlag_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    sentinel_interfaces__srv__SetBoolFlag_Event__fini(msg);
    return false;
  }
  // request
  if (!sentinel_interfaces__srv__SetBoolFlag_Request__Sequence__init(&msg->request, 0)) {
    sentinel_interfaces__srv__SetBoolFlag_Event__fini(msg);
    return false;
  }
  // response
  if (!sentinel_interfaces__srv__SetBoolFlag_Response__Sequence__init(&msg->response, 0)) {
    sentinel_interfaces__srv__SetBoolFlag_Event__fini(msg);
    return false;
  }
  return true;
}

void
sentinel_interfaces__srv__SetBoolFlag_Event__fini(sentinel_interfaces__srv__SetBoolFlag_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  sentinel_interfaces__srv__SetBoolFlag_Request__Sequence__fini(&msg->request);
  // response
  sentinel_interfaces__srv__SetBoolFlag_Response__Sequence__fini(&msg->response);
}

bool
sentinel_interfaces__srv__SetBoolFlag_Event__are_equal(const sentinel_interfaces__srv__SetBoolFlag_Event * lhs, const sentinel_interfaces__srv__SetBoolFlag_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!sentinel_interfaces__srv__SetBoolFlag_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!sentinel_interfaces__srv__SetBoolFlag_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
sentinel_interfaces__srv__SetBoolFlag_Event__copy(
  const sentinel_interfaces__srv__SetBoolFlag_Event * input,
  sentinel_interfaces__srv__SetBoolFlag_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!sentinel_interfaces__srv__SetBoolFlag_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!sentinel_interfaces__srv__SetBoolFlag_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

sentinel_interfaces__srv__SetBoolFlag_Event *
sentinel_interfaces__srv__SetBoolFlag_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__srv__SetBoolFlag_Event * msg = (sentinel_interfaces__srv__SetBoolFlag_Event *)allocator.allocate(sizeof(sentinel_interfaces__srv__SetBoolFlag_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(sentinel_interfaces__srv__SetBoolFlag_Event));
  bool success = sentinel_interfaces__srv__SetBoolFlag_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
sentinel_interfaces__srv__SetBoolFlag_Event__destroy(sentinel_interfaces__srv__SetBoolFlag_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    sentinel_interfaces__srv__SetBoolFlag_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
sentinel_interfaces__srv__SetBoolFlag_Event__Sequence__init(sentinel_interfaces__srv__SetBoolFlag_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__srv__SetBoolFlag_Event * data = NULL;

  if (size) {
    data = (sentinel_interfaces__srv__SetBoolFlag_Event *)allocator.zero_allocate(size, sizeof(sentinel_interfaces__srv__SetBoolFlag_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = sentinel_interfaces__srv__SetBoolFlag_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        sentinel_interfaces__srv__SetBoolFlag_Event__fini(&data[i - 1]);
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
sentinel_interfaces__srv__SetBoolFlag_Event__Sequence__fini(sentinel_interfaces__srv__SetBoolFlag_Event__Sequence * array)
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
      sentinel_interfaces__srv__SetBoolFlag_Event__fini(&array->data[i]);
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

sentinel_interfaces__srv__SetBoolFlag_Event__Sequence *
sentinel_interfaces__srv__SetBoolFlag_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  sentinel_interfaces__srv__SetBoolFlag_Event__Sequence * array = (sentinel_interfaces__srv__SetBoolFlag_Event__Sequence *)allocator.allocate(sizeof(sentinel_interfaces__srv__SetBoolFlag_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = sentinel_interfaces__srv__SetBoolFlag_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
sentinel_interfaces__srv__SetBoolFlag_Event__Sequence__destroy(sentinel_interfaces__srv__SetBoolFlag_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    sentinel_interfaces__srv__SetBoolFlag_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
sentinel_interfaces__srv__SetBoolFlag_Event__Sequence__are_equal(const sentinel_interfaces__srv__SetBoolFlag_Event__Sequence * lhs, const sentinel_interfaces__srv__SetBoolFlag_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!sentinel_interfaces__srv__SetBoolFlag_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
sentinel_interfaces__srv__SetBoolFlag_Event__Sequence__copy(
  const sentinel_interfaces__srv__SetBoolFlag_Event__Sequence * input,
  sentinel_interfaces__srv__SetBoolFlag_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(sentinel_interfaces__srv__SetBoolFlag_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    sentinel_interfaces__srv__SetBoolFlag_Event * data =
      (sentinel_interfaces__srv__SetBoolFlag_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!sentinel_interfaces__srv__SetBoolFlag_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          sentinel_interfaces__srv__SetBoolFlag_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!sentinel_interfaces__srv__SetBoolFlag_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
