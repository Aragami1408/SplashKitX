#pragma once

#include <skx_defines.h>

/*
   Memory layout
   u64 capacity = number elements that can be held
   u64 length = number of elements currently contained
   u64 stride = size of each element in bytes
   void *elements
*/

enum {
   DARRAY_CAPACITY,
   DARRAY_LENGTH,
   DARRAY_STRIDE,
   DARRAY_FIELD_LENGTH
};

SKX_API void *_darray_create(u64 length, u64 stride);
SKX_API void _darray_destroy(void *array);

SKX_API u64 _darray_field_get(void *array, u64 field);
SKX_API void _darray_field_set(void *array, u64 field, u64 value);

SKX_API  void *_darray_resize(void *array);

SKX_API void *_darray_push(void *array, const void *value_ptr);
SKX_API void _darray_pop(void *array, void *dest);

SKX_API void *_darray_pop_at(void *array, u64 index, void *dest);
SKX_API void *_darray_insert_at(void *array, u64 index, void *value_ptr);

#define SKX_DARRAY_DEFAULT_CAPACITY 1
#define SKX_DARRAY_RESIZE_FACTOR 2

#define skx_darray_create(type) _darray_create(SKX_DARRAY_DEFAULT_CAPACITY, sizeof(type))

#define skx_darray_reserve(type, capacity) _darray_create(capacity, sizeof(type))

#define skx_darray_destroy(array) _darray_destroy(array)

#define skx_darray_push(array, value)     \
   {                                      \
      decltype(value) temp = value;         \
      array = (decltype(value)*) _darray_push(array, &temp); \
   }

#define skx_darray_pop(array, value_ptr) _darary_pop(array, value_ptr)

#define skx_darray_insert_at(array, index, value)     \
   {                                                  \
      decltype(value) temp = value;                     \
      array = _darray_insert_at(array, index, &temp); \
   }

#define skx_darray_pop_at(array, index, value_ptr) _darray_pop_at(array, index, value_ptr)

#define skx_darray_clear(array) _darray_field_set(array, DARRAY_LENGTH, 0)

#define skx_darray_capacity(array) _darray_field_get(array, DARRAY_CAPACITY)

#define skx_darray_length(array) _darray_field_get(array, DARRAY_LENGTH)

#define skx_darray_stride(array) _darray_field_get(array, DARRAY_STRIDE)

#define skx_darray_length_set(array, value) _darray_field_set(array, DARRAY_FIELD_LENGTH, value)
