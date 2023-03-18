#pragma once
#include "defs.h"
#include <windows.h>

typedef void (*Callback_Main_Thread)(u32 param);

void window_proc_init();
void window_proc_release();
void run_on_main_thread(Callback_Main_Thread, u32);
