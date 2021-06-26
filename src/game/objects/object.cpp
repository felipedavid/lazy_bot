#include <stdio.h>
#include <stdint.h>

#include "object.h"
#include "../enums/object_type.hpp"

WowObject::WowObject(uint64_t guid, uint32_t pointer, ObjectType type) {
    this->guid = guid;
    this->pointer = pointer;
    this->type = type;
}

WowObject::log_object_info() {
    printf("Guid: %" PRIu64 "\n", guid);
    printf("Pointer: %" PRIu32 "\n", pointer);
    printf("Type : %" PRIu32 "\n", type);
}

WowObject::get_position() {
    Position position;
    *position = read_memory<Position>(pointer + pos_x_offset);
    return position;
}

uint32_t WowObject::get_pointer() { 
    return pointer;
}

uint64_t WowObject::get_guid() { 
    return guid;
}

ObjectType WowObject::get_object_type() { 
    return type;
}
