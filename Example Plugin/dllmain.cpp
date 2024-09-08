// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "API.hpp"
#include <fstream>
#include "GUI.h"

using namespace TygerFrameworkAPI; // For API class

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

EXTERN_C bool TygerFrameworkPluginInitialize(TygerFrameworkPluginInitializeParam* param) {
    //Make sure to call this first before any API Functions
    API::Initialize(param);

    //Subcribe functions to TygerFramework events
    param->functions->DrawPluginUI(GUI::DrawUI);
    //Make sure to cast this, otherwise TygerFramework won't get the return value
    param->functions->PluginImGuiHasFocus((ImGuiHasFocusFunc)GUI::ImGuiHasFocus);

    //Set the inital elements used in the TygerFramework window
    GUI::SetFrameworkImGuiElements();

    //Example log messages
    API::LogPluginMessage("Hello World From Example Plugin!");
    API::LogPluginMessage("Plugin Received Ty " + std::to_string(API::WhichTyGame()) + " as the Current Game");
    API::LogPluginMessage("Warning Test", Warning);
    API::LogPluginMessage("Error Test", Error);
    return true;
}

