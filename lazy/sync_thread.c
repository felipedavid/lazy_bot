#include <windows.h>
#include "bot.h"
#include "game_functions.h"

WNDPROC prev_window_proc;
WNDPROC never_change;
HWND wow_window;

char *lua_command_to_exec;

#define UPDATE 666

LRESULT CALLBACK new_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_USER) {
        game_call_lua(lua_command_to_exec);
    } else if (uMsg == UPDATE) {
        update(); 
        LRESULT result = CallWindowProc(never_change, hwnd, uMsg, wParam, lParam);
        return result;
    }
    return CallWindowProc(prev_window_proc, hwnd, uMsg, wParam, lParam);
}

void hook() {
    wow_window = FindWindow(NULL, "World of Warcraft");
    prev_window_proc = (WNDPROC) SetWindowLong(wow_window, GWL_WNDPROC, (LONG_PTR)&new_window_proc);
    never_change = prev_window_proc;
}

void run_lua_on_main_thread(char *lua_command) {
    lua_command_to_exec = lua_command;
    SendMessage(wow_window, WM_USER, 0, 0);
}

void run_update_on_main_thread() {
    SendMessage(wow_window, UPDATE, 0, 0);
}
