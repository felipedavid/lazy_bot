#include <windows.h>
#include "object_manager.h"
#include "wow.h"

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
	switch (reason) {
	case DLL_PROCESS_ATTACH:
		WoW::ConsolePrintf("hi");
		break;
	}
	return TRUE;
}
