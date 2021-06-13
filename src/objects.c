#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "objects.h"
#include "game_functions.h"
#include "memory_manager.h"

object_t objects[500];
size_t n_objects;

uint32_t __fastcall enumerate_objects_callback(void *thiss, uint32_t filter, uint64_t guid) {
    object_t object = {0};
    object.guid = guid;
    set_object_ptr(&object);
    set_object_type(&object);

    // TODO: remove this
    if (object.type == Player) {
        local_player = &objects[n_objects];
        objects[n_objects++] = object;
    } else if (object.type == Unit) {
        object.creature_type = get_creature_type(object);
        object.unit_reaction = get_unit_reaction(object);
        set_object_health(&object);
        set_unit_level(&object);
        objects[n_objects++] = object;
    }

    if (object.type == Player && object.type == Unit) {
    }

    return 1;
}

// temporary
void populate_lists() {
    n_objects = 0; 
    enumerate_visible_objects(enumerate_objects_callback);
}

void set_object_type(object_t *object) {
    const uint32_t OBJECT_TYPE_OFFSET = 0x14;
    object->type = (object_type_t) read_byte(object->pointer + OBJECT_TYPE_OFFSET);
}

void set_object_name(object_t *object) {
    if (object->type == Unit) {
        const uint32_t NAME_OFFSET = 0xB30;
        uint32_t ptr = read_dword(object->pointer + NAME_OFFSET);
        object->name = (char *) read_dword(ptr);
    } else if (object->type == Player) {
        const uint32_t NAME_BASE_OFFSET   = 0xC0E230;
        const uint32_t NEXT_NAME_OFFSET   = 0xC;
        const uint32_t PLAYER_NAME_OFFSET = 0x14;
        uint32_t name_ptr = read_dword(NAME_BASE_OFFSET);
        while (true) {
            uint64_t next_guid = read_qword(name_ptr + NEXT_NAME_OFFSET);
            if (next_guid == object->guid) break;
            name_ptr = read_dword(name_ptr);    
        }
        object->name = (char *) (name_ptr + PLAYER_NAME_OFFSET);
    }
}

uint32_t get_descriptor_addr(object_t object) {
    const uint32_t DESCRIPTOR_OFFSET  = 0x8;
    return read_dword(object.pointer + DESCRIPTOR_OFFSET);
}

void set_object_health(object_t *object) {
    const uint32_t HEALTH_OFFSET = 0x58;
    object->health = read_dword(get_descriptor_addr(*object) + HEALTH_OFFSET);
}

void set_object_position(object_t *object) {
    const uint32_t POS_X_OFFSET = 0x9B8;
    const uint32_t POS_Y_OFFSET = 0x9BC;
    const uint32_t POS_Z_OFFSET = 0x9C0;

    position_t position;
    position.x = read_float(object->pointer + POS_X_OFFSET);
    position.y = read_float(object->pointer + POS_Y_OFFSET);
    position.z = read_float(object->pointer + POS_Z_OFFSET);

    object->position = position;
}

void set_unit_level(object_t *object) {
    const uint32_t LEVEL_OFFSET = 0x88;
    object->level = read_dword(get_descriptor_addr(*object) + LEVEL_OFFSET);
}
