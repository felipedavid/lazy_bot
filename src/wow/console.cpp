
namespace WoW {

	typedef void (__fastcall *_ConsoleWriteA)(const char *fmt, u32 color, ...);
	_ConsoleWriteA ConsoleWriteA;

	b32 *s_consoleAccessEnabledPtr;
	b32 *s_consoleActivePtr;

}