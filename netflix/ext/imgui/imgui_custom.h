#pragma once

#include "imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui_internal.h"

#include <algorithm>
#include <iterator>
#include <numeric>
#include <array>

class KeyBind {
public:
    enum KeyCode : unsigned char {
        APOSTROPHE = 0,
        COMMA,
        MINUS,
        PERIOD,
        SLASH,
        KEY_0,
        KEY_1,
        KEY_2,
        KEY_3,
        KEY_4,
        KEY_5,
        KEY_6,
        KEY_7,
        KEY_8,
        KEY_9,
        SEMICOLON,
        EQUALS,
        A,
        ADD,
        B,
        BACKSPACE,
        C,
        CAPSLOCK,
        D,
        DECIMAL,
        DEL,
        DIVIDE,
        DOWN,
        E,
        END,
        ENTER,
        F,
        F1,
        F10,
        F11,
        F12,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        G,
        H,
        HOME,
        I,
        INSERT,
        J,
        K,
        L,
        LALT,
        LCTRL,
        LEFT,
        LSHIFT,
        M,
        MOUSE1,
        MOUSE2,
        MOUSE3,
        MOUSE4,
        MOUSE5,
        MULTIPLY,
        MOUSEWHEEL_DOWN,
        MOUSEWHEEL_UP,
        N,
        NONE,
        NUMPAD_0,
        NUMPAD_1,
        NUMPAD_2,
        NUMPAD_3,
        NUMPAD_4,
        NUMPAD_5,
        NUMPAD_6,
        NUMPAD_7,
        NUMPAD_8,
        NUMPAD_9,
        O,
        P,
        PAGE_DOWN,
        PAGE_UP,
        Q,
        R,
        RALT,
        RCTRL,
        RIGHT,
        RSHIFT,
        S,
        SPACE,
        SUBTRACT,
        T,
        TAB,
        U,
        UP,
        V,
        W,
        X,
        Y,
        Z,
        LEFTBRACKET,
        BACKSLASH,
        RIGHTBRACKET,
        BACKTICK,

        MAX
    };

    KeyBind() = default;
    explicit KeyBind(KeyCode keyCode) noexcept;
    explicit KeyBind(const char* keyName) noexcept;

    bool operator==(KeyCode keyCode) const noexcept { return this->keyCode == keyCode; }
    friend bool operator==(const KeyBind& a, const KeyBind& b) noexcept { return a.keyCode == b.keyCode; }

    [[nodiscard]] const char* toString() const noexcept;
    [[nodiscard]] bool isPressed() const noexcept;
    [[nodiscard]] bool isDown() const noexcept;
    [[nodiscard]] bool isSet() const noexcept { return keyCode != KeyCode::NONE; }

    bool setToPressedKey() noexcept;
private:
    KeyCode keyCode = KeyCode::NONE;
};

class KeyBindToggle : public KeyBind {
public:
    using KeyBind::KeyBind;

    void handleToggle() noexcept;
    [[nodiscard]] bool isToggled() const noexcept { return toggledOn; }
private:
    bool toggledOn = true;
};

namespace ImGui {
	IMGUI_API void ColorPicker(const char* name, float color[3]) noexcept;
	IMGUI_API void arrowButtonDisabled(const char* id, ImGuiDir dir) noexcept;
	IMGUI_API void progressBarFullWidth(float fraction, float height) noexcept;
	IMGUI_API void textUnformattedCentered(const char* text) noexcept;
	IMGUI_API void RenderBoxBorder(ImVec2 p_min, ImVec2 p_max, ImU32 border, ImU32 border_shadow, float rounding);
	IMGUI_API void RenderFilledBox(ImVec2 p_min, ImVec2 p_max, ImU32 fill_col, float rounding);
	IMGUI_API bool AnimatedCheckbox(const char* label, bool* v);
	IMGUI_API bool AnimatedButtonEx(const char* label, const ImVec2& size_arg, ImGuiButtonFlags flags);
	IMGUI_API bool AnimatedButton(const char* label, const ImVec2& size_arg);
	IMGUI_API void CustomRenderFrame(ImVec2 p_min, ImVec2 p_max, ImU32 fill_col, bool border, float rounding);

    IMGUI_API void hotkey(const char* label, KeyBind& key, float samelineOffset, const ImVec2& size) noexcept;

	namespace Animations {
		/*
		// Usage:
		//  int trickInt = ImTricks::Animations::FastLerpInt("trickInt", enable_animation, 0, 255, 15);
		//  draw->AddRectFilled(p, p + ImVec2(30, 30), ImColor(255, 255, 255, trickInt));
		*/
		extern int FastIntLerp(const char* identifier, bool state, int min, int max, int speed);

		/*
		// Usage:
		//  float trickFloat = ImTricks::Animations::FastLerpInt("trickFloat", enable_animation, 0.f, 1.f, 0.05f);
		//  draw->AddRectFilled(p, p + ImVec2(30, 30), ImColor(1.f, 1.f, 1.f, trickFloat));
		*/
		extern float FastFloatLerp(const char* identifier, bool state, float min, float max, float speed);


		/*
		// Usage:
		//  float trickFloat = ImTricks::Animations::FastFloatLerp("header", enable_animation, 0.f, 1.f, 0.05f);
		//  ImVec2 pos1 = ImTricks::Animations::FastImVec2Lerp("pos1", enable_animation, ImVec2(0, 50), ImVec2(100, 50), 5);
		//  ImVec2 pos2 = ImTricks::Animations::FastImVec2Lerp("pos2", enable_animation, ImVec2(413, 80), ImVec2(513, 80), 5);
		//  draw->AddRectFilled(p + pos1, p + pos2, ImTricks::Animations::FastColorLerp(ImColor(255, 0, 0), ImColor(0, 255, 0), trickFloat));
		*/
		extern ImVec2 FastImVec2Lerp(const char* identifier, bool state, ImVec2 min, ImVec2 max, float speed);

		/*
		// Usage:
		//	float trickFloat = ImTricks::Animations::FastLerpFloat("header", check, 0.f, 1.f, 0.05f);
		//	draw->AddRectFilled(p, p + ImVec2(513, 30), ImTricks::Animations::FastColorLerp(ImColor(255, 0, 0), ImColor(0, 255, 0), trickFloat));
		*/
		extern ImColor FastColorLerp(ImColor start, ImColor end, float stage);
	}
}