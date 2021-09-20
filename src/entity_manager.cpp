#include "entity_manager.h"

#include "utils.h"

Entity::Entity(u32 pointer) {
    this->pointer = pointer;
    this->guid = read_u32(pointer + guid_offset);
    this->type = (Entity_Type) read_u32(pointer + type_offset);
}

void Entity_Manager::populate_lists() {
    u32 current = read_u32(read_u32(entity_manager_addr) + first_entity_offset);
    u32 next;
    while (current != 0 && (current & 1) == 0) {
        
        entities.push_back(Entity(current));

        next = *(u32 *)(current + next_entity_offset);
        if (next == current) {
            break;
        } else {
            current = next;
        }
    }
}
