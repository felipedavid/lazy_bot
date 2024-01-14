void init_imgui(LPDIRECT3DDEVICE9 p_device)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(p_device);
}

void draw_ui() {
	ImGui::Begin("Lazy Fish");
	ImGui::Text("hiii");
	ImGui::End();
}