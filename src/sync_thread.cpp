#include <windows.h>
#include <stdio.h>

#include "utils.h"
#include "objects.h"
#include "local_player.h"
#include "game_functions.h"
#include "bot.h"

WNDPROC prev_window_proc;

#define UPDATE 666

LRESULT CALLBACK 
new_window_proc(HWND window_handle, UINT u_msg, WPARAM w_param, LPARAM l_param)
{
    switch (u_msg) {
        case UPDATE: 
            update(); 
            break;
    }
    // Call the original window procedure
    return CallWindowProc(prev_window_proc, window_handle, u_msg, w_param, l_param);
}

void hook_window_proc() {
    // Set our new_window_proc as the new window procedure
    prev_window_proc = 
        (WNDPROC) SetWindowLong(get_wow_window_handle(), 
                                GWL_WNDPROC, 
                                (LONG_PTR)&new_window_proc);
}

void run_update_on_main_thread() {
    SendMessage(get_wow_window_handle(), UPDATE, 0, 0);
}
