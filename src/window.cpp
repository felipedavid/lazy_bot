// Exchange the application's window proc, so that we can run code in the main thread any time,
// and so we can intercept messages sent to the window passing them to ImGui

HWND window = NULL;
WNDPROC original_window_proc = NULL;

b32 CALLBACK enum_windows_callback(HWND handle, LPARAM l_param) {
	DWORD window_proc_id;
	GetWindowThreadProcessId(handle, &window_proc_id);

	if (GetCurrentProcessId() != window_proc_id) return true;

	window = handle;
	return false;
}

HWND get_process_window() {
	window = NULL;
	EnumWindows(enum_windows_callback, NULL);
	return window;
}

LRESULT our_window_proc(HWND window, u32 msg, WPARAM w_param, LPARAM l_param);

void takeover_window_proc(HWND hwnd) {
    window = hwnd,
    original_window_proc = (WNDPROC) SetWindowLong(hwnd, GWL_WNDPROC, (u32)our_window_proc);
}

void giveback_window_proc() {
    SetWindowLong(window, GWL_WNDPROC, (u32)original_window_proc);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
typedef void(* _run_on_wndproc_arg)();

LRESULT our_window_proc(HWND window, u32 msg, WPARAM w_param, LPARAM l_param) {
    if (msg == WM_USER) {
        auto callback = (_run_on_wndproc_arg) w_param;
        callback();
        return 0;
    }

	if (ImGui_ImplWin32_WndProcHandler(window, msg, w_param, l_param)) return true;

    auto io = ImGui::GetIO();
    if ((io.WantCaptureMouse || io.WantCaptureKeyboard) && msg != WM_KEYUP) return true;

    return CallWindowProc(original_window_proc, window, msg, w_param, l_param);
}

void run_code_on_main_thread(_run_on_wndproc_arg callback) {
    SendMessage(window, WM_USER, (WPARAM)callback, 0);
}
