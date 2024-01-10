#pragma once

#include <skx_defines.h>

SKX_API u64 skx_string_length(const char *str);
SKX_API char *skx_string_duplicate(const char *str);

// Case-sensitive string comparison. True if the same, otherwise false.
SKX_API b8 skx_strings_equal(const char *str0, const char *str1);
