#include <core/skx_string.h>
#include <core/skx_memory.h>

#include <string.h>

SKX_API u64 skx_string_length(const char *str) {
	return strlen(str);
}
SKX_API char *skx_string_duplicate(const char *str) {
	u64 length = skx_string_length(str);
	char *copy = (char *)skx_allocate_memory(length + 1, MEMORY_TAG_STRING);
	skx_copy_memory(copy, str, length + 1);
	return copy;
}
