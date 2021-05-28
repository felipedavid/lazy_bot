#include <windows.h>
void hook_win_proc();
void run_lua_on_main_thread(char *lua_command);
void run_update_on_main_thread();
LRESULT CALLBACK new_window_proc(HWND window_handle, UINT u_msg, WPARAM w_param, LPARAM l_param);
