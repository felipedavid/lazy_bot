#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "logger.h"

const char *lvl_str[] = {
    [LOG_LVL_FATAL] = "FATAL",
    [LOG_LVL_ERROR] = "ERROR",
    [LOG_LVL_WARN]  = "WARN",
    [LOG_LVL_INFO]  = "INFO",
    [LOG_LVL_DEBUG] = "DEBUG",
    [LOG_LVL_TRACE] = "TRACE",
};

void log_output(Log_Level lvl, const char *msg, ...) {
    bool is_error = lvl < 2;

    static char buf[50000];

    va_list arg_ptr;
    va_start(arg_ptr, msg);
    vsnprintf(buf, sizeof(buf), msg, arg_ptr);
    va_end(arg_ptr);
    printf("[%s] %s\n", lvl_str[lvl], buf);
}