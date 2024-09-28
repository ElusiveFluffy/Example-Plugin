#pragma once
namespace GUI
{
	static bool init;

	void Initialize();
	void DrawUI();
	bool ImGuiWantCaptureMouse();

	void SetFrameworkImGuiElements();
};

