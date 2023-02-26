#pragma once
#include "stdarg.h"

typedef enum {
	LOG_LEVEL_FATAL,
	LOG_LEVEL_ERROR,
	LOG_LEVEL_WARNING,
	LOG_LEVEL_INFO,
} Log_Level;

#define log_fatal(fmt, ...)   log(LOG_LEVEL_FATAL,   fmt, ##__VA_ARGS__)
#define log_error(fmt, ...)   log(LOG_LEVEL_ERROR,   fmt, ##__VA_ARGS__)
#define log_warning(fmt, ...) log(LOG_LEVEL_WARNING, fmt, ##__VA_ARGS__)
#define log_info(fmt, ...)    log(LOG_LEVEL_INFO, fmt, ##__VA_ARGS__)
