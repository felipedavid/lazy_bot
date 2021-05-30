#include <stdint.h>

#include "game_functions.h"
#include "sync_thread.h"

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

void click_to_move(position_t position) {
    uint64_t interact_guid_ptr = 0; // no idea what this is.. but still works :)
    game_click_to_move((void*)local_player.pointer, 
                       local_player.pointer, 
                       MoveClick, 
                       &interact_guid_ptr, 
                       &position, 2);
}

void click_to_move_stop() {
    uint64_t interact_guid_ptr = 0; // no idea what this is.. but still works :)
    game_click_to_move((void*)local_player.pointer, 
                       local_player.pointer, 
                       NoneClick, 
                       &interact_guid_ptr, 
                       &(local_player.position), 2);
}

void set_target(object_t object) {
    game_set_target(object.guid);
}

bool player_logged_in() {
    return game_get_player_guid() > 0;
}

void cast_spell_by_name(const char *spell_name) {
    char lua_command[256] = "CastSpellByName('";
    strcat(lua_command, spell_name);
    strcat(lua_command, "')");

    run_lua_on_main_thread(lua_command);
}
