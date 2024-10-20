#pragma once
#include "framework.h"
class GUI
{
public:
	static inline bool init = false;

	static void Initialize();
	static void DrawUI();
	static bool ImGuiWantCaptureMouse();
	static bool WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	static void SetFrameworkImGuiElements();
};

