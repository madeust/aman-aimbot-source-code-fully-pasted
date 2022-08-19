#pragma once

LRESULT __stdcall window_process(const HWND window, const UINT message, const WPARAM w_param, const LPARAM l_param);

// user interface
namespace u {
	constexpr struct window_size_t {
		const int width = 805;
		const int height = 460;
	}size;

	inline HWND window = nullptr;
	inline WNDCLASSEX window_class = { };
	inline auto tab = 1;

	inline POINTS window_pos = { };
	inline auto current_tab = 0;
	inline auto button_height = 38.0f;

	inline PDIRECT3D9 d3d = nullptr;
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline D3DPRESENT_PARAMETERS params = { };

	inline IDirect3DTexture9* profile_picture = nullptr;
	inline LPDIRECT3DTEXTURE9 image_head = nullptr;
	inline LPDIRECT3DTEXTURE9 image_neck = nullptr;
	inline LPDIRECT3DTEXTURE9 image_chest = nullptr;

	inline IDirect3DTexture9* rage = nullptr;
	inline IDirect3DTexture9* legit = nullptr;
	inline IDirect3DTexture9* main = nullptr;
	inline IDirect3DTexture9* configs = nullptr;

	__forceinline const bool __fastcall create_window(const char* name) noexcept {

		window_class.cbSize = sizeof(WNDCLASSEX);
		window_class.style = CS_CLASSDC;
		window_class.lpfnWndProc = (WNDPROC)window_process;
		window_class.cbClsExtra = 0;
		window_class.cbWndExtra = 0;
		window_class.hInstance = GetModuleHandleA(0);
		window_class.hIcon = 0;
		window_class.hCursor = 0;
		window_class.hbrBackground = 0;
		window_class.lpszMenuName = 0;
		window_class.lpszClassName = "aman";
		window_class.hIconSm = 0;

		if (!RegisterClassEx(&window_class)) {
			return false;
		}

		window = CreateWindowExA(
			0,
			window_class.lpszClassName,
			name,
			WS_POPUP,
			100,
			100,
			size.width - 10,
			size.height - 4,
			0,
			0,
			window_class.hInstance,
			0
		);

		if (!window) {
			return false;
		}

		ShowWindow(window, SW_SHOWDEFAULT);
		UpdateWindow(window);

		//VMProtectEnd();

		return true;
	}
	__forceinline void __fastcall destroy_window() noexcept {
		//VMProtectBeginVirtualization("destroy_window");
		DestroyWindow(window);
		UnregisterClass(window_class.lpszClassName, window_class.hInstance);
		//VMProtectEnd();
	}

	__forceinline const bool __fastcall create_device() noexcept {
		//VMProtectBeginVirtualization("create_device");
		d3d = Direct3DCreate9(D3D_SDK_VERSION);
		if (!d3d) {
			return false;
		}

		SecureZeroMemory(&params, sizeof(params));
		params.Windowed = TRUE;
		params.SwapEffect = D3DSWAPEFFECT_DISCARD;
		params.BackBufferFormat = D3DFMT_UNKNOWN;
		params.EnableAutoDepthStencil = TRUE;
		params.AutoDepthStencilFormat = D3DFMT_D16;
		params.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

		if (d3d->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			window,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&params,
			&device) < 0) {
			return false;
		}

		//VMProtectEnd();

		return true;
	}
	__forceinline void __fastcall reset_device() noexcept {
		ImGui_ImplDX9_InvalidateDeviceObjects();

		const auto result = device->Reset(&params);
		if (result == D3DERR_INVALIDCALL) {
			IM_ASSERT(0);
		}

		ImGui_ImplDX9_CreateDeviceObjects();
	}
	__forceinline void __fastcall destroy_device() noexcept {
		//VMProtectBeginVirtualization("destroy_device");
		if (device) {
			device->Release();
			device = nullptr;
		}

		if (d3d) {
			d3d->Release();
			d3d = nullptr;
		}
		//VMProtectEnd();
	}

	__forceinline void __fastcall update_style() noexcept {
		ImGuiStyle* style = &ImGui::GetStyle();
		style->Alpha = 1.f;
		style->WindowRounding = 1.f;
		style->FramePadding = ImVec2(4, 3);
		style->WindowPadding = ImVec2(8, 8);
		style->ItemInnerSpacing = ImVec2(4, 4);
		style->ItemSpacing = ImVec2(8, 4);
		style->FrameRounding = 5.f;
		style->ScrollbarSize = 2.f;
		style->ScrollbarRounding = 12.f;


		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_ChildBg] = ImColor(24, 29, 59, 0);
		colors[ImGuiCol_Border] = ImVec4(0.07f, 0.07f, 0.11f, 0.50f);
		colors[ImGuiCol_FrameBg] = ImColor(25, 25, 33, 255);
		colors[ImGuiCol_FrameBgActive] = ImColor(25, 25, 33, 255);
		colors[ImGuiCol_FrameBgHovered] = ImColor(25, 25, 33, 255);
		colors[ImGuiCol_Header] = ImColor(25, 25, 33, 255);
		colors[ImGuiCol_HeaderActive] = ImColor(28, 28, 36, 255);
		colors[ImGuiCol_HeaderHovered] = ImColor(30, 30, 38, 255);
		colors[ImGuiCol_PopupBg] = ImColor(35, 35, 45, 255);
		/*auto menu_color = ImVec4(menu_accent[0], menu_accent[1], menu_accent[2], menu_accent[3]);
		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);

		colors[ImGuiCol_WindowBg] = menu_color;
		colors[ImGuiCol_Border] = ImVec4(menu_color.x + 0.20f, menu_color.y + 0.20f, menu_color.z + 0.20f, 1.00f);
		colors[ImGuiCol_BorderShadow] = ImVec4(menu_color.x - 0.20f, menu_color.y - 0.20f, menu_color.z - 0.20f, 1.00f);

		colors[ImGuiCol_TitleBg] = ImVec4(menu_color.x + 0.20f, menu_color.y + 0.20f, menu_color.z + 0.20f, 1.00f);
		colors[ImGuiCol_TitleBgActive] = colors[ImGuiCol_TitleBg];
		colors[ImGuiCol_TitleBgCollapsed] = colors[ImGuiCol_TitleBg];

		colors[ImGuiCol_FrameBg] = ImVec4(menu_color.x - 0.30f, menu_color.y - 0.30f, menu_color.z - 0.30f, 0.75f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(menu_color.x - 0.30f, menu_color.y - 0.30f, menu_color.z - 0.30f, 0.75f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(menu_color.x + 0.20f, menu_color.y + 0.20f, menu_color.z + 0.20f, 0.75f);

		colors[ImGuiCol_CheckMark] = ImVec4(menu_color.x + 0.30f, menu_color.y + 0.30f, menu_color.z + 0.30f, 1.00f);

		colors[ImGuiCol_Button] = ImVec4(menu_color.x + 0.20f, menu_color.y + 0.20f, menu_color.z + 0.20f, 1.00f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(menu_color.x + 0.10f, menu_color.y + 0.10f, menu_color.z + 0.10f, 1.00f);
		colors[ImGuiCol_ButtonActive] = ImVec4(menu_color.x + 0.20f, menu_color.y + 0.20f, menu_color.z + 0.20f, 1.00f);

		colors[ImGuiCol_SliderGrab] = ImVec4(menu_color.x + 0.20f, menu_color.y + 0.20f, menu_color.z + 0.20f, 1.00f);
		colors[ImGuiCol_SliderGrabActive] = colors[ImGuiCol_SliderGrab];

		colors[ImGuiCol_Separator] = ImVec4(menu_color.x + 0.20f, menu_color.y + 0.20f, menu_color.z + 0.20f, 1.00f);
		colors[ImGuiCol_SeparatorHovered] = colors[ImGuiCol_Separator];
		colors[ImGuiCol_SeparatorActive] = colors[ImGuiCol_Separator];

		colors[ImGuiCol_Tab] = ImVec4(menu_color.x - 0.20f, menu_color.y - 0.20f, menu_color.z - 0.20f, 1.00f);
		colors[ImGuiCol_TabHovered] = colors[ImGuiCol_Tab];
		colors[ImGuiCol_TabActive] = colors[ImGuiCol_Tab];
		colors[ImGuiCol_TabUnfocused] = colors[ImGuiCol_Tab];
		colors[ImGuiCol_TabUnfocusedActive] = colors[ImGuiCol_Tab];

		colors[ImGuiCol_ChildBg] = colors[ImGuiCol_Separator];
		colors[ImGuiCol_PopupBg] = colors[ImGuiCol_Separator];

		colors[ImGuiCol_NavHighlight] = ImVec4(menu_color.x - 0.20f, menu_color.y - 0.20f, menu_color.z - 0.20f, 1.00f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(menu_color.x - 0.20f, menu_color.y - 0.20f, menu_color.z - 0.20f, 1.00f);

		colors[ImGuiCol_Header] = ImVec4(menu_color.x + 0.20f, menu_color.y + 0.20f, menu_color.z + 0.20f, 1.00f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(menu_color.x - 0.20f, menu_color.y - 0.20f, menu_color.z - 0.20f, 1.00f);
		colors[ImGuiCol_HeaderActive] = colors[ImGuiCol_Header];*/
	}

	__forceinline void __fastcall create_menu() noexcept {
		//VMProtectBeginVirtualization("create_menu");
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = nullptr;
		io.LogFilename = nullptr;

		tolstiy = io.Fonts->AddFontFromFileTTF(("C:/windows/fonts/ariblk.ttf"), 40.0f);
		arialbd_13 = io.Fonts->AddFontFromFileTTF(("C:/windows/fonts/arialbd.ttf"), 13.0f);
		arialbd_15 = io.Fonts->AddFontFromFileTTF(("C:/windows/fonts/arialbd.ttf"), 15.0f);

		D3DXCreateTextureFromFileInMemoryEx(u::device, &rawData1337, sizeof(rawData1337), 100, 100, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &profile_picture);
		D3DXCreateTextureFromFileInMemory(u::device, &raw_head, sizeof(raw_head), &image_head);
		D3DXCreateTextureFromFileInMemory(u::device, &raw_neck, sizeof(raw_neck), &image_neck);
		D3DXCreateTextureFromFileInMemory(u::device, &raw_chest, sizeof(raw_chest), &image_chest);
		D3DXCreateTextureFromFileInMemoryEx(u::device, &rage_bytes, sizeof(rage_bytes), 15, 15, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &rage);
		D3DXCreateTextureFromFileInMemoryEx(u::device, &legit_bytes, sizeof(legit_bytes), 15, 15, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &legit);
		D3DXCreateTextureFromFileInMemoryEx(u::device, &main_bytes, sizeof(main_bytes), 15, 15, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &main);
		D3DXCreateTextureFromFileInMemoryEx(u::device, &configs_bytes, sizeof(configs_bytes), 15, 15, D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &configs);

		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX9_Init(device);

		//VMProtectEnd();
	}
	__forceinline void __fastcall destroy_menu() noexcept {
		//VMProtectBeginVirtualization("destroy_menu");
		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
		//VMProtectEnd();
	}

	inline void Tabss()
	{
		ImVec2 pos;
		ImDrawList* draw;

		pos = ImGui::GetWindowPos();
		draw = ImGui::GetWindowDrawList();

		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Button] = ImColor(35, 35, 45, 0);
		colors[ImGuiCol_ButtonActive] = ImColor(63, 63, 60, 255);
		colors[ImGuiCol_ButtonHovered] = ImColor(63, 63, 60, 255);
		ImGui::PushFont(arialbd_13);
		ImGui::SetCursorPos(ImVec2(12, 94));
		if (ImGui::Button("##3", ImVec2(172, 31)))
			tab = 3;

		ImGui::SetCursorPos(ImVec2(12, 130));
		if (ImGui::Button("##2", ImVec2(172, 31)))
			tab = 2;

		ImGui::SetCursorPos(ImVec2(12, 230));
		if (ImGui::Button("##1", ImVec2(172, 31)))
			tab = 1;
		ImGui::SetCursorPos(ImVec2(12, 193));
		if (ImGui::Button("##4", ImVec2(172, 31)))
			tab = 4;

		static auto size1 = ImGui::CalcTextSize(("Coming Soon!"));
		static auto size2 = ImGui::CalcTextSize(("Legitbot"));
		static auto size3 = ImGui::CalcTextSize(("Configs"));
		static auto size4 = ImGui::CalcTextSize(("Settings"));

		draw->AddText(arialbd_13, 15.f, ImVec2(pos.x + 51, pos.y + 101), ImColor(255, 255, 255), ("Coming Soon!"));
		if (tab == 3) draw->AddLine({ pos.x + 51, pos.y + 101 + size1.y }, { pos.x + 51 + size1.x + 10, pos.y + 101 + size1.y }, ImColor(255, 255, 255));
		draw->AddText(arialbd_13, 15.f, ImVec2(pos.x + 51, pos.y + 137), ImColor(255, 255, 255), ("Legitbot"));
		if (tab == 2) draw->AddLine({ pos.x + 51, pos.y + 137 + size2.y }, { pos.x + 51 + size2.x + 5, pos.y + 137 + size2.y }, ImColor(255, 255, 255));
		draw->AddText(arialbd_13, 15.f, ImVec2(pos.x + 51, pos.y + 201), ImColor(255, 255, 255), ("Configs"));
		if (tab == 4) draw->AddLine({ pos.x + 51, pos.y + 201 + size3.y }, { pos.x + 51 + size3.x + 5, pos.y + 201 + size3.y }, ImColor(255, 255, 255));
		draw->AddText(arialbd_13, 15.f, ImVec2(pos.x + 51, pos.y + 237), ImColor(255, 255, 255), ("Settings"));
		if (tab == 1) draw->AddLine({ pos.x + 51, pos.y + 237 + size4.y }, { pos.x + 51 + size4.x + 5, pos.y + 237 + size4.y }, ImColor(255, 255, 255));

		ImGui::SetCursorPos(ImVec2(25, 102));
		ImGui::Image(rage, ImVec2(15, 15));

		ImGui::SetCursorPos(ImVec2(25, 138));
		ImGui::Image(legit, ImVec2(15, 15));

		ImGui::SetCursorPos(ImVec2(25, 201));
		ImGui::Image(main, ImVec2(15, 15));

		ImGui::SetCursorPos(ImVec2(25, 237));
		ImGui::Image(configs, ImVec2(15, 15));

		ImGui::PopFont();
	}

	void render() noexcept;
}