#include "globals.h"
#include "dll_array.h"
#include <tchar.h>

void keybinds(void) {
	while (g::run) {
		switch (settings.aimkey_option) {
		case 0: // mouse 1
			aim_key = VK_LBUTTON;
			break;
		case 1: // mouse 4
			aim_key = VK_XBUTTON1;
			break;
		case 2: // mouse 5
			aim_key = VK_XBUTTON2;
			break;
		}

		switch (settings.aimtype_option) {
		case 0: // hold
			if (GetAsyncKeyState(aim_key)) {
				left_down = true;
				settings.aim = true;
			}
			else {
				left_down = false;
				settings.aim = false;
			}
			break;
		case 1: // toggle
			if (GetAsyncKeyState(aim_key) & 1) {
				left_down = !left_down;
				settings.aim = !settings.aim;
			}
			break;
		}

		if (GetAsyncKeyState(VK_END) & 1) {
			g::run = false;
		}
	}
}
#define DLL_FILE TEXT(("C:/temp/nt.dll"))

int start() {

	auto hdll = LoadLibraryA(DLL_FILE);
	mouse_button = (pDD_btn)GetProcAddress(hdll, ("DD_btn"));
	mouse_move_rel = (pDD_movR)GetProcAddress(hdll, ("DD_movR"));
	mouse_move_abs = (pDD_mov)GetProcAddress(hdll, ("DD_mov"));

	if (!(mouse_button && mouse_move_rel && mouse_move_abs)) {
		return -2;
	}
	int st = mouse_button(0);
	if (st != 1) {
		return st;
	}

	if (!u::create_window(("aman"))) {
		return g::dialog(("failed to create window."));
	}

	if (!u::create_device()) {
		u::destroy_window();
		return g::dialog(("failed to create device."));
	}

	u::create_menu();

	std::thread(bot).detach();
	std::thread(logic).detach();
	std::thread(keybinds).detach();

	while (g::run) {
		u::render();
		std::this_thread::sleep_for(std::chrono::milliseconds(8));
	}

	// clean up
	u::destroy_menu();
	u::destroy_device();
	u::destroy_window();

	FreeLibrary(hdll);
}

int main() {
	start();
}

int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	start();
}

// used so you can use as a dll with rundll32.exe and execute from an export you can also inject shellcode to execute the export in any process
//extern "C" __declspec (dllexport) void __cdecl start(HWND hwnd, HINSTANCE hinst, LPTSTR lp_cmd_line, int n_cmd_show) {
//	start();
//}