#pragma once
#include "bot.h"

void hook_event_signal();
void unhook_event_signal();
void process_event(char* event_name);

extern Bot bot;
