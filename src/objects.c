#include <stdio.h>
#include <stdbool.h>

#include "objects.h"
#include "stdint.h"
#include "game_functions.h"
#include "memory_manager.h"
#include "local_player.h"

object_t objects[500];
size_t n_objects;

uint32_t __fastcall enumerate_objects_callback(void *thiss, uint32_t filter, uint64_t guid) {
    object_t object = {0};
    object.guid = guid;
    object.pointer = get_object_ptr(object.guid);
    object.type = get_object_type(object.pointer);

    // TODO: remove this
    if (object.type == Player) {
        local_player = &objects[n_objects];
    }

    if (object.type == Unit || object.type == Player) {
        objects[n_objects++] = object;
    }

    return 1;
}

// temporary
void update_view() {
    n_objects = 0; 
    enumerate_visible_objects(enumerate_objects_callback);
}

object_type_t get_object_type(uint32_t object_ptr) {
    const uint32_t OBJECT_TYPE_OFFSET = 0x14;
    return (object_type_t) read_byte(object_ptr + OBJECT_TYPE_OFFSET);
}

char *get_object_name(object_t object) {
    char *name = NULL;

    switch (object.type) {
        case Unit: {
            const uint32_t NAME_OFFSET = 0xB30;
            uint32_t ptr = read_dword(object.pointer + NAME_OFFSET);
            name = (char *) read_dword(ptr);
        } break;

        case Player: {
            const uint32_t NAME_BASE_OFFSET   = 0xC0E230;
            const uint32_t NEXT_NAME_OFFSET   = 0xC;
            const uint32_t PLAYER_NAME_OFFSET = 0x14;
            uint32_t name_ptr = read_dword(NAME_BASE_OFFSET);
            while (true) {
                uint64_t next_guid = read_qword(name_ptr + NEXT_NAME_OFFSET);
                if (next_guid == object.guid) break;
                name_ptr = read_dword(name_ptr);    
            }
            name = (char *) (name_ptr + PLAYER_NAME_OFFSET);
        } break;

        default:
            break;
    }

    return name;
}

uint32_t get_object_health(object_t object) {
    uint32_t health = 0;

    switch(object.type) {
        case Unit: 
        case Player: {
            const uint32_t DESCRIPTOR_OFFSET  = 0x8;
            const uint32_t HEALTH_OFFSET      = 0x58;
            uint32_t descriptor_collection_addr = 
                read_dword(object.pointer + DESCRIPTOR_OFFSET);
            health = read_dword(descriptor_collection_addr + HEALTH_OFFSET);
            } break;
        default:
            break;
    }

    return health;
}

position_t get_object_position(object_t object) {
    const uint32_t POS_X_OFFSET = 0x9B8;
    const uint32_t POS_Y_OFFSET = 0x9BC;
    const uint32_t POS_Z_OFFSET = 0x9C0;

    position_t position;
    position.x = read_float(object.pointer + POS_X_OFFSET);
    position.y = read_float(object.pointer + POS_Y_OFFSET);
    position.z = read_float(object.pointer + POS_Z_OFFSET);

    return position;
}

void print_object_info(object_t object) {
    printf("Guid: %llu\n", object.guid);
    printf("Pointer: 0x%x\n", object.pointer);
    printf("Type: 0x%x\n", object.type);
    printf("Health: %d\n", get_object_health(object));
    printf("Name: %s\n", get_object_name(object));

    position_t position = get_object_position(object);
    printf("Position: %.2f %.2f %.2f\n", position.x,
                                         position.y,
                                         position.z);
    printf("Distance from local player: %.2f\n\n", get_distance_from_object(object));
}
