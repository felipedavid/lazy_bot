#pragma once
#include "type.h"

template <typename T>
T read(u32 addr) { return *(T*)addr; }
