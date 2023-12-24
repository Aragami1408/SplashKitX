#pragma once

#include <skx_defines.h>
#include <core/skx_logger.h>

class SKXPlatformState {
public:
    void *internal_state;

    b8 startup(const char *application_name, i32 x, i32 y, i32 width, i32 height);  
    void shutdown();
    b8 pump_messages();



};

void *skx_mem_allocate(u64 size, b8 aligned);
void skx_mem_free(void *block, b8 aligned);
void *skx_zero_memory(void *block, u64 size);
void *skx_copy_memory(void *dest, const void *source, u64 size);
void *skx_set_memory(void *dest, i32 value, u64 size);

void skx_console_write(const char *message, u8 color);
void skx_console_write_error(const char *message, u8 color);

f64 skx_get_absolute_time();

void skx_sleep(u64 ms);