#include <windows.h>
#include <stdint.h>

#include "memory_manager.h"

uint32_t event = 0;
const uint32_t whatever_fun_ptr = 0x7040D0;
const uint32_t jump_back = 0x703E78;
__declspec(naked) void get_event_code_cave() {
    __asm {
        pushad
        mov event, edi
    }
    printf("%s\n", (char *) *(uint32_t *)event);
    __asm {
        popad
        call whatever_fun_ptr
        jmp jump_back
    }
}

void hook_event_signal() {
    const uint32_t hook_location = 0x00703E73;

    DWORD old_protect;
    VirtualProtect((void*)hook_location, 5, PAGE_EXECUTE_READWRITE, &old_protect);
    *(uint8_t *)hook_location = 0xE9; // jmp
    *(uint32_t *)(hook_location+1) = (uint32_t)&get_event_code_cave - ((uint32_t)hook_location + 5);
    VirtualProtect((void*)hook_location, 5, old_protect, &old_protect);
}

void unhook_event_signal() {
    const uint32_t hook_location = 0x00703E73;
    uint8_t original_code[5] = {0xE8, 0x58, 0x2, 0x0, 0x0};
    write_bytes(hook_location, original_code, sizeof(original_code));
}
