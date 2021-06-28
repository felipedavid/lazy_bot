#include <windows.h>
#include <stdint.h>

#include "functions.hpp"
#include "objects/object.hpp"

#define ENUM_VISIBLE_OBJECTS_FUN_PTR 0x00468380
#define GET_OBJECT_PTR_FUN_PTR   0x00464870
#define GET_PLAYER_GUID_FUN_PTR      0x00468550

// call the 'callback' for each object passing their guid
void enumerate_visible_objects(void *callback) {
    typedef void (__fastcall* _enumerate_visible_objects)(void *callback, int32_t filter);
    _enumerate_visible_objects fun = 
        (_enumerate_visible_objects) ENUM_VISIBLE_OBJECTS_FUN_PTR;
    fun(callback, 0);
}

uint32_t get_object_ptr(uint64_t guid) {
    typedef uint32_t (__stdcall* _get_object_ptr)(uint64_t guid);
    _get_object_ptr fun = (_get_object_ptr) GET_OBJECT_PTR_FUN_PTR;
    return fun(guid);
}

uint64_t get_player_guid() {
    typedef uint64_t (__stdcall *_get_player_guid)();
    _get_player_guid fun = (_get_player_guid) GET_PLAYER_GUID_FUN_PTR;
    return fun();
}
