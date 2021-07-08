#include <windows.h>
#include <stdint.h>
#include <string.h>

void unlock_lua() {
    void *buffer = (void *) 0x494A50;
    uint8_t new_stuff[] = { 0xB8, 0x01, 0x00, 0x00, 0x00, 0xc3 };
    WriteProcessMemory(GetCurrentProcess(), buffer, new_stuff, sizeof(new_stuff), NULL);
}

void fix_click_to_move() {
    *(uint32_t *) 0x860A90 = 0;
}
