#include <stdint.h>

#include "game_functions.h"
#include "sync_thread.h"

#define CALL_LUA_FUN_PTR                  0x704CD0
#define GET_PLAYER_GUID_FUN_PTR           0x468550
#define ENUMERATE_VISIBLE_OBJECTS_FUN_PTR 0x468380
#define GET_OBJECT_FUN_PTR                0x464870
#define CLICK_TO_MOVE_FUN_PTR             0x611130
#define SET_TARGET_FUN_PTR                0x493540

extern object_t local_player;

_get_player_guid game_get_player_guid = (_get_player_guid) GET_PLAYER_GUID_FUN_PTR;
_enumerate_visible_objects game_enumerate_visible_objects =
    (_enumerate_visible_objects) ENUMERATE_VISIBLE_OBJECTS_FUN_PTR;
_get_object_ptr game_get_object_ptr = (_get_object_ptr) GET_OBJECT_FUN_PTR;
_click_to_move game_click_to_move = (_click_to_move) CLICK_TO_MOVE_FUN_PTR;
_set_target game_set_target = (_set_target) SET_TARGET_FUN_PTR;

void game_call_lua(const char *lua_command) {
    __asm {
        pushad
        mov edx, new_window_proc 
        mov ecx, lua_command
        mov esi, CALL_LUA_FUN_PTR
        call esi
        popad
    }
}

void go_to(position_t position, click_type_t click_type) {
    uint64_t interact_guid_ptr = 0;
    game_click_to_move((void*)local_player.pointer, 
                       local_player.pointer, 
                       click_type, 
                       &interact_guid_ptr, 
                       &position, 2);
}
