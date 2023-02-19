#include "common.h"
#include "logger.h"

#include <stdio.h>
#include <stdarg.h>
#include <windows.h>

HANDLE logger_pipe;

void setup_logger() {
    logger_pipe = CreateFile("\\\\.\\pipe\\lazy_logger", GENERIC_WRITE|GENERIC_READ,
		0, NULL, OPEN_EXISTING, 0, NULL);
	if (!logger_pipe) {
        exit(-1);
	}
}

const char *log_lvl_str[] = {
    [LOG_LVL_FATAL] = "FATAL",
    [LOG_LVL_ERROR] = "ERROR",
    [LOG_LVL_WARNING] = "WARNING",
    [LOG_LVL_INFO] = "INFO",
};

void log(Log_Level lvl, const char *msg, ...) {
    char buf[40000];

    va_list arg_ptr;
    va_start(arg_ptr, msg);
    vsnprintf(buf, sizeof(buf), msg, arg_ptr);
    va_end(arg_ptr);
    u32 len = sprintf(buf, "[%s] %s\n", log_lvl_str[lvl], buf);

    u32 written;
    WriteFile(logger_pipe, "Hello pipe", 12, &written, NULL);
}