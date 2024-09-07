// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "API.hpp"
#include <fstream>
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"

using namespace TygerFrameworkAPI; // For API class
static bool init;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        //How you would specify a custom name (just uncommented of course)
        //API::PluginName = "Example Plugin Custom Name";
    }
    return TRUE;
}

void Initialize() {

    //Setup ImGui Context
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    if (API::GetTyWindowHandle() == 0) {
        API::LogPluginMessage("Error");
        return;
    }
    ImGui_ImplWin32_InitForOpenGL(API::GetTyWindowHandle());
    ImGui_ImplOpenGL3_Init();

    API::LogPluginMessage("Initialized ImGui");
    init = true;
}

void DrawUI() {
    if (!init)
        Initialize();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Example Plugin");
    ImGui::Text("Hello World");

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;
    return false;
}

bool ImGuiHasFocus() {
    return ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow);
}

EXTERN_C bool TygerFrameworkPluginInitialize(TygerFrameworkPluginInitializeParam* param) {
    //Make sure to call this first before any API Functions
    API::Initialize(param);

    param->functions->DrawPluginUI(DrawUI);
    param->functions->PluginImGuiHasFocus((ImGuiHasFocusFunc)ImGuiHasFocus);
    param->functions->PluginWndProc((WndProcFunc)WndProc);

    API::LogPluginMessage("Hello World From Example Plugin!");
    API::LogPluginMessage("Plugin Received Ty " + std::to_string(API::WhichTyGame()) + " as the Current Game");
    API::LogPluginMessage("Warning Test", Warning);
    API::LogPluginMessage("Error Test", Error);
    return true;
}

