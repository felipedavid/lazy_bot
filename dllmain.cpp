// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "wow.h"
#include "memory.h"
#include "object_manager.h"

HWND window_handle;
HMODULE module_handle;

BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam) {
	DWORD wnd_proc_id;
	GetWindowThreadProcessId(handle, &wnd_proc_id);

	if (GetCurrentProcessId() != wnd_proc_id) return TRUE;

	window_handle = handle;
	return FALSE;
}

HWND get_process_window() {
	window_handle = NULL;
	EnumWindows(enum_windows_callback, NULL);
	return window_handle;
}

WNDPROC orig_wndproc;
LRESULT __stdcall WndProc(const HWND h_wnd, UINT msg, WPARAM w_param, LPARAM l_param) {
	if (msg == WM_USER) {
		typedef void(*_callback)(); 
        auto callback = (_callback)w_param;
        callback();
	}

	return CallWindowProc(orig_wndproc, h_wnd, msg, w_param, l_param);
}

Object_Manager object_manager;

void pulse() {
}

void pulse_cycle() {
    int sleep_time = 100;
    for (;;) {
        SendMessage(window_handle, WM_USER, (WPARAM)pulse, 0);

        auto cvar = WoW::CVar__Lookup("sleep_time");
        if (cvar) {
            sleep_time = atoi(cvar->value);
            log_info("logging time: %s", cvar->value);
        }
        Sleep(sleep_time);
    }
}

void fish_command() {
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)pulse_cycle, NULL, 0, NULL);
}

void unload_command() {
    log_warn("Unloading totally legit software >.>");
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FreeLibrary, module_handle, 0, NULL);
}

void objects_command() {
    object_manager.populate_objects();
    object_manager.log();
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    module_handle = hModule;
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
		log_warn("Totally legit software loaded >.>");

        write_memory<u8>((u8*)0x6571D1, 0x45);

        WoW::ConsoleCommandRegister("objects", objects_command, 0, 0, 0);
        WoW::ConsoleCommandRegister("fish", fish_command, 0, 0, 0);
        WoW::ConsoleCommandRegister("unload", unload_command, 0, 0, 0);

        WoW::CVar__Register("tick", "<nil>", 0, "100", NULL, 0, 0, 0, 0);

		window_handle = get_process_window();
		orig_wndproc = (WNDPROC)SetWindowLongPtr(window_handle, GWLP_WNDPROC, (LONG_PTR)WndProc);
        break;
    case DLL_PROCESS_DETACH:
        WoW::ConsoleCommandUnregister("fish");
        WoW::ConsoleCommandUnregister("unload");

        // TODO: Unregister cvars

        SetWindowLongPtr(window_handle, GWLP_WNDPROC, (LONG_PTR)orig_wndproc);
        break;
    }
    return TRUE;
}

