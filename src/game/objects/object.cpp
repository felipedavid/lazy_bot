#include <cstdint>
#include <cstdio>

#include "object.h"
#include "../../memory_manager.h"
#include "../../position.h"

uint32_t WowObject::get_descriptor_fields() {
    return read_uint(base_addr + descriptor_offset);
}

Position WowObject::get_position() {
    float pos_x = read_float(base_addr + position_x_offset);
    float pos_y = read_float(base_addr + position_x_offset + 0x4);
    float pos_z = read_float(base_addr + position_x_offset + 0x8);

    Position pos{pos_x, pos_y, pos_z};
    return pos;
}

void WowObject::log_info() {
    printf("Base addr: 0x%x\n", base_addr);
}
