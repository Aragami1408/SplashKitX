#pragma once

#include <skx_defines.h>

#define SKX_LOG_WARN_ENABLED 1
#define SKX_LOG_INFO_ENABLED 1
#define SKX_LOG_DEBUG_ENABLED 1
#define SKX_LOG_TRACE_ENABLED 1

// Disable debug and trace logging for release builds
#if SKX_RELEASE == 1
  #define SKX_LOG_DEBUG_ENABLED 0
  #define SKX_LOG_TRACE_ENABLED 0
#endif

enum SKXLogLevel {
  LOG_LEVEL_FATAL,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_WARN,
  LOG_LEVEL_INFO,
  LOG_LEVEL_DEBUG,
  LOG_LEVEL_TRACE,
};

b8 skx_initialize_logging();
void skx_shutdown_logging();

SKX_API void skx_log_output(enum SKXLogLevel level, const char *message, ...);

// Logs a fatal-level 
#define SKX_FATAL(message, ...) skx_log_output(SKXLogLevel::LOG_LEVEL_FATAL, message, ##__VA_ARGS__);

#ifndef SKX_ERROR
#define SKX_ERROR(message, ...) skx_log_output(SKXLogLevel::LOG_LEVEL_ERROR, message, ##__VA_ARGS__);
#endif

#if SKX_LOG_WARN_ENABLED == 1
  #define SKX_WARN(message, ...) skx_log_output(SKXLogLevel::LOG_LEVEL_WARN, message, ##__VA_ARGS__);
#else
  #define SKX_WARN(message, ...)
#endif

#if SKX_LOG_INFO_ENABLED == 1
  #define SKX_INFO(message, ...) skx_log_output(SKXLogLevel::LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#else
  #define SKX_INFO(message, ...)
#endif

#if SKX_LOG_DEBUG_ENABLED == 1
  #define SKX_DEBUG(message, ...) skx_log_output(SKXLogLevel::LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#else
  #define SKX_DEBUG(message, ...)
#endif

#if SKX_LOG_TRACE_ENABLED == 1
  #define SKX_TRACE(message, ...) skx_log_output(SKXLogLevel::LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
#else
  #define SKX_TRACE(message, ...)
#endif
