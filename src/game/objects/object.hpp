#ifndef WOW_OBJECT
#define WOW_OBJECT
#include <stdint.h>
#include "../enums/object_type.hpp"

class WowObject {
    const uint32_t descriptor_fields_offset = 0x8;

    // Not every game's object has a position attribute, so this will have
    // to go away when we are handling things like items.
    const uint32_t pos_x_offset = 0x9B8;
    const uint32_t pos_y_offset = 0x9BC;
    const uint32_t pos_z_offset = 0x9C0;

    uint64_t guid;
    uint32_t base_addr;
    ObjectType type;

public:
    WowObject(uint64_t guid, uint32_t base_addr, ObjectType type);
    void log_info();
    uint32_t get_base_addr();
    uint64_t get_guid();
    ObjectType get_type();
    float get_x_pos();
    float get_y_pos();
    float get_z_pos();
    
    // Be careful, almost every server check this stuff
    void set_x_pos(float new_x);
    void set_y_pos(float new_y);
    void set_z_pos(float new_z);

    uint32_t get_descriptor_addr();
};
#endif
