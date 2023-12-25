#pragma once

#include <skx_defines.h>

/*
   Memory layout
   u64 capacity = number elements that can be held
   u64 length = number of elements currently contained
   u64 stride = size of each element in bytes
   void *elements
*/
