void initImGui(LPDIRECT3DDEVICE9 p_device)
{
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange | ImGuiConfigFlags_NavNoCaptureKeyboard;

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(p_device);
}

void ObjectManagerInspector(bool* p_open)
{
	auto objects = entityManager.visibleObjs;
	auto objects_len = entityManager.objsLen;

    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Object Manager Inspector", p_open, ImGuiWindowFlags_MenuBar))
    {
        // Left
        static int selected = 0;
        {
            ImGui::BeginChild("left pane", ImVec2(150, 0), ImGuiChildFlags_Border | ImGuiChildFlags_ResizeX);
            for (int i = 0; i < objects_len; i++)
            {
                // FIXME: Good candidate to use ImGuiSelectableFlags_SelectOnNav
				auto obj = ClntObjMgrObjectPtr(objects[i], TYPEMASK_ALL);
				if (!obj) continue;

                char label[256];
                sprintf(label, "%s %llu", ObjTypeStr[obj->type], objects[i]);
                if (ImGui::Selectable(label, selected == i)) {
					*s_currentTargetGUID = objects[i];
                    selected = i;
				}
            }
            ImGui::EndChild();
        }
        ImGui::SameLine();

        // Right
        {
            ImGui::BeginGroup();
            ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
            ImGui::Text("MyObject: %d", selected);
            ImGui::Separator();
            if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
            {
                if (ImGui::BeginTabItem("Description"))
                {
                    ImGui::TextWrapped("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ");
                    ImGui::EndTabItem();
                }
                if (ImGui::BeginTabItem("Details"))
                {
                    ImGui::Text("ID: 0123456789");
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }
            ImGui::EndChild();
            if (ImGui::Button("Revert")) {}
            ImGui::SameLine();
            if (ImGui::Button("Save")) {}
            ImGui::EndGroup();
        }
    }
    ImGui::End();
}

void drawGui() {
	static char buf[256];
	ImGui::Begin("Lazy Fish", &lazy_fish_running);

	sprintf(buf, "Player: 0x%x", (u32)ClntObjMgrGetActivePlayerObj());
	ImGui::Text(buf);

	sprintf(buf, "SelectedGuid: 0x%x %llu", (u32)ClntObjMgrObjectPtr(*s_currentTargetGUID, TYPEMASK_OBJECT), *s_currentTargetGUID);
	ImGui::Text(buf);

	static bool open = true;
	ObjectManagerInspector(&open);

	ImGui::End();
}