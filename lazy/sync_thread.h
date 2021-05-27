#include <windows.h>
void hook();
void run_lua_on_main_thread(char *lua_command);
void run_update_on_main_thread();
LRESULT CALLBACK new_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
