#include "entity_manager.h"

#include "utils.h"

u64 Entity::get_guid() { 
    return read_u64(pointer + guid_offset); 
}

Entity_Type Entity::get_type() { 
    return (Entity_Type) read_u32(pointer + type_offset); 
}

void Entity_Manager::populate_lists() {
    entities.erase(entities.begin(), entities.end());

    u32 current = read_u32(read_u32(entity_manager_addr) + first_entity_offset);
    u32 next;
    while (current != 0 && (current & 1) == 0) {
        
        entities.push_back(Entity{current});

        next = read_u32(current + next_entity_offset);
        if (next == current) {
            break;
        }
        current = next;
    }
}
