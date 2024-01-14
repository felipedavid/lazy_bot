
struct ObjectManager {
    u8 unk[0xAC];
    WoWObject *visibleObjects;
};

// TODO: Find out the right way to this so that I don't need to write assembly
ObjectManager *get_object_manager() {
    __asm {
        mov ecx,dword ptr fs:[0x2C]
        mov eax,dword ptr ds:[0xD439BC]
        mov edx,dword ptr ds:[ecx+eax*4]
        mov eax,dword ptr ds:[edx+8]
    }
}

WoWObject *get_object(u64 guid) {
    ObjectManager *obj_mgr = get_object_manager();
    WoWObject *obj = obj_mgr->visibleObjects;

    while (obj && (((u32)obj & 1) == 0)) {
        u32 obj_mgr_unk_field = *(u32*)((u32)obj_mgr+0xA4);
        obj = *(WoWObject**)((u32)obj + obj_mgr_unk_field + 4);
    }

    return NULL;
}
