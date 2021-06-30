#include <stdint.h>

#include "wow_object.hpp"
#include "..\enums\entity_type.hpp"

class Unit : public WowObject {
    const uint32_t name_offset = 0xB30;

    // Some unit's information are stored in a different memory location. 
    // To access it, use the following pointer path:
    // [[unit_base_addr + 0x8] + unit_field_health_offset] -> unit_health
    const uint32_t unit_field_health_offset = 0x58;
    const uint32_t unit_field_max_health_offset = 0x70;

public:
    Unit(uint64_t guid, uint32_t base_addr, ObjectType type);
    int get_health();
    int get_max_health();
    int get_health_percentage();
    char *get_name();
    void log_info();
};
