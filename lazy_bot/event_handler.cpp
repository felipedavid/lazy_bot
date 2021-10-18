#include <windows.h>
#include <cstdint>
#include <cstdio>

#include "event_handler.h"
#include "looting.h"
#include "utils.h"

char* event_name;
const uint32_t whatever_fun_ptr = 0x7040D0;
const uint32_t jump_back = 0x703E78;
__declspec(naked) void get_event_code_cave() {
    __asm {
        call whatever_fun_ptr
        pushad
        mov event_name, edi
    }
    event_name = (char*)(read<u32>((u32)event_name));
    process_event(event_name);
    __asm {
        popad
        jmp jump_back
    }
}

void hook_event_signal() {
    const uint32_t hook_location = 0x00703E73;
    u8 hook[5] = { 0xE9 };
    *(u32*)(hook+1) = (u32)&get_event_code_cave - ((u32)hook_location + 5); // Computing relative address
    write_to_memory((u8*)hook_location, hook, 5);
}

void unhook_event_signal() {
    const u32 hook_location = 0x00703E73;
    u8 original_code[5] = { 0xE8, 0x58, 0x2, 0x0, 0x0 };
    write_to_memory((u8*)hook_location, original_code, 5);
}

void process_event(char* event_name) {
    if(!strcmp(event_name, "LOOT_OPENED")) {
        //bot.log("Loot opened.");
        // For now, just use auto loot
        //Loot_Frame loot_frame;
        //loot_frame.init();
    }
}
