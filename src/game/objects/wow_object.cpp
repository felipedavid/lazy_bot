#include <stdio.h>
#include <stdint.h>

#include "wow_object.hpp"
#include "../position.hpp"

WowObject::WowObject(uint32_t base_addr) {
    this->base_addr = base_addr;
}

void WowObject::log_info() {
    printf("Guid: %llu\n",  get_guid());
    printf("Pointer: %u\n", get_base_addr());
    printf("Type : %u\n",   get_type());
    Position pos = get_position();
    printf("Position: {X: %f, Y: %f, Z: %f}\n", pos.x, pos.y, pos.z);
}

uint32_t WowObject::get_base_addr() { 
    return base_addr;
}

uint64_t WowObject::get_guid() { 
    return *(uint64_t *) (base_addr + guid_offset);
}

ObjectType WowObject::get_type() { 
    return (ObjectType) (*(uint32_t *) (base_addr + type_offset));
}

Position WowObject::get_position() {
    float x = *(float *) (base_addr + pos_x_offset);
    float y = *(float *) (base_addr + pos_y_offset);
    float z = *(float *) (base_addr + pos_z_offset);
    Position pos(x, y, z);
    return pos;
}

uint32_t WowObject::get_descriptor_addr() {
    return *(uint32_t *) (base_addr + descriptor_fields_offset);
}
