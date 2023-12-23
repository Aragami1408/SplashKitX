#pragma once

#include <skx_defines.h>

#define SKX_ASSERTIONS_ENABLED

#ifdef SKX_ASSERTIONS_ENABLED
  #if _MSC_VER
    #include <intrin.h>
    #define debugBreak() __debugbreak()
  #else
    #define debugBreak() __builtin_trap()
  #endif

  SKX_API void skx_report_assertion_failure(const char *expression, const char *message, const char *file, i32 line);

  #define SKX_ASSERT(expr)                                           \
    {                                                                \
      if (expr)                                                      \
      {                                                              \
      }                                                              \
      else                                                           \
      {                                                              \
        skx_report_assertion_failure(#expr, "", __FILE__, __LINE__); \
        debugBreak();                                                \
      }                                                              \
    }

  #define SKX_ASSERT_MSG(expr, message)                                   \
    {                                                                     \
      if (expr)                                                           \
      {                                                                   \
      }                                                                   \
      else                                                                \
      {                                                                   \
        skx_report_assertion_failure(#expr, message, __FILE__, __LINE__); \
        debugBreak();                                                     \
      }                                                                   \
    }

  #ifdef _DEBUG
  #define SKX_ASSERT_DEBUG(expr)                                           \
    {                                                                \
      if (expr)                                                      \
      {                                                              \
      }                                                              \
      else                                                           \
      {                                                              \
        skx_report_assertion_failure(#expr, "", __FILE__, __LINE__); \
        debugBreak();                                                \
      }                                                              \
    }
  #else
  #define SKX_ASSERT_DEBUG(expr) // Does nothing at all
  #endif

#else
#define SKX_ASSERT(expr)
#define SKX_ASSERT_MSG(expr)
#define SKX_ASSERT_DEBUG(expr)
#endif