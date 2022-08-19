#pragma once

#include "globals.h"

#define INAME ("VALORANT  ") 

//inline int fovW = 200;
//inline int fovH = 100;
inline std::chrono::high_resolution_clock lastFlick;
inline int colorMode = 0;
inline BYTE* screenData = 0;
inline const int screen_width = GetSystemMetrics(SM_CXSCREEN), screen_height = GetSystemMetrics(SM_CYSCREEN);

inline int aim_x = 0;
inline int aim_y = 0;
inline POINT aim_rage{};

inline bool left_down = false;
inline auto aim_key = VK_LBUTTON;

struct point {
	double x;
	double y;
	point(double x, double y) : x(x), y(y) {}
};

inline bool is_color(int red, int green, int blue) {
	// color purple
	if (colorMode == 0) {
		if (green >= 190) {
			return false;
		}

		if (green >= 140) {
			return abs(red - blue) <= 8 &&
				red - green >= 50 &&
				blue - green >= 50 &&
				red >= 105 &&
				blue >= 105;
		}

		return abs(red - blue) <= 13 &&
			red - green >= 60 &&
			blue - green >= 60 &&
			red >= 110 &&
			blue >= 100;
	}

	// yellow
	else {
		if (red < 160)
		{
			return false;
		}
		if (red > 161 && red < 255) {
			return green > 150 && green < 255 && blue > 0 && blue < 79;
		}
		return false;
	}
}

inline bool scan(HDC dc, int area_x, int area_y) {
	COLORREF col;
	for (int y = 2 * (-1); y < 2; ++y) {
		for (int x = 3 * (-1); x < 3; ++x) {
			col = GetPixel(dc, area_x + x, area_y + y);
			if (is_color((short)GetRValue(col), (short)GetGValue(col), (short)GetBValue(col))) {
				return true;
			}
		}
	}
	return false;
}

inline bool in_range(unsigned low, unsigned high, unsigned x) {
	return (low <= x && x <= high);
}

//bot with purple (original (again not default))
inline void bot() {
	int w = settings.fovx, h = settings.fovy;
	auto t_start = std::chrono::high_resolution_clock::now();
	auto t_end = std::chrono::high_resolution_clock::now();

	HDC hScreen = GetDC(NULL);
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, w, h);
	screenData = (BYTE*)malloc(5 * screen_width * screen_height);
	HDC hDC = CreateCompatibleDC(hScreen);
	point middle_screen(screen_width / 2, screen_height / 2);

	BITMAPINFOHEADER bmi = { 0 };
	bmi.biSize = sizeof(BITMAPINFOHEADER);
	bmi.biPlanes = 1;
	bmi.biBitCount = 32;
	bmi.biWidth = w;
	bmi.biHeight = -h;
	bmi.biCompression = BI_RGB;
	bmi.biSizeImage = 0;

	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
	while (g::run) {
		//if (w != settings.fovx || h != settings.fovy) {
		//	w = settings.fovx, h = settings.fovy;
		//	//DeleteObject(hBitmap);
		//	hBitmap = CreateCompatibleBitmap(hScreen, w, h);
		//}
		//SetBitmapDimensionEx(hBitmap, w, h, NULL);

		std::this_thread::sleep_for(std::chrono::milliseconds(7));
		HGDIOBJ old_obj = SelectObject(hDC, hBitmap);
		BOOL bRet = BitBlt(hDC, 0, 0, w, h, hScreen, middle_screen.x - (w / 2), middle_screen.y - (h / 2), SRCCOPY);
		SelectObject(hDC, old_obj);
		GetDIBits(hDC, hBitmap, 0, h, screenData, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);
		bool stop_loop = false;
		for (int j = 0; j < h; ++j) {
			for (int i = 0; i < w * 4; i += 4) {
				unsigned short red = screenData[i + (j * w * 4) + 2] & 255;
				unsigned short green = screenData[i + (j * w * 4) + 1] & 255;
				unsigned short blue = screenData[i + (j * w * 4) + 0] & 255;

				if (is_color(red, green, blue)) { // determine if the pixel color is purple or yellow
					aim_x = (i / 4) - (w / 2);
					aim_y = j - (h / 2) + settings.snapValue;

					stop_loop = true;
					break;
				}
			}
			if (stop_loop) {
				break;
			}
		}
		if (!stop_loop) {
			aim_x = 0;
			aim_y = 0;
		}
	}
}

inline void logic(void) {

	auto t_start = std::chrono::high_resolution_clock::now();
	auto t_end = std::chrono::high_resolution_clock::now();
	auto left_start = std::chrono::high_resolution_clock::now();
	auto left_end = std::chrono::high_resolution_clock::now();

	HWND deeznuts;
	deeznuts = FindWindowA(NULL, INAME);
	HDC nDC = GetDC(deeznuts);

	double sensitivity_x = 1.0 / settings.sensitivity / (screen_width / screen_width) * 1.08;
	double sensitivity_y = 1.0 / settings.sensitivity / (screen_height / screen_height) * 1.08;

	while (g::run) {
		settings.sensitivity = settings.sensitivity /** 10*/;
		t_end = std::chrono::high_resolution_clock::now();
		double elapsed_time_ms = std::chrono::duration<double, std::milli>(t_end - t_start).count();

		if (settings.aim && (settings.global_legit || settings.global_rage)) {
			CURSORINFO cursorInfo = { 0 };
			cursorInfo.cbSize = sizeof(cursorInfo);
			GetCursorInfo(&cursorInfo);
			if (cursorInfo.flags != 1) {
				if (settings.global_rage) {
					left_down = true;
					if (elapsed_time_ms > 7) {
						t_start = std::chrono::high_resolution_clock::now();
						// left_start = std::chrono::high_resolution_clock::now();
						if (aim_x != 0 || aim_y != 0) {
							mouse_move_rel(double(aim_rage.x) * sensitivity_x, double(aim_rage.y) * sensitivity_y);
						}
					}
				}
				else if (settings.global_legit) {
					if (elapsed_time_ms > 7) {
						t_start = std::chrono::high_resolution_clock::now();
						if (aim_x != 0 || aim_y != 0) {
							if (aim_x >= -15 && aim_x <= 15 && aim_y >= -30 && aim_y <= 5 && settings.trigger) {
								mouse_button(1);
								Sleep(settings.triggerdelay);
								mouse_button(2);
							}

							left_end = std::chrono::high_resolution_clock::now();
							double recoil_ms = std::chrono::duration<double, std::milli>(left_end - left_start).count();

							double extra = 38.0 * (screen_height / screen_height) * (recoil_ms / 1000.0);

							auto number1 = 0.0;
							auto number = settings.snapValue;
							switch (number) {
							case 1:
								number1 = 38;
								extra = 38.0 * (screen_height / screen_height) * (recoil_ms / 1000.0);
								break;
							case 11:
								number1 = 34;
								extra = 34.0 * (screen_height / screen_height) * (recoil_ms / 1000.0);
								break;
							case 28:
								number1 = 15;
								extra = 15.0 * (screen_height / screen_height) * (recoil_ms / 1000.0);
								break;
							}
							if (!left_down) {
								extra = 0;
							}
							else if (extra > number1) {
								extra = number1;
							}
							double v_x = double(aim_x) * sensitivity_x * settings.smoothing;
							double v_y = double(aim_y) * sensitivity_y * settings.smoothing;
							if (GetAsyncKeyState(VK_LBUTTON) && settings.recoil_key.isDown() && settings.recoil) {
								v_y = double(aim_y + extra) * sensitivity_y * settings.smoothing;
							}
							if (fabs(v_x) < 1.0) {
								v_x = v_x > 0 ? 1.05 : -1.05;
							}
							if (fabs(v_y) < 1.0) {
								v_y = v_y > 0 ? 1.05 : -1.05;
							}
							mouse_move_rel(v_x, v_y);
							Sleep(10);
						}
					}
				}
			}
		}
	}
}