#include <windows.h>
#include <stdint.h>
#include <stdio.h>

#include "hacks.h"
#include "object.h"

uint32_t position_addr = 0;
uint32_t return_addr = 0x6102ef;
__declspec(naked) void click_to_teleport_code_cave() {
    __asm {
        pushad
        mov eax, dword ptr ds:[esp + 0x30]
        mov position_addr, eax
        popad
        sub esp, 0x10
        jmp return_addr
    }
}

void toggle_click_to_teleport() {
    uint8_t *hook_location = (uint8_t *) (0x400000 + 0x21113E);
    if (*hook_location == 0xE8) { // is not hooked
        DWORD old_protect;
        VirtualProtect((void *)hook_location, 5, PAGE_EXECUTE_READWRITE, &old_protect);
        *hook_location = 0xE9;
        *(uint32_t *)(hook_location + 1) = (uint32_t)&click_to_teleport_code_cave - ((uint32_t)hook_location + 5);
    } else { // is hooked
        uint8_t original_code[] = {0xE8, 0x1D, 0xEA, 0xFF, 0xFF};
        WriteProcessMemory(GetCurrentProcess(), (void*)hook_location, 
                (void *)original_code, sizeof(original_code), NULL);
    }
}

void show_position() {
    position_t *pos = (position_t *) position_addr;
    printf("X: %.2f  Y: %.2f  Z: %.2f\n", pos->x, pos->y, pos->z);
}
