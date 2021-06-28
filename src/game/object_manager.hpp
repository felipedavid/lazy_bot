#include <stdint.h>
#include <vector>

#include "objects/object.hpp"

class ObjectManager {
    std::vector<WowObject> object_list;

public:
    void populate_list();
    void log_objects();
};


int __fastcall enumerate_objects_callback(void *base_pointer, int filter, uint64_t guid);
