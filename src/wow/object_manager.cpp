
struct ObjectManager {
    u8 unk[0xAC];
    WoWObject *visibleObjects;
};

ObjectManager *getObjectManager() {
    ObjectManager *objMgr = NULL;
    __asm {
        pushad
        mov ecx, dword ptr fs:[0x2C]
        mov ecx, dword ptr ds:[ecx]
        mov ecx, dword ptr ds:[ecx+8]
        mov objMgr, ecx
        popad
    }
    return objMgr;
}

WoWObject *getObject(ObjectManager *objMgr, u64 guid) {
    WoWObject *obj = objMgr->visibleObjects;

    while (obj && (((u32)obj & 1) == 0)) {
        u32 obj_mgr_unk_field = *(u32*)((u32)objMgr+0xA4);
        obj = *(WoWObject**)((u32)obj + obj_mgr_unk_field + 4);
    }

    return NULL;
}
