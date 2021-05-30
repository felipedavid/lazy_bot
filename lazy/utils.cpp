#include <windows.h>
#include <stdint.h>
#include <stdio.h>

#include "sync_thread.h"

void fix_click_to_move() {
    uint32_t *click_to_move_fix_addr = (uint32_t *) 0x860A90;
    *click_to_move_fix_addr = 0;
}

// Enable protected lua functions
void unlock_lua() {
    uint8_t bytes_to_write[] = { 0xB8, 0x01, 0x00, 0x00, 0x00, 0xc3 };
    WriteProcessMemory(GetCurrentProcess(), 
                       (void *)0x494A50, 
                       (void*)bytes_to_write, 
                       sizeof(bytes_to_write), 
                       NULL); 
}

void create_console() {
    AllocConsole();
    FILE *file_dummy;
    freopen_s(&file_dummy, "CONOUT$", "w", stdout);
}

void setup_client() {
    hook_win_proc();
    unlock_lua();
    fix_click_to_move();
    create_console();
}
