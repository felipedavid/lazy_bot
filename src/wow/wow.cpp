
namespace WoW {
    typedef void (__cdecl *_ConsolePrintf)(char *fmt, ...);

    auto ConsolePrintf = (_ConsolePrintf) 0x007653b0;

    auto s_ConsoleAcivePtr = (b32 *) 0x00CA1978;
};