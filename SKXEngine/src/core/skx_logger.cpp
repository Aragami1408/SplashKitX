#include "skx_logger.h"
#include "skx_asserts.h"
#include <platform/skx_platform.h>

// TODO: temporary
#include <stdio.h>
#include <string.h>
#include <stdarg.h>



b8 skx_initialize_logging() {
    // TODO: create log file
    return TRUE;
}
void skx_shutdown_logging() { 
    // TODO: cleanup logging/write queued entries.
}

void skx_log_output(SKXLogLevel level, const char *message, ...) {
    const char* level_strings[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: "};
    b8 is_error = level < SKXLogLevel::LOG_LEVEL_WARN;

    // Technically imposes a 32k character limit on a single log entry, but ...
    // DON'T DO THAT!
	const i32 msg_length = 32000;
	char out_message[msg_length];
    memset(out_message, 0, sizeof(out_message));

    // Format original message
    __builtin_va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(out_message, msg_length, message, arg_ptr);
    va_end(arg_ptr);

    char out_message2[msg_length];
    sprintf(out_message2, "%s%s\n", level_strings[level], out_message);

    // Platform-specific output
    if (is_error) {
        skx_console_write_error(out_message2, level);
    }
    else {
        skx_console_write(out_message2, level);
    }
}

void skx_report_assertion_failure(const char *expression, const char *message, const char *file, i32 line) {
    skx_log_output(LOG_LEVEL_FATAL, "Assertion Failure: %s, message: '%s', in file: %s, line: %d\n", expression, message, file, line);
}
