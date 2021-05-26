#include <windows.h>
//#include "game_functions.h"

WNDPROC prevWndProc;
WNDPROC never_change;
HWND wow_window;

char *lua_function_to_exec;

#define MELLO 1231

LRESULT CALLBACK myNewWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_USER) {
        game_call_lua(lua_function_to_exec);
    } else if (uMsg == MELLO) {
        update(); 
        LRESULT result = CallWindowProc(never_change, hwnd, uMsg, wParam, lParam); // Access violation on some maps
        return result;
    }
    return CallWindowProc(prevWndProc, hwnd, uMsg, wParam, lParam); // Access violation on some maps
}

void sync() {
    wow_window = FindWindow(NULL, "World of Warcraft");
    prevWndProc = (WNDPROC) SetWindowLong(wow_window, GWL_WNDPROC, (LONG_PTR)&myNewWndProc);
    never_change = prevWndProc;
}

void invoke(char *lua_function) {
    lua_function_to_exec = lua_function;
    SendMessage(wow_window, WM_USER, 0, 0);
}

void invoke_update() {
    SendMessage(wow_window, MELLO, 0, 0);
}
