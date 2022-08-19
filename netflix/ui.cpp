#include "globals.h"

static const char* aim_type[] = { ("Hold"), ("Toggle") };
static const char* aim_keys[] = { ("Left Click"), ("MB4"), ("MB5") };

void u::render() noexcept {
    //VMProtectBeginVirtualization("render");
    MSG message;
    while (PeekMessage(&message, 0, 0, 0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessage(&message);
        if (message.message == WM_QUIT) {
            g::run = !g::run;
            return;
        }
    }

    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    static auto flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove;
    //static auto picker_flags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoTooltip /*| ImGuiColorEditFlags_NoLabel*/;

    update_style();

    ImGui::SetNextWindowPos({ -5, -1 });
    ImGui::SetNextWindowSize({ static_cast<float>(size.width), static_cast<float>(size.height) });
    ImGui::Begin(("##annihilation"), &g::run, flags);
    {
        auto pos = ImGui::GetWindowPos();
        auto draw = ImGui::GetWindowDrawList();

        //window size
        ImGui::SetWindowSize(ImVec2(810, 475));

        draw->AddRectFilled(ImVec2(pos.x + 190, pos.y + 0), ImVec2(pos.x + 807, pos.y + 457), ImColor(8, 8, 8), 8.f, 10);
        draw->AddRectFilled(ImVec2(pos.x + 0, pos.y + 0), ImVec2(pos.x + 190, pos.y + 457), ImColor(20, 20, 20, 230), 10.f, 5);

        draw->AddText(tolstiy, 35.f, ImVec2(pos.x + 16, pos.y + 26), ImColor(65, 186, 217), ("PASTAMAN"));
        draw->AddText(tolstiy, 35.f, ImVec2(pos.x + 17, pos.y + 26), ImColor(255, 255, 255), ("PASTAMAN"));

        draw->AddLine(ImVec2(pos.x + 0, pos.y + 393), ImVec2(pos.x + 190, pos.y + 394), ImColor(32, 32, 30));
        draw->AddLine(ImVec2(pos.x + 190, pos.y + 70), ImVec2(pos.x + 807, pos.y + 71), ImColor(32, 32, 30));

        draw->AddText(arialbd_13, 13.f, ImVec2(pos.x + 21, pos.y + 74), ImColor(55, 55, 55), ("Aimbot"));
        draw->AddText(arialbd_13, 13.f, ImVec2(pos.x + 21, pos.y + 173), ImColor(55, 55, 55), ("Settings"));

        Tabss();

        ImGui::SetCursorPos(ImVec2(100, 100));
        draw->AddCircleImageFilled(profile_picture, ImVec2(pos.x + 39, pos.y + 426), 23.f, ImColor(255, 255, 255), 360);
        draw->AddText(arialbd_13, 15.f, ImVec2(pos.x + 70, pos.y + 406), ImColor(255, 255, 255), ("madeust#7731"));
        draw->AddText(arialbd_13, 13.f, ImVec2(pos.x + 70, pos.y + 430), ImColor(55, 55, 55), ("till:"));
        draw->AddText(arialbd_13, 13.f, ImVec2(pos.x + 95, pos.y + 430), ImColor(22, 162, 240), tm_to_readable_time(timet_to_tm(string_to_timet(keyauthapp.data.expiry))).c_str());

        ImGui::PushFont(arialbd_15);

        switch (tab) {
        case 0:
            break;
        case 1:
            draw->AddRectFilled(ImVec2(pos.x + 210, pos.y + 90), ImVec2(pos.x + 490, pos.y + 450), ImColor(13, 11, 16));
            draw->AddLine(ImVec2(pos.x + 210, pos.y + 120), ImVec2(pos.x + 490, pos.y + 121), ImColor(32, 32, 30));
            draw->AddText(arialbd_13, 15.f, ImVec2(pos.x + 218, pos.y + 98), ImColor(255, 255, 255), ("Settings"));
            draw->AddRectFilled(ImVec2(pos.x + 506, pos.y + 90), ImVec2(pos.x + 786, pos.y + 450), ImColor(13, 11, 16));
            draw->AddLine(ImVec2(pos.x + 506, pos.y + 120), ImVec2(pos.x + 786, pos.y + 121), ImColor(32, 32, 30));
            draw->AddText(arialbd_13, 15.f, ImVec2(pos.x + 514, pos.y + 98), ImColor(255, 255, 255), ("Hitbox"));

            ImGui::BeginGroup();
            ImGui::SetCursorPos(ImVec2(223, 130));
            ImGui::Text(("Aim Key"));
            ImGui::SameLine();
            ImGui::SetNextItemWidth(135);
            ImGui::SetCursorPosX(321);
            ImGui::Combo(("##aimkey"), &settings.aimkey_option, aim_keys, 3);

            ImGui::SetCursorPos(ImVec2(223, 160));
            ImGui::Text(("Aim Type"));
            ImGui::SameLine();
            ImGui::SetNextItemWidth(135);
            ImGui::SetCursorPosX(321);
            ImGui::Combo(("##aimtype"), &settings.aimtype_option, aim_type, 2);

            ImGui::SetCursorPos(ImVec2(223, 190));
            ImGui::Text(("Aim Color"));
            ImGui::SameLine();
            ImGui::SetNextItemWidth(135);
            ImGui::SetCursorPosX(321);
            ImGui::Combo(("##aimcolor"), &colorMode, "Purple\0Yellow", 2);

            ImGui::SetCursorPos(ImVec2(223, 220));
            ImGui::Text(("Sensitivity"));
            ImGui::SameLine();
            ImGui::SetNextItemWidth(135);
            ImGui::SetCursorPosX(321);
            ImGui::InputFloat(("##sensitivity"), &settings.sensitivity, 0.01, 1, ("%.2f"), ImGuiInputTextFlags_AlwaysInsertMode | ImGuiInputTextFlags_CharsDecimal);



            ImGui::PushFont(arialbd_15);
            ImGui::SetCursorPos(ImVec2(227, 250));
            ImGui::Checkbox(("Recoil"), &settings.recoil);
            ImGui::SetCursorPos(ImVec2(223, 280));
            ImGui::PopFont();
            ImGui::hotkey("Recoil Key", settings.recoil_key, 0, { 65, 20 });

            ImGui::PushFont(arialbd_15);
            ImGui::SetCursorPos(ImVec2(227, 310));
            ImGui::Checkbox(("Trigger Bot"), &settings.trigger);
            ImGui::PopFont();

            if (settings.trigger == true) {
                ImGui::SetCursorPos(ImVec2(223, 340));
                ImGui::BeginGroup();
                ImGui::PushFont(arialbd_15);
                ImGui::Text(("Trigger Delay"));
                ImGui::SameLine();
                ImGui::SetNextItemWidth(135);
                ImGui::SetCursorPosX(320);
                ImGui::SliderInt(("##Trigger Delay"), &settings.triggerdelay, 1, 100);
                ImGui::SetCursorPos(ImVec2(227, 370));
                ImGui::PopFont();
            }


            ImGui::SetCursorPos(ImVec2(520, 130));
            if (ImGui::RadioButton(("Head##2"), &settings.snapValue, 1)) {
                settings.snapValue = 1;
            }

            ImGui::SetCursorPos(ImVec2(520, 160));
            if (ImGui::RadioButton(("Neck##2"), &settings.snapValue, 11)) {
                settings.snapValue = 11;
            }
         
            ImGui::SetCursorPos(ImVec2(520, 190));
            if (ImGui::RadioButton(("Chest##2"), &settings.snapValue, 28)) {
                settings.snapValue = 28;
            }

            ImGui::SetCursorPos(ImVec2(550, 120));
            switch (settings.snapValue) {
            case 1:
                ImGui::Image((void*)image_head, ImVec2(200, 300));
                break;
            case 11:
                ImGui::Image((void*)image_neck, ImVec2(200, 300));
                break;
            case 28:
                ImGui::Image((void*)image_chest, ImVec2(200, 300));
                break;
            }

            ImGui::EndGroup();
            break;
        case 2:
            //SILENT
            ImGui::BeginGroup();
            draw->AddRectFilled(ImVec2(pos.x + 210, pos.y + 90), ImVec2(pos.x + 490, pos.y + 450), ImColor(13, 11, 16));
            draw->AddLine(ImVec2(pos.x + 210, pos.y + 120), ImVec2(pos.x + 490, pos.y + 121), ImColor(32, 32, 30));
            draw->AddText(arialbd_13, 15.f, ImVec2(pos.x + 218, pos.y + 98), ImColor(255, 255, 255), ("Legit Aim"));

            ImGui::SetCursorPos(ImVec2(255, 95));

            ImGui::Checkbox(("##blank"), &settings.global_legit);

            if (settings.global_legit) {
                settings.global_rage = false;
            }

            if (settings.global_legit && !settings.global_rage) {

                ImGui::SetCursorPos(ImVec2(222, 130));

                ImGui::BeginGroup();
                ImGui::PushFont(arialbd_15);
                ImGui::Text(("Speed"));
                ImGui::SameLine();
                ImGui::SetNextItemWidth(135);
                ImGui::SetCursorPosX(320);
                ImGui::SliderFloat(("##Speed"), &settings.smoothing, 0.01, 0.5, ("%.2f"));
                ImGui::PopFont();

                //ImGui::SetCursorPos(ImVec2(223, 160));

               /* ImGui::BeginGroup();
                ImGui::PushFont(arialbd_15);
                ImGui::Text("FOV X");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(135);
                ImGui::SetCursorPosX(321);
                ImGui::SliderInt("##fovx", &settings.fovx, 1, 400);
                ImGui::PopFont();
                ImGui::PushFont(arialbd_15);
                ImGui::Text("FOV Y");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(135);
                ImGui::SetCursorPosX(321);
                ImGui::SliderInt("##fovy", &settings.fovy, 1, 300);
                ImGui::PopFont();
                ImGui::EndGroup();*/

                //ImGui::BeginGroup();
                //draw->AddRectFilled(ImVec2(pos.x + 506, pos.y + 90), ImVec2(pos.x + 786, pos.y + 450), ImColor(13, 11, 16));
                //draw->AddLine(ImVec2(pos.x + 506, pos.y + 120), ImVec2(pos.x + 786, pos.y + 121), ImColor(32, 32, 30));
                ////draw->AddText(ne_takoi_tolstiy, 15.f, ImVec2(pos.x + 516, pos.y + 98), ImColor(255, 255, 255), "Silent");

                //ImGui::EndGroup();
            }
            ImGui::EndGroup();
            break;
        case 3:
            //SILENT
            draw->AddRectFilled(ImVec2(pos.x + 210, pos.y + 90), ImVec2(pos.x + 490, pos.y + 450), ImColor(13, 11, 16));
            draw->AddLine(ImVec2(pos.x + 210, pos.y + 120), ImVec2(pos.x + 490, pos.y + 121), ImColor(32, 32, 30));
            draw->AddText(arialbd_13, 15.f, ImVec2(pos.x + 218, pos.y + 98), ImColor(255, 255, 255), ("Coming Soon!"));

        /*    ImGui::SetCursorPos(ImVec2(255, 95));
            ImGui::Checkbox("##blank", &settings.global_rage);
            if (settings.global_rage) {
                settings.global_legit = false;
            }

            if (settings.global_rage && !settings.global_legit) {
                ImGui::SetCursorPos(ImVec2(222, 130));*/

                //ImGui::BeginGroup();
                //ImGui::SetCursorPos(ImVec2(230, 130));
                //ImGui::Checkbox("Silent", &settings.silent);
                //if (settings.silent) {
                //    ImGui::SetCursorPos(ImVec2(230, 160));
                //    settings.flick = false;
                //}
                //ImGui::EndGroup();
                //
              /*  ImGui::BeginGroup();
                ImGui::SetCursorPos(ImVec2(230, 160));
                ImGui::Checkbox("Insta Flick", &settings.flick);
                if (settings.flick) {
                    ImGui::SetCursorPos(ImVec2(230, 160));
                    settings.silent = false;
                }
                ImGui::EndGroup();*/

               /* ImGui::SetCursorPos(ImVec2(223, 190));

                ImGui::BeginGroup();
                ImGui::PushFont(arialbd_15);
                ImGui::Text("FOV");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(135);
                ImGui::SetCursorPosX(321);
                ImGui::SliderInt("##fov", &settings.fov, 1, 200);

                ImGui::PopFont();
                ImGui::EndGroup();*/

                /*ImGui::BeginGroup();
                draw->AddRectFilled(ImVec2(pos.x + 506, pos.y + 90), ImVec2(pos.x + 786, pos.y + 450), ImColor(13, 11, 16));
                draw->AddLine(ImVec2(pos.x + 506, pos.y + 120), ImVec2(pos.x + 786, pos.y + 121), ImColor(32, 32, 30));*/
                //draw->AddText(ne_takoi_tolstiy, 15.f, ImVec2(pos.x + 516, pos.y + 98), ImColor(255, 255, 255), "Silent");

               

               /* ImGui::EndGroup();*/
            /*}*/
            break;
        case 4:
            draw->AddRectFilled(ImVec2(pos.x + 210, pos.y + 90), ImVec2(pos.x + 490, pos.y + 450), ImColor(13, 11, 16));
            draw->AddLine(ImVec2(pos.x + 210, pos.y + 120), ImVec2(pos.x + 490, pos.y + 121), ImColor(32, 32, 30));
            draw->AddRectFilled(ImVec2(pos.x + 506, pos.y + 90), ImVec2(pos.x + 786, pos.y + 450), ImColor(13, 11, 16));
            draw->AddLine(ImVec2(pos.x + 506, pos.y + 120), ImVec2(pos.x + 786, pos.y + 121), ImColor(32, 32, 30));
            draw->AddText(arialbd_13, 15.f, ImVec2(pos.x + 514, pos.y + 98), ImColor(255, 255, 255), ("info"));
            draw->AddText(arialbd_13, 15.f, ImVec2(pos.x + 514, pos.y + 130), ImColor(255, 255, 255), (R"(Huge thanks to "Rea" for helping me so
much with the project. You did such
an amazing job. I couldn't have done it
with out you and your very generous help!
You can join our discord below to support
us and keep updated with "Aman VAL"
thanks again "Rea" <3
- Much love, aman_anthony)"));

            ImGui::SetCursorPos(ImVec2(223, 130));
            if (ImGui::Button(("save config"))) {
                g::save_config();
            }
            ImGui::SetCursorPos(ImVec2(223, 160));
            if (ImGui::Button(("load config"))) {
                g::load_config();
            }

            ImGui::SetCursorPos(ImVec2(514, 330));

            if (ImGui::Button(("-> discord server <-"))) {
                ShellExecute(0, 0, ("https://discord.gg/r8NVSMcHgm"), 0, 0, SW_SHOW);
            }
            break;
        default:
            break;
        }

        ImGui::PopFont();
        ImGui::End();
    }

    ImGui::EndFrame();

    device->SetRenderState(D3DRS_ZENABLE, FALSE);
    device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
    device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

    if (device->BeginScene() >= 0) {
        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
        device->EndScene();
    }

    const auto result = device->Present(0, 0, 0, 0);
    if (result == D3DERR_DEVICELOST && device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
        reset_device();
    }
    //VMProtectEnd();
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND window, UINT message, WPARAM w_param, LPARAM l_param);

LRESULT __stdcall window_process(const HWND window, const UINT message, const WPARAM w_param, const LPARAM l_param) {
    //VMProtectBeginVirtualization("window_process");
    if (ImGui_ImplWin32_WndProcHandler(
        window,
        message,
        w_param,
        l_param))
        return 1L;

    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0L;

    case WM_LBUTTONDOWN:
        u::window_pos = MAKEPOINTS(l_param);
        return 0L;

    case WM_MOUSEMOVE:
        if (w_param == MK_LBUTTON) {
            const auto points = MAKEPOINTS(l_param);

            auto rect = RECT{ };
            GetWindowRect(u::window, &rect);

            rect.left += points.x - u::window_pos.x;
            rect.top += points.y - u::window_pos.y;

            if (u::window_pos.x >= 0 &&
                u::window_pos.x <= u::size.width &&
                u::window_pos.y >= 0 && u::window_pos.y <= 19) {

                SetWindowPos(
                    u::window,
                    HWND_TOP,
                    rect.left,
                    rect.top,
                    0,
                    0,
                    SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER
                );
            }
        }

        return 0L;
    }

    //VMProtectEnd();

    return DefWindowProc(
        window,
        message,
        w_param,
        l_param
    );
}

struct Key {
    constexpr Key(std::string_view name, int code) : name{ name }, code{ code } {  }

    std::string_view name;
    int code;
};

// indices must match KeyBind::KeyCode enum
static constexpr auto keyMap = std::to_array<Key>({
    { "'", VK_OEM_7 },
    { ",", VK_OEM_COMMA },
    { "-", VK_OEM_MINUS },
    { ".", VK_OEM_PERIOD },
    { "/", VK_OEM_2 },
    { "0", '0' },
    { "1", '1' },
    { "2", '2' },
    { "3", '3' },
    { "4", '4' },
    { "5", '5' },
    { "6", '6' },
    { "7", '7' },
    { "8", '8' },
    { "9", '9' },
    { ";", VK_OEM_1 },
    { "=", VK_OEM_PLUS },
    { "A", 'A' },
    { "ADD", VK_ADD },
    { "B", 'B' },
    { "BACKSPACE", VK_BACK },
    { "C", 'C' },
    { "CAPSLOCK", VK_CAPITAL },
    { "D", 'D' },
    { "DECIMAL", VK_DECIMAL },
    { "DELETE", VK_DELETE },
    { "DIVIDE", VK_DIVIDE },
    { "DOWN", VK_DOWN },
    { "E", 'E' },
    { "END", VK_END },
    { "ENTER", VK_RETURN },
    { "F", 'F' },
    { "F1", VK_F1 },
    { "F10", VK_F10 },
    { "F11", VK_F11 },
    { "F12", VK_F12 },
    { "F2", VK_F2 },
    { "F3", VK_F3 },
    { "F4", VK_F4 },
    { "F5", VK_F5 },
    { "F6", VK_F6 },
    { "F7", VK_F7 },
    { "F8", VK_F8 },
    { "F9", VK_F9 },
    { "G", 'G' },
    { "H", 'H' },
    { "HOME", VK_HOME },
    { "I", 'I' },
    { "INSERT", VK_INSERT },
    { "J", 'J' },
    { "K", 'K' },
    { "L", 'L' },
    { "LALT", VK_LMENU },
    { "LCTRL", VK_LCONTROL },
    { "LEFT", VK_LEFT },
    { "LSHIFT", VK_LSHIFT },
    { "M", 'M' },
    { "MOUSE1", 0 },
    { "MOUSE2", 1 },
    { "MOUSE3", 2 },
    { "MOUSE4", 3 },
    { "MOUSE5", 4 },
    { "MULTIPLY", VK_MULTIPLY },
    { "MWHEEL_DOWN", 0 },
    { "MWHEEL_UP", 0 },
    { "N", 'N' },
    { "NONE", 0 },
    { "NUMPAD_0", VK_NUMPAD0 },
    { "NUMPAD_1", VK_NUMPAD1 },
    { "NUMPAD_2", VK_NUMPAD2 },
    { "NUMPAD_3", VK_NUMPAD3 },
    { "NUMPAD_4", VK_NUMPAD4 },
    { "NUMPAD_5", VK_NUMPAD5 },
    { "NUMPAD_6", VK_NUMPAD6 },
    { "NUMPAD_7", VK_NUMPAD7 },
    { "NUMPAD_8", VK_NUMPAD8 },
    { "NUMPAD_9", VK_NUMPAD9 },
    { "O", 'O' },
    { "P", 'P' },
    { "PAGE_DOWN", VK_NEXT },
    { "PAGE_UP", VK_PRIOR },
    { "Q", 'Q' },
    { "R", 'R' },
    { "RALT", VK_RMENU },
    { "RCTRL", VK_RCONTROL },
    { "RIGHT", VK_RIGHT },
    { "RSHIFT", VK_RSHIFT },
    { "S", 'S' },
    { "SPACE", VK_SPACE },
    { "SUBTRACT", VK_SUBTRACT },
    { "T", 'T' },
    { "TAB", VK_TAB },
    { "U", 'U' },
    { "UP", VK_UP },
    { "V", 'V' },
    { "W", 'W' },
    { "X", 'X' },
    { "Y", 'Y' },
    { "Z", 'Z' },
    { "[", VK_OEM_4 },
    { "\\", VK_OEM_5 },
    { "]", VK_OEM_6 },
    { "`", VK_OEM_3 }
    });

static_assert(keyMap.size() == KeyBind::MAX);
static_assert(std::ranges::is_sorted(keyMap, {}, & Key::name));

KeyBind::KeyBind(KeyCode keyCode) noexcept : keyCode{ static_cast<std::size_t>(keyCode) < keyMap.size() ? keyCode : KeyCode::NONE } {}

KeyBind::KeyBind(const char* keyName) noexcept
{
    if (const auto it = std::ranges::lower_bound(keyMap, keyName, {}, &Key::name); it != keyMap.end() && it->name == keyName)
        keyCode = static_cast<KeyCode>(std::distance(keyMap.begin(), it));
    else
        keyCode = KeyCode::NONE;
}

const char* KeyBind::toString() const noexcept
{
    return keyMap[static_cast<std::size_t>(keyCode) < keyMap.size() ? keyCode : KeyCode::NONE].name.data();
}

bool KeyBind::isPressed() const noexcept
{
    if (keyCode == KeyCode::NONE)
        return false;

    if (keyCode == KeyCode::MOUSEWHEEL_DOWN)
        return ImGui::GetIO().MouseWheel < 0.0f;

    if (keyCode == KeyCode::MOUSEWHEEL_UP)
        return ImGui::GetIO().MouseWheel > 0.0f;

    if (keyCode >= KeyCode::MOUSE1 && keyCode <= KeyCode::MOUSE5)
        return ImGui::IsMouseClicked(keyMap[keyCode].code);

    return static_cast<std::size_t>(keyCode) < keyMap.size() && ImGui::IsKeyPressed(keyMap[keyCode].code, false);
}

bool KeyBind::isDown() const noexcept
{
    if (keyCode == KeyCode::NONE)
        return false;

    if (keyCode == KeyCode::MOUSEWHEEL_DOWN)
        return ImGui::GetIO().MouseWheel < 0.0f;

    if (keyCode == KeyCode::MOUSEWHEEL_UP)
        return ImGui::GetIO().MouseWheel > 0.0f;

    if (keyCode >= KeyCode::MOUSE1 && keyCode <= KeyCode::MOUSE5)
        return ImGui::IsMouseDown(keyMap[keyCode].code);

    return static_cast<std::size_t>(keyCode) < keyMap.size() && ImGui::IsKeyDown(keyMap[keyCode].code);
}

bool KeyBind::setToPressedKey() noexcept
{
    if (ImGui::IsKeyPressed(ImGui::GetIO().KeyMap[ImGuiKey_Escape])) {
        keyCode = KeyCode::NONE;
        return true;
    }
    else if (ImGui::GetIO().MouseWheel < 0.0f) {
        keyCode = KeyCode::MOUSEWHEEL_DOWN;
        return true;
    }
    else if (ImGui::GetIO().MouseWheel > 0.0f) {
        keyCode = KeyCode::MOUSEWHEEL_UP;
        return true;
    }

    for (int i = 0; i < IM_ARRAYSIZE(ImGui::GetIO().MouseDown); ++i) {
        if (ImGui::IsMouseClicked(i)) {
            keyCode = KeyCode(KeyCode::MOUSE1 + i);
            return true;
        }
    }

    for (int i = 0; i < IM_ARRAYSIZE(ImGui::GetIO().KeysDown); ++i) {
        if (!ImGui::IsKeyPressed(i))
            continue;

        if (const auto it = std::ranges::find(keyMap, i, &Key::code); it != keyMap.end()) {
            keyCode = static_cast<KeyCode>(std::distance(keyMap.begin(), it));
            // Treat AltGr as RALT
            if (keyCode == KeyCode::LCTRL && ImGui::IsKeyPressed(keyMap[KeyCode::RALT].code))
                keyCode = KeyCode::RALT;
            return true;
        }
    }
    return false;
}

void KeyBindToggle::handleToggle() noexcept
{
    if (isPressed())
        toggledOn = !toggledOn;
}