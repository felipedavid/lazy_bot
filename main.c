#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"
#include "defs.h"
#include "object_manager.h"
#include "fisher.h"

#pragma comment (lib, "user32.lib")

#include <windows.h>
#include <stdio.h>

void test(HMODULE module) {
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	Object_Manager object_manager;
	object_manager_init(&object_manager);

	Fisher fisher;

	b32 running = false;
	for (;;) {
		if (GetAsyncKeyState(VK_DELETE) & 1) {
			break;
		}

		if (GetAsyncKeyState(VK_HOME) & 1) {
			running = !running;
			if (running) {
				fisher_init(&fisher, &object_manager);
			}
		}

		if (running) {
			run_on_main_thread(fisher_tick, &fisher);
		}
		Sleep(fisher.next_sleep_duration);
	}

	FreeConsole();
	FreeLibraryAndExitThread(module, 0);
}

BOOL DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
	switch (reason) {
	case DLL_PROCESS_ATTACH:
		window_proc_init();
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) test, module, 0, NULL);
		break;
	case DLL_PROCESS_DETACH:
		window_proc_release();
		break;
	}
	return TRUE;
}
