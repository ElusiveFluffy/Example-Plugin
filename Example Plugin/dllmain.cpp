// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "API.hpp"
#include <fstream>

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

    API::Get()->LogPluginMessage("Hello World From Example Plugin!");
    API::Get()->LogPluginMessage("Plugin Received Ty " + std::to_string(param->functions->WhichTyGame()) + " as the Current Game");
    API::Get()->LogPluginMessage("Warning Test", Warning);
    API::Get()->LogPluginMessage("Error Test", Error);
    return true;
}

