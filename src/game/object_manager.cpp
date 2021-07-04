#include <cstdio>
#include <cstdint>
#include <vector>

#include "objects/object.h"
#include "objects/unit.h"
#include "objects/local_player.h"
#include "object_manager.h"
#include "../memory_manager.h"
#include "functions.h"

void ObjectManager::populate_lists() {
    static const uint32_t object_manager_offset = 0x00B41414;  
    static const uint32_t first_obj_ptr_offset = 0xac;  
    static const uint32_t next_obj_ptr_offset= 0x3c;  
    static const uint32_t obj_type_offset = 0x14;  
    
    uint32_t cur_obj_ptr = read_uint(read_uint(object_manager_offset) + first_obj_ptr_offset);
    uint32_t next_obj_ptr;
    while (cur_obj_ptr != 0 && (cur_obj_ptr & 1) == 0) {
        ObjectType cur_obj_type = (ObjectType) read_uint(cur_obj_ptr + obj_type_offset);
        switch (cur_obj_type) {
            case UnitType: {
                Unit new_unit;
                new_unit.base_addr = cur_obj_ptr;
                units.push_back(new_unit);
            } break;
        }

        next_obj_ptr = read_uint(cur_obj_ptr + next_obj_ptr_offset);
        if (next_obj_ptr == cur_obj_ptr) break;
        else cur_obj_ptr = next_obj_ptr;
    }
}

void ObjectManager::log_info() {
    get_closest_unit().log_info();
}

Unit ObjectManager::get_closest_unit() {
    Unit closest_unit;
    closest_unit.base_addr = 0;
    float closest_unit_distance, unit_distance;
    for (auto unit : units) {
        unit_distance = unit.get_position().distance_from(local_player.get_position());
        if ((closest_unit.base_addr == 0) || (unit_distance < closest_unit_distance)) {
            closest_unit = unit;
            closest_unit_distance = unit_distance;
        }
    }
    // debugging
    local_player.move_to(closest_unit.get_position());
    return closest_unit;
}
