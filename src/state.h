
typedef enum {
    NoState,
    GrindState,
    MoveToTargetState,
    CombatState,
} state_t;

typedef struct {
    state_t stack[20];
    int top_index;
    int max_size;
} state_stack_t;

void push_state(state_t state);
void pop_state();
state_t get_top_state();
