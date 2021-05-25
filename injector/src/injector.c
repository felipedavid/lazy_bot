#include <windows.h>
#include <stdint.h>
#include <stdbool.h>

#define DLL_PATH "W:\\lazy\\bin\\lazy_bot.dll"

void set_debug_privileges() {
    LUID luid;
    TOKEN_PRIVILEGES tp;
    HANDLE token_handle;
    OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &token_handle);
    LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid);

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    AdjustTokenPrivileges(token_handle, 
                          false, 
                          &tp, 
                          0,
                          (PTOKEN_PRIVILEGES) NULL,
                          (PDWORD) NULL);
}

HANDLE get_wow_handle() {
    HWND hwnd = NULL;
    while (!(hwnd = FindWindow(NULL, "World of Warcraft"))) Sleep(100);

    uint32_t proc_id;
    GetWindowThreadProcessId(hwnd, &proc_id);

    return OpenProcess(PROCESS_CREATE_THREAD |
                       PROCESS_QUERY_INFORMATION |
                       PROCESS_VM_OPERATION |
                       PROCESS_VM_WRITE |
                       PROCESS_VM_READ,
                       false,
                       proc_id);
}

void inject_dll() {
    HANDLE proc_handle = get_wow_handle();
    size_t len_dll_path = strlen(DLL_PATH) + 1;
    void *allocated_space = VirtualAllocEx(proc_handle, 
                                           NULL, 
                                           len_dll_path, 
                                           MEM_COMMIT|MEM_RESERVE, 
                                           PAGE_EXECUTE_READWRITE);

    WriteProcessMemory(proc_handle, allocated_space, DLL_PATH, len_dll_path, NULL);

    void *load_lib_addr = 
        GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "LoadLibraryA");

    HANDLE th = CreateRemoteThread(proc_handle, 
                                   NULL, 
                                   0, 
                                   (LPTHREAD_START_ROUTINE)load_lib_addr, 
                                   allocated_space, 
                                   0, 
                                   NULL);

    VirtualFreeEx(proc_handle, allocated_space, len_dll_path, MEM_DECOMMIT|MEM_RELEASE);
    CloseHandle(th);
}

void setup_windows_layout() {
    HANDLE wow_window  = FindWindow(NULL, "World of Warcraft");
    HANDLE logs_window = FindWindow(NULL, "WoW");
    HANDLE bot_window  = FindWindow(NULL, "Lazy Bot");

    SetWindowPos(wow_window,  HWND_TOP, -10, 0, 800, 600, 0);
    SetWindowPos(bot_window, HWND_TOP, 780, 0, 500, 250, 0);
    SetWindowPos(logs_window, HWND_TOP, 775, 245, 1376-775, 753-250, 0);
}

int main() {
    set_debug_privileges();
    inject_dll();
    Sleep(500);
    setup_windows_layout();
}
