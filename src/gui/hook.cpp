#include <windows.h>
#include <cstdio>

#include "..\utils.h"
#include "..\type.h"

// TODO: Rewrite this crap

u32 end_scene_fun_ptr = 0;
u32 i_scene_end_fun_ptr = 0x005A17A0;
byte original_code[6] = {0x56, 0x8b, 0xf1, 0x8b, 0x86, 0x38};

int __fastcall i_scene_end_hook(u32 addr) {
    end_scene_fun_ptr = read_u32(read_u32(read_u32(addr + 0x38A8)) + 0xa8);
    WriteProcessMemory(GetCurrentProcess(), (void*)i_scene_end_fun_ptr, (void*)original_code, 6, NULL);
    return ((int (__fastcall*)(u32 ptr))(i_scene_end_fun_ptr))(addr);
}

void get_end_scene_ptr() {
    u32 hook_location = i_scene_end_fun_ptr;
    byte new_code[6];
    new_code[0] = 0x68;
    *(u32 *)(new_code+1) = (u32)i_scene_end_hook;
    new_code[5] = 0xc3;

    WriteProcessMemory(GetCurrentProcess(), (void*)i_scene_end_fun_ptr, (void*)new_code, 6, NULL);

    // TODO: Put some sleeping time
    for(;;) {if (end_scene_fun_ptr != 0) break; printf("Not yet.\n");};
    printf("Endscene address = %x\n", end_scene_fun_ptr);
}
