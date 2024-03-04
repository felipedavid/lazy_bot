
#define SET_ADDR(ptr, addr) (*(void**)ptr = (void*)((u64)GetModuleHandleA("Wow-64_patched.exe") + (u64)addr))

namespace WoW {
	typedef void (__fastcall *_ConsoleWriteA)(const char *fmt, u32 color, ...);
	_ConsoleWriteA ConsoleWriteA;

	b32 *s_consoleAccessEnabledPtr;
	b32 *s_consoleActivePtr;

	void init() {
		assert(GetModuleHandleA("Wow-64_patched.exe"));
		SET_ADDR(&ConsoleWriteA, 0x75473);
		SET_ADDR(&s_consoleAccessEnabledPtr, 0x1350E10);
		SET_ADDR(&s_consoleActivePtr, 0x1350BEC);
	}

}