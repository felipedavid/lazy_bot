#include <stdint.h>
#include "object.h"

typedef uint64_t (__cdecl* _get_player_guid)();
typedef uint32_t (__stdcall* _get_object_ptr)(uint64_t guid);
typedef uint32_t (__fastcall* _enumerate_visible_objects)
    (void *callback, int32_t filter); // Iterate over objects visible by the 
                                      // player and call the 'callback' for
                                      // each one of them passing their guid
                                      // as parameter.
typedef void (__fastcall* _click_to_move)
    (void* garbage, int32_t player_ptr, click_type_t click_type, 
     uint64_t *interact_guid_ptr, position_t *position_ptr, float precision);
typedef void (__stdcall* _set_target)(uint64_t guid);

_get_player_guid game_get_player_guid;
_enumerate_visible_objects game_enumerate_visible_objects;
_get_object_ptr game_get_object_ptr;
_set_target game_set_target;

/* function wrappers */
void game_call_lua(const char *lua_command);
void go_to(position_t position, click_type_t click_type);
