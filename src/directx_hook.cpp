typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
EndScene originalEndscene = NULL;

i64 __stdcall ourEndscene(LPDIRECT3DDEVICE9 pDevice)
{
    static bool init = false;
	if (!init) {
		initImGui(pDevice);
		init = true;
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

    drawUI();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return originalEndscene(pDevice);
}

// TODO: do the hooking myself and stop depending on kiero
void hookDirectX() {
    if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success) {
        kiero::bind(42, (void**)&originalEndscene, ourEndscene);
    }
}

void unhookDirectX() {
    kiero::shutdown();
}