#include <stdint.h>
#include "object.h"

void game_call_lua(const char *lua_command);


typedef uint64_t (__cdecl* get_player_guid_ft)();
typedef uint32_t (__stdcall* get_object_ptr_ft)(uint64_t guid);
typedef uint32_t (__fastcall* enumerate_visible_objects_ft)
    (void *callback, int32_t filter); // Iterate over objects visible by the 
                                      // player and call the 'callback' for
                                      // each one of them passing their guid
                                      // as parameter.
typedef void (__fastcall* click_to_move_ft)
    (void* garbage, int32_t player_ptr, click_type_t click_type, 
     uint64_t *interact_guid_ptr, position_t *position_ptr, float precision);
typedef void (__stdcall* set_target_ft)(uint64_t guid);

get_player_guid_ft game_get_player_guid = (get_player_guid_ft) 0x468550;
enumerate_visible_objects_ft game_enumerate_visible_objects = 
    (enumerate_visible_objects_ft) 0x00468380;
get_object_ptr_ft game_get_object_ptr = (get_object_ptr_ft) 0x00464870;
click_to_move_ft game_click_to_move = (click_to_move_ft) 0x00611130;
set_target_ft game_set_target = (set_target_ft) 0x00493540;
