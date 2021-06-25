#include <stdint.h>

int callback(uint32_t garbage, int filter, uint64_t guid) {
    uint32_t obj_pointer = get_object_pointer(guid);
    const uint32_t OBJECT_TYPE_OFFSET = 0x14;
    auto obj_type = read_memory<ObjectType>(obj_pointer + OBJECT_TYPE_OFFSET);
}
