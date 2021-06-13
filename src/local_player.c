#include <math.h>
#include <string.h>

#include "local_player.h"
#include "game_functions.h"
#include "objects.h"

object_t *local_player;

float get_distance_from_object(object_t object) {
    float delta_x = local_player->position.x - object.position.x;
    float delta_y = local_player->position.y - object.position.y;
    float delta_z = local_player->position.z - object.position.z;

    return (float) sqrt(delta_x * delta_x + delta_y * delta_y + delta_z * delta_z);
}

object_t get_new_target() {
    object_t new_enemy = {0};
    // temporary dumb thing
    object_t *obj_ptr;
    for (int i = 0; i < n_objects; i++) {
        obj_ptr = &objects[i];
        if (obj_ptr->health > 0 &&
            obj_ptr->creature_type != Critter &&
            obj_ptr->creature_type != NotSpecified &&
            obj_ptr->creature_type != Totem //&&
            //(obj_ptr->unit_reaction == Hostile ||
            // obj_ptr->unit_reaction == Unfriendly ||
            // obj_ptr->unit_reaction == Neutral)) {
            ) {
            new_enemy = *obj_ptr;
        }
    }

    for (size_t i = 0; i < n_objects; i++) {
        obj_ptr = &objects[i];
        if (obj_ptr->health > 0 &&
            obj_ptr->creature_type != Critter &&
            obj_ptr->creature_type != NotSpecified &&
            obj_ptr->creature_type != Totem &&
            //(obj_ptr->unit_reaction == Hostile ||
            // obj_ptr->unit_reaction == Unfriendly ||
            // obj_ptr->unit_reaction == Neutral) &&
             get_distance_from_object(objects[i]) <
             get_distance_from_object(new_enemy)) {
            new_enemy = *obj_ptr;
        }
    }
    return new_enemy;
}
