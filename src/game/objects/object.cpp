#include <stdio.h>
#include <stdint.h>

#include "object.hpp"
#include "..\functions.hpp" // remove it later
#include "..\..\memory_manager.hpp"

WowObject::WowObject(uint64_t guid, uint32_t base_addr, ObjectType type) {
    this->guid = guid;
    this->base_addr = base_addr;
    this->type = type;
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
    return guid;
}

ObjectType WowObject::get_type() { 
    return type;
}

float WowObject::get_x_pos() {
    return read_float(base_addr + pos_x_offset);
}

float WowObject::get_y_pos() {
    return read_float(base_addr + pos_y_offset);
}

float WowObject::get_z_pos() {
    return read_float(base_addr + pos_z_offset);
}

uint32_t WowObject::get_descriptor_addr() {
    return read_uint32(base_addr + descriptor_fields_offset);
}
