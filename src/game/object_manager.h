#ifndef OBJECT_MANAGER
#define OBJECT_MANAGER
#include <cstdint>
#include <vector>

#include "objects/object.h"
#include "objects/unit.h"
#include "objects/player.h"

struct ObjectManager {
    std::vector<Unit> units;
    std::vector<Player> players;

    void populate_lists();
    void log_info();
};
#endif
