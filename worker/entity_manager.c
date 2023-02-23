#include "entity_manager.h"

void log_entity(Entity *ent) {
	ConsoleWrite("Addr: 0x%x\nGuid: 0x%x\nType: %s\n\n", ent->addr, ent->guid, ent->type);
}
