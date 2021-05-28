#include <windows.h>
#include "bot.h"
#include "game_functions.h"

WNDPROC prev_window_proc;
HWND wow_window;

char *lua_command_to_exec;

#define UPDATE 666

LRESULT CALLBACK new_window_proc(HWND window_handle, UINT u_msg, WPARAM w_param, LPARAM l_param)
{
    switch (u_msg) {
        case WM_USER:
            game_call_lua(lua_command_to_exec);
            break;
        case UPDATE:
            update();
            break;
    }
    return CallWindowProc(prev_window_proc, window_handle, u_msg, w_param, l_param);
}

void hook_win_proc() {
    wow_window = FindWindow(NULL, "World of Warcraft");
    prev_window_proc = (WNDPROC) SetWindowLong(wow_window, GWL_WNDPROC, (LONG_PTR)&new_window_proc);
}

void run_lua_on_main_thread(char *lua_command) {
    lua_command_to_exec = lua_command;
    SendMessage(wow_window, WM_USER, 0, 0);
}

void run_update_on_main_thread() {
    SendMessage(wow_window, UPDATE, 0, 0);
}
