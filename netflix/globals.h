#pragma once
//#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <d3d9.h>
#include <d3dx9tex.h>
#include <shellapi.h>
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <sys/stat.h>
#include <string>
#include <filesystem>

#ifdef _WIN32
#include <io.h>
#define access    _access_s
#else
#include <unistd.h>
#endif

#include "mouse.h"

//#include <imgui/imgui.h>
//#include <imgui/imgui_impl_dx9.h>
//#include <imgui/imgui_impl_win32.h>
//#include <imgui/imgui_custom.h>
//#include <font_awesome.h>

#include "auth.hpp"

inline std::string name = ("kebapcedomasno");
inline std::string ownerid = ("JodfjDebCJ");
inline std::string secret = ("66018025cf4ec121b1ab98e2d5f5acffd2431b2fd1a13b850fba6071ed063660");
inline std::string version = ("1.0");
inline std::string url = ("https://keyauth.win/api/1.1/"); // change if you're self-hosting
inline std::string sslPin = ("ssl pin key (optional)");

inline KeyAuth::api keyauthapp(name, ownerid, secret, version, url, sslPin);

#include "ext/imgui/imgui.h"
#include "ext/imgui/imgui_impl_dx9.h"
#include "ext/imgui/imgui_impl_win32.h"
#include "ext/imgui/imgui_custom.h"
#include "ext/font_awesome.h"

inline struct s_settings {
	bool global_legit = true;
	bool global_rage = false;

	int aimkey_option = 0;
	int aimtype_option = 0;
	int aimcolor_option = 0;
	int rage_hitbox = 0;
	int legit_hitbox = 0;
	int fovx = 100;
	int fovy = 100;

	float sensitivity = 0.5f;
	float smoothing = 0.25f;
	int mode = 3;

	bool recoil = false;
	bool aim = false;
	bool hold = true;
	bool trigger = false;

	int snapValue = 1;
	int triggerdelay = 10;

	KeyBind recoil_key;
	KeyBind trigger_key;
} settings;

#include "byte_arrays.h"
#include "ui.h"

namespace g {
	inline bool run = true;

	__forceinline const int __fastcall dialog(const std::string& text) noexcept {
		MessageBeep(MB_ICONERROR);
		return MessageBoxA(
			u::window ? u::window : NULL,
			text.c_str(),
			("aman"),
			MB_ICONERROR | MB_OK
			);
	}

	__forceinline bool save_config() {
		// in the future this will be saved to the cloud
		FILE* file = NULL;
		errno_t err = fopen_s(&file, ("config.aman"), ("wb+"));
		if (err != 0) {
			return false;
		}

		fwrite(&settings, sizeof(settings), 1, file);
		fclose(file);
		return true;
	}

	__forceinline bool load_config() {
		// in the future this will be loaded from the cloud
		FILE* file = NULL;
		errno_t err = fopen_s(&file, ("config.aman"), ("rb"));
		if (err != 0) {
			return false;
		}

		fread(&settings, sizeof(settings), 1, file);
		fclose(file);
		return true;
	}
}

#include "color_bot.h"

inline std::string tm_to_readable_time(tm ctx) {
	char buffer[80];

	strftime(buffer, sizeof(buffer), ("%a %m/%d/%y"), &ctx);

	return std::string(buffer);
}

inline static std::time_t string_to_timet(std::string timestamp) {
	auto cv = strtol(timestamp.c_str(), NULL, 10); // long

	return (time_t)cv;
}

inline static std::tm timet_to_tm(time_t timestamp) {
	std::tm context;

	localtime_s(&context, &timestamp);

	return context;
}