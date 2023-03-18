/* This file allows us to run stuff on the process's main thread by setting up a new wndproc */
#include "window_proc.h"

HWND wow_window_handle;
WNDPROC wow_window_proc;

LRESULT new_window_proc(HWND window, UINT message, WPARAM w_param, LPARAM l_param) {
	if (message == WM_USER) {
		Callback_Main_Thread callback = (Callback_Main_Thread) w_param;
		u32 param = (u32) l_param;

		callback(param);

		return 0;
	}
	return CallWindowProc(wow_window_proc, window, message, w_param, l_param);
}

// Sets a new wndproc where our callbacks will run
void window_proc_init() {
	// TODO: Figure out a better way to get the handle to the window
	wow_window_handle = FindWindowA(NULL, "World of Warcraft");
	wow_window_proc = (WNDPROC) SetWindowLongA(wow_window_handle, GWL_WNDPROC, (LONG)new_window_proc);
}

void window_proc_release() {
	SetWindowLongA(wow_window_handle, GWL_WNDPROC, (LONG) wow_window_proc);
}

// WARNING: Before calling this function, you should setup the new wndproc by calling new_window_proc_setup
void run_on_main_thread(Callback_Main_Thread callback, u32 param) {
	SendMessage(wow_window_handle, WM_USER, (WPARAM)callback, (LPARAM)param);
}
