#pragma once

typedef enum {
    LOG_LVL_FATAL,
    LOG_LVL_ERROR,
    LOG_LVL_WARNING,
    LOG_LVL_INFO,
} Log_Level; 

void log(Log_Level lvl, const char *msg, ...);

#define LFATAL(msg, ...) log(LOG_LVL_FATAL, msg, ##__VA_ARGS__);
#define LERROR(msg, ...) log(LOG_LVL_ERROR, msg, ##__VA_ARGS__);
#define LWARNING(msg, ...) log(LOG_LVL_WARNING, msg, ##__VA_ARGS__);
#define LINFO(msg, ...) log(LOG_LVL_INFO, msg, ##__VA_ARGS__);

void setup_logger();