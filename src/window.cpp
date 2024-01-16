// Replaces the window proc of the application enabling us to execute code in the main thread at any point,
// and allowing us to capture and handle messages sent to the window by redirecting them to ImGui.

HWND window = NULL;
WNDPROC originalWindowProc = NULL;

b32 CALLBACK enumWindowsCallback(HWND handle, LPARAM lParam) {
	DWORD windowProcID;
	GetWindowThreadProcessId(handle, &windowProcID);

	if (GetCurrentProcessId() != windowProcID) return true;

	window = handle;
	return false;
}

HWND getProcessWindow() {
	window = NULL;
	EnumWindows(enumWindowsCallback, NULL);
	return window;
}

LRESULT ourWindowProc(HWND window, u32 msg, WPARAM wParam, LPARAM lParam);

void takeoverWindowProc(HWND hwnd) {
    window = hwnd,
    originalWindowProc = (WNDPROC) SetWindowLong(hwnd, GWL_WNDPROC, (u32)ourWindowProc);
}

void givebackWindowProc() {
    SetWindowLong(window, GWL_WNDPROC, (u32)originalWindowProc);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
typedef void(* _RunCodeOnMainThreadCallback)();

LRESULT ourWindowProc(HWND window, u32 msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_USER) {
        auto callback = (_RunCodeOnMainThreadCallback) wParam;
        callback();
        return 0;
    }

	if (ImGui_ImplWin32_WndProcHandler(window, msg, wParam, lParam)) return true;

    auto io = ImGui::GetIO();
    if (io.WantCaptureKeyboard && (msg == WM_KEYDOWN)) return true;

    auto isMouseMessage = ((msg == WM_LBUTTONDOWN) || (msg == WM_LBUTTONUP));
    if (io.WantCaptureMouse && isMouseMessage) return true;

    return CallWindowProc(originalWindowProc, window, msg, wParam, lParam);
}

void runCodeOnMainThread(_RunCodeOnMainThreadCallback callback) {
    SendMessage(window, WM_USER, (WPARAM)callback, 0);
}
