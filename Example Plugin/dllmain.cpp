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

//Ticks before the game does
void TickBeforeGame(float deltaSeconds) {
    //Tick functionality here
}

//Recommended so your plugin doesn't get loaded with a loader version lower than the API needs, causing a crash
EXTERN_C void TygerFrameworkPluginRequiredVersion(TygerFrameworkPluginVersion* version) {
    //Specifiy the version number defined in the API
    version->Major = TygerFrameworkPluginVersion_Major;
    version->Minor = TygerFrameworkPluginVersion_Minor;
    version->Patch = TygerFrameworkPluginVersion_Patch;

    //Optional if you only want the plugin to run for a specific game //Optional (If the plugin is compatible with 2 or more games write it out like 12 for Ty 1 and 2. 13 for Ty 1, and 3. Etc. Leave unchanged for any game)
    //version->GameNumber = 1;
}

EXTERN_C bool TygerFrameworkPluginInitialize(TygerFrameworkPluginInitializeParam* param) {
    //Make sure to call this first before any API Functions
    API::Initialize(param);

    //Example of using the error message on init
    //if (Error Condition) {
    //    param->initErrorMessage = "Input what is wrong here";
    //    return false;
    //}

    //Subcribe functions to TygerFramework events
    API::AddDrawPluginUI(GUI::DrawUI);
    //Make sure to cast this, otherwise TygerFramework won't get the return value
    API::AddPluginImGuiHasFocus((ImGuiHasFocusFunc)GUI::ImGuiHasFocus);

    API::AddTickBeforeGame(TickBeforeGame);

    //Set the inital elements used in the TygerFramework window
    GUI::SetFrameworkImGuiElements();

    //Example log messages
    API::LogPluginMessage("Hello World From Example Plugin!");
    API::LogPluginMessage("Plugin Received Ty " + std::to_string(API::WhichTyGame()) + " as the Current Game");
    API::LogPluginMessage("Warning Test", Warning);
    API::LogPluginMessage("Error Test", Error);
    return true;
}

