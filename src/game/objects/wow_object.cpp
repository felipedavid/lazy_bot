#include <stdio.h>
#include <stdint.h>

#include "wow_object.hpp"
#include "..\..\memory_manager.hpp"

WowObject::WowObject(uint32_t base_addr) {
    this->base_addr = base_addr;
}

void WowObject::log_info() {
    printf("Guid: %llu\n",  guid);
    printf("Pointer: %u\n", base_addr);
    printf("Type : %u\n",   type);
    printf("Position: {X: %f, Y: %f, Z: %f}\n", get_x_pos(), 
                                                get_y_pos(), 
                                                get_z_pos());
}

uint32_t WowObject::get_base_addr() { 
    return base_addr;
}

uint64_t WowObject::get_guid() { 
    return *(uint64_t *) (base_addr + guid_offset);
}

WowObjectType WowObject::get_type() { 
    return (ObjectType) (*(uint32_t *) (base_addr + type_offset));
}

Position WowObject::get_position() {
    float x = *(float *) (base_addr + pos_x_offset);
    float y = *(float *) (base_addr + pos_y_offset);
    float z = *(float *) (base_addr + pos_z_offset);
    Position pos(x, y, z);
    return pos;
}

void WowObject::set_position(Position new_position) {
    *(Position *) (base_addr + pos_x_offset) = new_position;
}

uint32_t WowObject::get_descriptor_addr() {
    return read_uint32(base_addr + descriptor_fields_offset);
}
