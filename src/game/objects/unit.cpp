#include <stdio.h>

#include "unit.hpp"
#include "..\..\memory_manager.hpp"

UnitObject::UnitObject(uint64_t guid, uint32_t base_addr, ObjectType type):
    WowObject(guid, base_addr, type) {
}

int UnitObject::get_health() {
    return read_int32(get_descriptor_addr() + unit_field_health_offset);
}

int UnitObject::get_max_health() {
    return read_int32(get_descriptor_addr() + unit_field_max_health_offset);
}

int UnitObject::get_health_percentage() {
    return (int) (((float)get_health() / (float)get_max_health()) * 100.0);
}

char *UnitObject::get_name() {
    uint32_t name_addr = read_uint32(get_base_addr() + name_offset);
    return (char *) read_uint32(name_addr);
}

void UnitObject::log_info() {
    printf("Name: %s\n", get_name());
    printf("Health: %d\n", get_health());
    printf("Max Health: %d\n", get_max_health());
    printf("Helth Percentage: %d\n", get_health_percentage());
    printf("Base Address: %x\n", get_base_addr());
    printf("Guid: %llu\n", get_guid());
    printf("Position: {X: %f, Y: %f, Z: %f}\n\n", get_x_pos(),
                                                  get_y_pos(),
                                                  get_z_pos());
}
