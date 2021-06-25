#include <stdint.h>

#include "../memory_manager.h"

typedef struct {
    float x;
    float y;
    float z;
} Position;

class WowObject {
    uint64_t guid;
    uint32_t pointer;
    ObjectType type;

    WowObject(uint64_t obj_guid, uint32_t obj_pointer, ObjectType obj_type);
    Vector3 get_position();
    void log_object_info();
    uint32_t get_descriptor_fields() { return read_memory<uint32_t>(pointer + DescriptorFieldsOffset };
    uint32_t get_pointer() { return pointer };
    uint64_t get_guid() { return guid };
    ObjectType get_object_type() { return type };
}
