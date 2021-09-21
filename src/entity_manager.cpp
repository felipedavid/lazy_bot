#include "entity_manager.h"

#include "utils.h"

u64 Entity::get_guid() { 
    return read_u64(base_addr + guid_offset); 
}

Entity_Type Entity::get_type() { 
    return (Entity_Type) read_u32(base_addr + type_offset); 
}

u32 Unit::get_descriptor_ptr() {
    return read_u32(base_addr + descriptor_ptr_offset);
}

int Unit::get_health() {
    return read_int(get_descriptor_ptr() + health_offset);
}

void Entity_Manager::populate_lists() {
    units.erase(units.begin(), units.end());

    // Get a pointer to the first entity of the linked list
    u32 current = read_u32(read_u32(entity_manager_addr) + first_entity_offset);
    u32 next;
    // Iterate over the game's linked list and populate our vectors of entities
    while (current != 0 && (current & 1) == 0) {
        
        auto entity_type = (Entity_Type) read_u32(current + 0x14);
        switch (entity_type) {
            case ET_ITEM:
                Unit unit;
                unit.base_addr = current;
                units.push_back(unit);
                break;
        }

        next = read_u32(current + next_entity_offset);
        if (next == current) {
            break;
        }
        current = next;
    }
}
