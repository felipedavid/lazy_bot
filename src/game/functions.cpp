#include <cstdint>

uint64_t get_player_guid() {
    static const uint32_t get_player_guid_fun_ptr = 0x00468550;
    return ((uint64_t (__stdcall*)())(get_player_guid_fun_ptr))();
}

uint32_t get_object_ptr(uint64_t guid) {
    static const uint32_t get_object_ptr_fun_ptr = 0x00464870;
    return ((uint32_t (__stdcall*)(uint64_t))(get_object_ptr_fun_ptr))(guid);
}
