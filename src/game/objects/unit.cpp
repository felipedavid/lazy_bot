#include <cstdio>

#include "unit.h"
#include "../../memory_manager.h"

int Unit::get_health() {
    return read_uint(get_descriptor_fields() + health_offset);
}

char *Unit::get_name() {
    return (char *) read_uint(read_uint(base_addr + name_offset));
}

void Unit::log_info() {
    Position pos = get_position();
    printf("Position: {X: %f, Y: %f, Z: %f}\n", pos.x, pos.y, pos.z);
    printf("Guid: %llu\n", get_guid());
    printf("Health: %d\n", get_health());
    printf("Pointer: 0x%x\n", base_addr);
    printf("Name: %s\n\n", get_name());
}
