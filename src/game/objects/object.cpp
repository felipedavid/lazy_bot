#include <stdio.h>
#include <stdint.h>

WowObject::WowObject(uint64_t obj_guid, uint32_t obj_pointer, ObjectType obj_type) {
    guid = obj_guid;
    pointer = obj_pointer;
    type = obj_type;
}

void WowObject::log_object_info() {
    printf("Guid: %llu\n", this->guid);
    printf("Pointer: %u\n", this->pointer);
    printf("Type : %u\n", this->type);
}

uint32_t WowObject::get_pointer() { 
    return this->pointer;
}

uint64_t WowObject::get_guid() { 
    return this->guid;
}

ObjectType WowObject::get_object_type() { 
    return this->type;
}
