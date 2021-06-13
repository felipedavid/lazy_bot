#include <windows.h>
#include <stdint.h>

#include "game_functions.h"
#include "objects.h"

#define ENUM_VISIBLE_OBJECTS_FUN_PTR 0x00468380
#define GET_OBJECT_PTR_FUN_PTR       0x00464870
#define CLICK_TO_MOVE_FUN_PTR        0x00611130
#define SET_TARGET_FUN_PTR           0x00493540
#define CALL_LUA_FUN_PTR             0x00704CD0 
#define GET_PLAYER_GUID_FUN_PTR      0x00468550
#define GET_CREATURE_TYPE_FUN_PTR    0x00605570
#define GET_UNIT_REACTION_FUN_PTR    0x006061E0

// call the 'callback' for each object passing their guid
void enumerate_visible_objects(void *callback) {
    typedef void (__fastcall* _enumerate_visible_objects)(void *callback, int32_t filter);
    _enumerate_visible_objects fun = 
        (_enumerate_visible_objects) ENUM_VISIBLE_OBJECTS_FUN_PTR;
    fun(callback, 0);
}

void set_object_ptr(object_t *object) {
    typedef uint32_t (__stdcall* _get_object_ptr)(uint64_t guid);
    _get_object_ptr fun = (_get_object_ptr) GET_OBJECT_PTR_FUN_PTR;
    object->pointer = fun(object->guid);
}

void click_to_move(position_t position, click_type_t click_type) {
    typedef void (__fastcall* _click_to_move)(uint32_t garbage, 
                                              uint32_t player_ptr, 
                                              click_type_t click_type,
                                              uint64_t *interact_guid, 
                                              position_t *position, 
                                              float precision);
    _click_to_move fun = (_click_to_move) CLICK_TO_MOVE_FUN_PTR; 
    uint64_t interact_guid = 0;
    fun(local_player->pointer, local_player->pointer, click_type, &interact_guid, &position, 2);
}

void set_target(object_t object) {
    typedef uint32_t (__stdcall* _set_target)(uint64_t target_guid);
    _set_target fun = (_set_target) SET_TARGET_FUN_PTR;
    fun(object.guid);
}

void call_lua(char *code) {
    typedef uint32_t (__fastcall* _call_lua)(char *code, void *no_idea);
    _call_lua fun = (_call_lua) CALL_LUA_FUN_PTR;
    fun(code, (void*)CALL_LUA_FUN_PTR);
}

uint64_t get_player_guid() {
    typedef uint64_t (__stdcall* _get_player_guid)();
    _get_player_guid fun = (_get_player_guid) GET_PLAYER_GUID_FUN_PTR;
    return fun();
}

uint32_t get_creature_type(object_t object) {
    typedef uint32_t (__fastcall* _get_creature_type)(uint32_t garbage, uint32_t unit_ptr);
    _get_creature_type fun = (_get_creature_type) GET_CREATURE_TYPE_FUN_PTR;
    return fun(object.pointer, object.pointer);
}

uint32_t get_unit_reaction(object_t object) {
    typedef uint32_t (__fastcall* _get_unit_reaction)
        (uint32_t garbage, uint32_t player_ptr, uint32_t unit_ptr);
    _get_unit_reaction fun = (_get_unit_reaction) GET_UNIT_REACTION_FUN_PTR;
    return fun(local_player->pointer, object.pointer, local_player->pointer);
}
