#pragma once

enum Log_Level {
	LOG_TYPE_FATAL,
	LOG_TYPE_ERROR,
	LOG_TYPE_WARNING,
	LOG_TYPE_INFO,
};

void log(Log_Level lvl, const char* fmt, ...);

#define log_fatal(fmt, ...) log(LOG_TYPE_FATAL, fmt, ##__VA_ARGS__)
#define log_error(fmt, ...) log(LOG_TYPE_ERROR, fmt, ##__VA_ARGS__)
#define log_info(fmt, ...)  log(LOG_TYPE_INFO, fmt, ##__VA_ARGS__)
#define log_warn(fmt, ...)  log(LOG_TYPE_WARNING, fmt, ##__VA_ARGS__)
