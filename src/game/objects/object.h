#ifndef WOW_OBJECT
#define WOW_OBJECT
#include <cstdint>
#include "../../position.h"
#include "../enums/object_type.h"

struct WowObject {
    static const uint32_t guid_offset = 0x30;
    static const uint32_t type_offset = 0x14;
    static const uint32_t position_x_offset = 0x9B8;
    static const uint32_t descriptor_fields_offset = 0x8;

    uint32_t base_addr;

    uint32_t get_descriptor_fields();
    Position get_position();
    ObjectType get_type();
    virtual uint64_t get_guid();
    virtual void log_info();
};
#endif
