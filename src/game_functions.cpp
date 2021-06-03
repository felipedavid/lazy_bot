#include <stdint.h>

#define ENUMERATE_VISIBLE_OBJECTS_FUN_PTR 0x00468380
#define GET_OBJECT_PTR_FUN_PTR            0x00464870

typedef uint32_t (__stdcall* _get_object_ptr)(uint64_t guid);
typedef void (__fastcall* _enumerate_visible_objects)(void *callback, int32_t filter);

// call the 'callback' for each object passing their guid
void enumerate_visible_objects(void *callback) {
    _enumerate_visible_objects fun = 
        (_enumerate_visible_objects) ENUMERATE_VISIBLE_OBJECTS_FUN_PTR;
    fun(callback, 0);
}

uint32_t get_object_ptr(uint64_t guid) {
    _get_object_ptr fun = (_get_object_ptr) GET_OBJECT_PTR_FUN_PTR;
    return fun(guid);
}
