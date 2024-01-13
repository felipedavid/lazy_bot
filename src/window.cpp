
namespace Window {

HWND handle = NULL;
b32 attached = false;
WNDPROC old_window_proc = NULL;

typedef void(* _run_on_wndproc_arg)();

void run_on_wndproc(_run_on_wndproc_arg callback) {
    assert(attached);

    SendMessage(handle, WM_USER, (WPARAM)callback, 0);
}

LRESULT new_window_proc(HWND window, u32 msg, WPARAM w_param, LPARAM l_param) {
    if (msg == WM_USER) {
        auto callback = (_run_on_wndproc_arg) w_param;
        callback();
        return 0;
    }

    return CallWindowProc(old_window_proc, handle, msg, w_param, l_param);
}

void attach(HWND window) {
    handle = window;
    old_window_proc = (WNDPROC) SetWindowLong(handle, GWL_WNDPROC, (u32)new_window_proc);
    if (old_window_proc == 0) {
        ConsolePrintf("Error: %d", GetLastError());
        return;
    }
    attached = true;
}

void dettach() {
    assert(attached);

    SetWindowLong(handle, GWL_WNDPROC, (u32)old_window_proc);
    attached = false;
}

}
