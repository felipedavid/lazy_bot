#include <cstdio>

#include "unit.h"
#include "../../utils/memory_manager.h"

int Unit::get_health() {
    return read_uint(get_descriptor_fields() + health_offset);
}

int Unit::get_max_health() {
    return read_uint(get_descriptor_fields() + max_health_offset);
}

int Unit::get_health_percentage() {
    return (int) (((float)get_health() / (float)get_max_health()) * 100.0f);
}

int Unit::get_mana() {
    return read_uint(get_descriptor_fields() + mana_offset);
}

int Unit::get_max_mana() {
    return read_uint(get_descriptor_fields() + max_mana_offset);
}

int Unit::get_mana_percentage() {
    int max_mana;
    if (max_mana = get_max_mana()) {
        return (int) (((float)get_mana() / (float)max_mana) * 100.0f);
    }
    return 0;
}

char *Unit::get_name() {
    return (char *) read_uint(read_uint(base_addr + name_offset));
}

void Unit::log_info() {
    Position pos = get_position();
    printf("Position: {X: %f, Y: %f, Z: %f}\n", pos.x, pos.y, pos.z);
    printf("Guid: %llu\n", get_guid());
    printf("Health: %d%%\n", get_health_percentage());
    printf("Mana: %d%%\n", get_mana_percentage());
    printf("Pointer: 0x%x\n", base_addr);
    printf("Name: %s\n\n", get_name());
}
