#include <stdio.h>
#include <string.h>
#include "state.h"
#include "game_functions.h"
#include "object_manager.h"

state_stack_t bot_state = {0};

void grind_state_handler() {
    if (local_player.target_guid == 0) {
        n_units = 0; // wrap this up
        game_enumerate_visible_objects(objects_callback, 0);

        if (!strcmp(closest_unit.name_ptr, "Plainstrider")) {
            set_target(closest_unit);
        }
    } else {
        push_state(MOVE_TO_TARGET_STATE);
    }
}

void move_to_target_state_handler() {
    //set_unit_position(&closest_unit);
    //set_unit_position(&local_player);
        n_units = 0; // wrap this up
        game_enumerate_visible_objects(objects_callback, 0);
    if (local_player.target_guid > 0 && 
        local_player_distance_from_position(closest_unit.position) > 4) {
        click_to_move(closest_unit.position);
    } else {
        click_to_move_stop();
        push_state(COMBAT_STATE);
    }
}

void combat_state_handler() {
        n_units = 0; // wrap this up
        game_enumerate_visible_objects(objects_callback, 0);
    if (local_player_distance_from_position(closest_unit.position) > 4) {
        pop_state();
        return;
    } 

    if (closest_unit.health > 0) {
        cast_spell_by_name("Attack");
    } else {
        // come back to grind state
        bot_state.n_states -= 2;
    }
}

void push_state(state_t state) {
    if (bot_state.n_states < 10) {
        bot_state.stack[(bot_state.n_states)++] = state;
    } else {
        printf("State stack is full.\n");
    }
}

void pop_state() {
    if (bot_state.n_states) {
        bot_state.n_states--;
    } else {
        printf("Bot state stack is already empty.\n");
    }
}

state_t top_state() {
    if (bot_state.n_states == 0) {
        return NO_STATE;
    }
    return bot_state.stack[bot_state.n_states - 1];
}
