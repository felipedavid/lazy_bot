#pragma once
#include "common.h"

#define LOG_WARN_ENABLED  1
#define LOG_INFO_ENABLED  1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

typedef enum {
    LOG_LVL_FATAL = 0, // Crash
    LOG_LVL_ERROR = 1, // The application will try to recover
    LOG_LVL_WARN  = 2, // Something is not right, but we can still keep going
    LOG_LVL_INFO  = 3,
    LOG_LVL_DEBUG = 4,
    LOG_LVL_TRACE = 5,
} Log_Level;

void log_output(Log_Level, const char *msg, ...);

#define log_fatal(msg, ...) log_output(LOG_LVL_FATAL, msg, ##__VA_ARGS__);
#define log_error(msg, ...) log_output(LOG_LVL_ERROR, msg, ##__VA_ARGS__);

#if LOG_WARN_ENABLED == 1
#define log_warn(msg, ...) log_output(LOG_LVL_WARN, msg, ##__VA_ARGS__);
#else
#define log_warn(msg, ...)
#endif

#if LOG_INFO_ENABLED == 1
#define log_info(msg, ...) log_output(LOG_LVL_INFO, msg, ##__VA_ARGS__);
#else
#define log_info(msg, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
#define log_debug(msg, ...) log_output(LOG_LVL_DEBUG, msg, ##__VA_ARGS__);
#else
#define log_debug(msg, ...)
#endif

#if LOG_TRACE_ENABLED == 1
#define log_trace(msg, ...) log_output(LOG_LVL_TRACE, msg, ##__VA_ARGS__);
#else
#define log_trace(msg, ...)
#endif
