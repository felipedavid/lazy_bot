typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
EndScene original_endscene = NULL;

i64 __stdcall our_endscene(LPDIRECT3DDEVICE9 p_device)
{
    static bool init = false;
	if (!init) {
		init_imgui(p_device);
		init = true;
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

    draw_ui();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return original_endscene(p_device);
}

// TODO: do the hooking myself and stop depending on kiero
void hook_directx() {
    if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success) {
        kiero::bind(42, (void**)&original_endscene, our_endscene);
    }
}

void unhook_directx() {
    kiero::shutdown();
}