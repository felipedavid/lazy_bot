
typedef enum {
    NoState,
    GrindState,
    MoveToTargetState,
    CombatState,
    LootState,
} state_t;

typedef struct {
    state_t stack[20];
    int top_index;
    int max_size;
} state_stack_t;

void push_state(state_t state);
void pop_state();
state_t get_top_state();

void handle_grind_state();
void handle_move_to_target_state();
void handle_combat_state();
void handle_loot_state();
