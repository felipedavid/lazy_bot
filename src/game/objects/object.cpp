#include <stdio.h>
#include <stdint.h>

#include "object.h"
#include "../enums/object_type.h"

WowObject::WowObject(uint64_t obj_guid, uint32_t obj_pointer, ObjectType obj_type) {
    guid = obj_guid;
    pointer = obj_pointer;
    type = obj_type;
}

WowObject::log_object_info() {
    printf("Guid: %" PRIu64 "\n", guid);
    printf("Pointer: %" PRIu32 "\n", pointer);
}

WowObject::get_position() {
    Position position;
    *position = read_memory<Position>(pointer + XPositionOffset);

    return position;
}
