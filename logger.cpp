#include "pch.h"
#include "logger.h"
#include "stdarg.h"
#include "wow.h"

#include <stdio.h>

const char* log_level_str[] = {
	"FATAL",
	"ERROR",
	"WARNING",
	"INFO",
};

int log_level_colors[] = {
	3,
	3,
	4,
	0,
};

void log_output(Log_Level lvl, const char* fmt, ...) {
	static char buf1[24000];
	static char buf2[24000];

	va_list args;
	va_start(args, fmt);
	vsprintf_s(buf1, sizeof(buf1), fmt, args);
	va_end(args);

	sprintf_s(buf2, sizeof(buf2), "[%s] %s", log_level_str[lvl], buf1);
	WoW::ConsoleWrite(buf2, log_level_colors[lvl]);
}
