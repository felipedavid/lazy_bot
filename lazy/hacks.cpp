#include <windows.h>
#include <stdint.h>
#include <stdio.h>

#include "hacks.h"
#include "object.h"
#include "object_manager.h"
#include "game_functions.h"

// TODO: See what make it crash
void __fastcall click_to_teleport(uint32_t class_garbage, 
                                  int32_t player_ptr, 
                                  uint64_t *interact_guid_ptr,
                                  click_type_t click_type,
                                  void *position_ptr,
                                  float precision) {
    if (running) {
        *(float *)(local_player.pointer + 0x9B8) = *(float *)position_ptr;
        *(float *)(local_player.pointer + 0x9BC) = *(float *)((uint32_t)position_ptr + 0x4);
        *(float *)(local_player.pointer + 0x9C0) = *(float *)((uint32_t)position_ptr + 0x8);
        printf("X: %.2f", *(float *)position_ptr);
    }
}

void toggle_click_to_teleport() {
    uint8_t *hook_location = (uint8_t *) (0x400000 + 0x2102EA);
    DWORD old_protect;
    VirtualProtect((void *)hook_location, 5, PAGE_EXECUTE_READWRITE, &old_protect);
    *(uint32_t *)(hook_location + 1) = 
        (uint32_t)&click_to_teleport - ((uint32_t)hook_location + 5);
}
