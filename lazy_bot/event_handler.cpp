#include <windows.h>
#include <cstdint>
#include <cstdio>

#include "event_handler.h"
#include "looting.h"

char* event_name;
const uint32_t whatever_fun_ptr = 0x7040D0;
const uint32_t jump_back = 0x703E78;
__declspec(naked) void get_event_code_cave() {
    __asm {
        call whatever_fun_ptr
        pushad
        mov event_name, edi
    }
    event_name = (char*)(*(uint32_t*)event_name);
    process_event(event_name);
    __asm {
        popad
        jmp jump_back
    }
}

void hook_event_signal() {
    const uint32_t hook_location = 0x00703E73;

    DWORD old_protect;
    VirtualProtect((void*)hook_location, 5, PAGE_EXECUTE_READWRITE, &old_protect);
    *(uint8_t*)hook_location = 0xE9; // jmp
    *(uint32_t*)(hook_location + 1) = (uint32_t)&get_event_code_cave - ((uint32_t)hook_location + 5);
    VirtualProtect((void*)hook_location, 5, old_protect, &old_protect);
}

void unhook_event_signal() {
    const u32 hook_location = 0x00703E73;
    u8 original_code[5] = { 0xE8, 0x58, 0x2, 0x0, 0x0 };

    DWORD old_protect;
    VirtualProtect((void*)hook_location, 5, PAGE_EXECUTE_READWRITE, &old_protect);
    for (int i = 0; i < sizeof(original_code); i++) {
        *(uint8_t*)(hook_location + i) = original_code[i];
    }
    VirtualProtect((void*)hook_location, 5, old_protect, &old_protect);
}

void process_event(char* event_name) {
    if(!strcmp(event_name, "LOOT_OPENED")) {
        bot.add_log("Loot:");
        Loot_Frame loot_frame;
        loot_frame.init();
    }
}
