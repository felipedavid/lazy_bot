#include <stdint.h>
#include <stdbool.h>
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

#define CALL_LUA_FUN_PTR                  0x704CD0
#define GET_PLAYER_GUID_FUN_PTR           0x468550
#define ENUMERATE_VISIBLE_OBJECTS_FUN_PTR 0x468380
#define GET_OBJECT_FUN_PTR                0x464870
#define CLICK_TO_MOVE_FUN_PTR             0x611130
#define SET_TARGET_FUN_PTR                0x493540

extern _get_player_guid game_get_player_guid;
extern _enumerate_visible_objects game_enumerate_visible_objects;
extern _get_object_ptr game_get_object_ptr;

extern object_t local_player;

/* function wrappers */
void game_call_lua(const char *lua_command);
void click_to_move(position_t position);
void click_to_move_stop();
bool player_logged_in();
void cast_spell_by_name(const char *spell_name);
void set_target(object_t object);
