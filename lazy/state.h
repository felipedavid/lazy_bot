#include "object.h"

typedef enum {
    NO_STATE,
    GRIND_STATE,
    MOVE_TO_TARGET_STATE,
    COMBAT_STATE,
} state_t;

typedef struct {
    state_t stack[10];
    int n_states;
} state_stack_t;

extern object_t local_player;
extern object_t closest_unit;
extern int n_units;

void grind_state_handler();
void move_to_target_state_handler();
void combat_state_handler();
void push_state(state_t state);
void pop_state();
state_t top_state();
