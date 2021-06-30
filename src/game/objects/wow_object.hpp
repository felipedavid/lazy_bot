#ifndef WOW_OBJECT
#define WOW_OBJECT
#include <stdint.h>

#include "../enums/object_type.hpp"
#include "../position.hpp"

class WowObject {
    const uint32_t descriptor_fields_offset = 0x8;
    const uint32_t type_offset = 0x14;
    const uint32_t guid_offset = 0x30;

    const uint32_t pos_x_offset = 0x9B8;
    const uint32_t pos_y_offset = 0x9BC;
    const uint32_t pos_z_offset = 0x9C0;

    uint32_t base_addr;
public:
    WowObject(uint32_t base_addr);
    void log_info();
    uint32_t get_base_addr();
    uint64_t get_guid();
    ObjectType get_type();
    Position get_position();
    uint32_t get_descriptor_addr();
};
#endif
