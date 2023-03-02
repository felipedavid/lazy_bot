#include <windows.h>
#include "object_manager.h"
#include "mem.h"
#include "commands.h"
#include "wow.h"
#include "fisher.h"

Object_Manager obj_mgr;
Fisher fisher;
HMODULE module_handle;
HWND window_handle;

BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam) {
	DWORD wnd_proc_id;
	GetWindowThreadProcessId(handle, &wnd_proc_id);

	if (GetCurrentProcessId() != wnd_proc_id) return TRUE;

	window_handle = handle;
	return FALSE; // window found abort search
}

HWND get_process_window() {
	window_handle = NULL;
	EnumWindows(enum_windows_callback, NULL);
	return window_handle;
}

WNDPROC orig_wndproc;
LRESULT __stdcall WndProc(const HWND h_wnd, UINT msg, WPARAM w_param, LPARAM l_param) {
	if (fisher.on) {
		fisher.pulse();
	}

	return CallWindowProc(orig_wndproc, h_wnd, msg, w_param, l_param);
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
	module_handle = module;
	switch (reason) {
	case DLL_PROCESS_ATTACH: {
		WoW::ConsolePrintf("Dll injected!");

		WoW::ConsolePrintf("Hooking wndproc");
		window_handle = get_process_window();
		orig_wndproc = (WNDPROC)SetWindowLongPtr(window_handle, GWL_WNDPROC, (LONG_PTR)WndProc);

		setup_commands();
	} break;
	case DLL_PROCESS_DETACH:
		WoW::ConsolePrintf("Dll unloaded!");
		break;
	}
	return TRUE;
}
