typedef void(__cdecl *_ConsolePrintf)(const char *fmt, ...);
typedef WoWObject *(__cdecl *_ClntObjMgrObjectPtr)(u64 guid, TypeMask type_mask);
typedef Player *(__cdecl *_ClntObjMgrGetActivePlayerObj)();
typedef u64(__cdecl *_ClntObjMgrGetActivePlayer)();

typedef b32(__cdecl *_EnumVisibleObjectsCallback)(u64 guid, u32 filter);
typedef b32(__cdecl *_EnumVisibleObjects)(_EnumVisibleObjectsCallback, u32 filter);
typedef void(__thiscall *_ChatBubbleShow)(Unit *unit, int unknown, const char *msg);
typedef b32(__thiscall *_IsLocalPlayer)(WoWObject *object);

typedef void(__thiscall *_DeclineGroup)(Player *player);
typedef void(__thiscall *_DeclineGuild)(Player *player);
typedef b32(__thiscall *_IsClickMoving)(Player *player);

auto ConsolePrintf = (_ConsolePrintf) 0x007653B0;
auto ClntObjMgrObjectPtr = (_ClntObjMgrObjectPtr) 0x004D4DB0;
auto ClntObjMgrGetActivePlayerObj = (_ClntObjMgrGetActivePlayerObj) 0x004038F0;
auto ClntObjMgrGetActivePlayer = (_ClntObjMgrGetActivePlayer) 0x004D3790;
auto EnumVisibleObjects = (_EnumVisibleObjects) 0x004D4B30;
auto ChatBubbleShow = (_ChatBubbleShow) 0x00720010;
auto IsLocalPlayer = (_IsLocalPlayer) 0x004CEE50;
auto DeclineGroup = (_DeclineGroup) 0x006D44D0;
auto DeclineGuild = (_DeclineGuild) 0x006D47D0;
auto IsClickMoving = (_IsClickMoving) 0x00721F90;