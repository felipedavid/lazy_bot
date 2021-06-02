#include <windows.h>
#include <stdio.h>

void create_console() {
    AllocConsole();
    FILE *file_dummy;
    freopen_s(&file_dummy, "CONOUT$", "w", stdout);
}
