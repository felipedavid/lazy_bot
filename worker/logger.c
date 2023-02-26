#include "logger.h"
#include "stdio.h"
#include "wow.h"

const char *log_level_str[] = {
	[LOG_LEVEL_FATAL]   = "FATAL",
	[LOG_LEVEL_ERROR]   = "ERROR",
	[LOG_LEVEL_WARNING] = "WARNING",
	[LOG_LEVEL_INFO]    = "INFO",
};

Console_Text_Color log_level_color[] = {
	[LOG_LEVEL_FATAL]   = C_RED,
	[LOG_LEVEL_ERROR]   = C_RED,
	[LOG_LEVEL_WARNING] = C_YELLOW,
	[LOG_LEVEL_INFO]    = C_WHITE,
};

void log(Log_Level lvl, const char *fmt, ...) {
	// temporary
	static char buf[48000];
	static char buf2[48000];

	va_list args;
	va_start(args, fmt);
	vsprintf(buf, fmt, args);
	va_end(args);

	sprintf(buf2, "[%s] %s", log_level_str[lvl], buf);
	ConsoleWrite(buf2, log_level_color[lvl]);
}
