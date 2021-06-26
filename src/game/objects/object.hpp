#include <stdint.h>

typedef struct {
    float x;
    float y;
    float z;
} Position;

class WowObject {
    const uint32_t pos_x_offset = 0x9B8;
    const uint32_t pos_y_offset = 0x9BC;
    const uint32_t pos_z_offset = 0x9C0;

    uint64_t guid;
    uint32_t pointer;
    ObjectType type;

    WowObject(uint64_t obj_guid, uint32_t obj_pointer, ObjectType obj_type);
    Position get_position();
    void log_object_info();
    uint32_t get_pointer();
    uint64_t get_guid();
    ObjectType get_object_type();
}
