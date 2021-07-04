#ifndef PLAYER
#define PLAYER
#include "unit.h"

struct LocalPlayer : Unit {
    LocalPlayer();
    char *get_name() override;
    uint64_t get_guid() override;
    void move_to(Position pos);
};
#endif
