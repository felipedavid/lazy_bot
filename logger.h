#pragma once

enum Log_Level {
	LOG_TYPE_FATAL,
	LOG_TYPE_ERROR,
	LOG_TYPE_WARNING,
	LOG_TYPE_INFO,
};

void log_output(Log_Level lvl, const char* fmt, ...);

#define log_fatal(msg, ...) log_output(LOG_TYPE_FATAL, msg, __VA_ARGS__);
#define log_error(msg, ...) log_output(LOG_TYPE_ERROR, msg, __VA_ARGS__);
#define log_warn(msg, ...)  log_output(LOG_TYPE_WARNING, msg, __VA_ARGS__);
#define log_info(msg, ...)  log_output(LOG_TYPE_INFO, msg, __VA_ARGS__);
