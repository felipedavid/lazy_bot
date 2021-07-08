#include <cstdint>
#include <cstdio>

#include "object.h"
#include "../../utils/memory_manager.h"
#include "../enums/object_type.h"
#include "../position.h"

uint32_t WowObject::get_descriptor_fields() {
    return read_uint(base_addr + descriptor_fields_offset);
}

Position WowObject::get_position() {
    float pos_x = read_float(base_addr + position_x_offset);
    float pos_y = read_float(base_addr + position_x_offset + 0x4);
    float pos_z = read_float(base_addr + position_x_offset + 0x8);

    Position pos{pos_x, pos_y, pos_z};
    return pos;
}

ObjectType WowObject::get_type() {
    return (ObjectType) read_uint(base_addr + type_offset);
}

uint64_t WowObject::get_guid() {
    return read_uint64(base_addr + guid_offset);
}

void WowObject::log_info() {
    printf("Base addr: 0x%x\n", base_addr);
    printf("Guid: %llu\n", get_guid());
    printf("Type: %d\n", get_type());
    Position pos = get_position();
    printf("Position: {X: %f, Y: %f, Z: %f}\n\n", pos.x, pos.y, pos.z);
}
