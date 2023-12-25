#pragma once

#include <skx_defines.h>

enum SKXMemoryTag {
    // For temporary use. Should be assigned one of the below or have a new tag created.
    MEMORY_TAG_UNKNOWN,
    MEMORY_TAG_ARRAY,
    MEMORY_TAG_DARRAY,
    MEMORY_TAG_DICT,
    MEMORY_TAG_RING_QUEUE,
    MEMORY_TAG_BST,
    MEMORY_TAG_STRING,
    MEMORY_TAG_APPLICATION,
    MEMORY_TAG_JOB,
    MEMORY_TAG_TEXTURE,
    MEMORY_TAG_MATERIAL_INSTANCE,
    MEMORY_TAG_RENDERER,
    MEMORY_TAG_GAME,
    MEMORY_TAG_TRANSFORM,
    MEMORY_TAG_ENTITY,
    MEMORY_TAG_ENTITY_NODE,
    MEMORY_TAG_SCENE,

    MEMORY_TAG_MAX_TAGS
};

void skx_initialize_memory();
void skx_shutdown_memory();

SKX_API void *skx_allocate_memory(u64 size, enum SKXMemoryTag tag);
SKX_API void skx_free_memory(void *block, u64 size, enum SKXMemoryTag tag);
SKX_API void *skx_zero_memory(void *block, u64 size);
SKX_API void *skx_copy_memory(void *dest, const void *source, u64 size);
SKX_API void *skx_set_memory(void *Dest, i32 value, u64 size);
SKX_API char *skx_get_memory_usage_str();