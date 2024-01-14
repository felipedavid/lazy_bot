
namespace UI {

typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
EndScene old_endscene = NULL;

void init_imgui(LPDIRECT3DDEVICE9 p_device)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(Window::handle);
	ImGui_ImplDX9_Init(p_device);
}

long __stdcall endscene_hook(LPDIRECT3DDEVICE9 p_device)
{
    static bool init = false;
	if (!init) {
		init_imgui(p_device);
		init = true;
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return old_endscene(p_device);
}

void hook() {
    if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success) {
        kiero::bind(42, (void**)&old_endscene, endscene_hook);
    }
}

void unhook() {
    kiero::shutdown();
}

}


