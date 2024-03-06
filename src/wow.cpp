#include "wow/console.cpp"
#include "wow/object_manager.cpp"

#define SET_REBASED_ADDR(ptr, zero_based_addr) \
	(*(void**)ptr = (void*)((u64)GetModuleHandleA("Wow-64_patched.exe") + (u64)zero_based_addr))
#define REBASE_ADDR(zero_based_addr) \
	((void*)((u64)GetModuleHandleA("Wow-64_patched.exe") + (u64)zero_based_addr))

namespace WoW {

	void init() {
		assert(GetModuleHandleA("Wow-64_patched.exe"));

		{ // Console
			SET_REBASED_ADDR(&ConsoleWriteA, 0x75473);
			SET_REBASED_ADDR(&s_consoleAccessEnabledPtr, 0x1350E10);
			SET_REBASED_ADDR(&s_consoleActivePtr, 0x1350BEC);
		}

		{ // Object manager
			s_curMgr = *(CGObjectManager**) REBASE_ADDR(0x1387048);
		}
	}

}