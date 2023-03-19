#include "directx_hook.h"

#include <windows.h>

typedef LPDIRECT3D9(__stdcall* Direct3DCreate9Fun)(UINT);

b32 directx_init() {
	HMODULE d3d9_module = GetModuleHandleA("d3d9.dll");
	if (!d3d9_module) return false;

	Direct3DCreate9Fun create = (Direct3DCreate9Fun) GetProcAddress(d3d9_module, "Direct3DCreate9");
	if (!create) return false;

	LPDIRECT3D9 d3d9 = create(D3D_SDK_VERSION);
	if (!d3d9) return false;

	D3DPRESENT_PARAMETERS params;
	ZeroMemory(&params, sizeof(params));

	HRESULT result = IDirect3D9_CreateDevice(d3d9, );
	if (!result) return false;

	return true;
}

void directx_release() {
}
