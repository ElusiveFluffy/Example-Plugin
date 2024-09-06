// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "API.hpp"
#include <fstream>
#include "imgui.h"

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
    ImGui::SetCurrentContext((ImGuiContext*)API::GetImGuiContext());
    init = true;
}

void DrawUI() {
    if (!init)
        Initialize();

    if (ImGui::Begin("Example Plugin"));
        ImGui::Text("Hello World");

    ImGui::End();
}

bool WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    return false;
}



EXTERN_C bool TygerFrameworkPluginInitialize(TygerFrameworkPluginInitializeParam* param) {
    //Make sure to call this first before any API Functions
    API::Initialize(param);

    param->functions->DrawPluginUI(DrawUI);
    param->functions->PluginWndProc((WndProcFunc)WndProc);

    API::LogPluginMessage("Hello World From Example Plugin!");
    API::LogPluginMessage("Plugin Received Ty " + std::to_string(API::WhichTyGame()) + " as the Current Game");
    API::LogPluginMessage("Warning Test", Warning);
    API::LogPluginMessage("Error Test", Error);
    return true;
}

