#include "common.h"
#include "logger.h"

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <windows.h>

HANDLE logger_pipe;

void setup_logger() {
    logger_pipe = CreateFile("\\\\.\\pipe\\lazy_logger", GENERIC_WRITE|GENERIC_READ,
		0, NULL, OPEN_EXISTING, 0, NULL);
	if (!logger_pipe) {
        exit(-1);
	}
}

char *log_lvl_str[] = {
    [LOG_LVL_FATAL] = "FATAL",
    [LOG_LVL_ERROR] = "ERROR",
    [LOG_LVL_WARNING] = "WARNING",
    [LOG_LVL_INFO] = "INFO",
};

char fmt_str[5012];
char end_str[5012];

void log(Log_Level lvl, const char *msg, ...) {
    va_list arg_ptr;
    va_start(arg_ptr, msg);
    vsnprintf(fmt_str, sizeof(fmt_str), msg, arg_ptr);
    va_end(arg_ptr);
    u32 len = snprintf(end_str, sizeof(end_str), "[%s] %s\n", log_lvl_str[lvl], fmt_str);

    u32 written;
    WriteFile(logger_pipe, end_str, len, &written, NULL);
}