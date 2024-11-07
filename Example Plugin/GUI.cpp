#include "GUI.h"
#include "framework.h"
#include <filesystem>

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_win32.h"

#include "TygerFrameworkAPI.hpp"

//WndProc to be able to interact with imgui or block any WndProc from interacting with the Ty window
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool GUI::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_KEYDOWN) {
        //Just keybinds to test and show toggling the blocked input state
        switch (wParam) {
        // /?
        case VK_OEM_2: {
            //Always sets NoMouseInput to be enabled but keeping all other flags enabled
            API::SetTyInputFlag(NoMouseInput, true);
            break;
        }
        // [{
        case VK_OEM_4: {
            auto inputState = API::GetTyInputState();
            //XOR auto toggles it on and off
            API::SetTyInputState(inputState ^ NoMouseInput);
            break;
        }
        // ]}
        case VK_OEM_6: {
            //Sets the entire state to only have NoKeyboardInput enable
            API::SetTyInputState(NoKeyboardInput);
            break;
        }
        // \|
        case VK_OEM_5: {
            auto inputState = API::GetTyInputState();
            //Toggle both at the same time
            //If any are set this will be true
            if (inputState)
                API::SetTyInputState(None);
            else
                API::SetTyInputState(NoKeyboardInput | NoMouseClickInput | NoMouseCameraInput);
            break;
        }
        // '"
        case VK_OEM_7: {
            auto inputState = API::GetTyInputState();
            //XOR auto toggles it on and off. Shows the cursor and unlocks it
            API::SetTyInputState(inputState ^ TyShowCursor);
            break;
        }
        }
    }
    if (API::DrawingGUI())
        if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
            return true;
    return false;
}

void GUI::Initialize() {

    //Setup ImGui Context
    ImGui::CreateContext();

    //Set the font to be the same as TygerFramework
    API::SetImGuiFont(ImGui::GetIO().Fonts);

    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    if (API::GetTyWindowHandle() == 0) {
        API::LogPluginMessage("Error");
        return;
    }
    //Setup backend
    ImGui_ImplWin32_InitForOpenGL(API::GetTyWindowHandle());
    ImGui_ImplOpenGL3_Init();

    API::LogPluginMessage("Initialized ImGui");
    GUI::init = true;
}

//ImGui Drawing code
void GUI::DrawUI() {
    if (!GUI::init)
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

//To block clicks from the game when the window is focused
bool GUI::ImGuiWantCaptureMouse() {
    //WantCaptureMouse works better than window focus
    //Minimal evaluation used here, if the GUI isn't initialized it won't check the want capture mouse from ImGui
    //This is to avoid a crash if adding the WndProc event in the TygerFrameworkPluginInitialize if the UI is closed by default
    return GUI::init && ImGui::GetIO().WantCaptureMouse;
}

void GUI::SetFrameworkImGuiElements()
{
    namespace fs = std::filesystem;
    //Setting the values for GUI to render on the TygerFramework window
    //Only a few basic elements avaliable as its mainly intended to just be for adding basic stuff to the TygerFramework window 
    std::vector<TygerFrameworkImGuiParam> TygerFrameworkImguiElements = { {CollapsingHeader, "Example Plugin"},
                                                                          {Text, "Files in Ty Directory Example"},
                                                                          {SameLine},
                                                                          {Text, "(?)"},
                                                                          {SetTooltip, "Just an Example of Iterating and Adding Elements"},
                                                                          {TreePush, "Example Plugin"} };
    //Looping through elements and adding them
    for (auto&& entry : fs::directory_iterator{ fs::current_path() }) {
        auto&& path = entry.path();
        TygerFrameworkImguiElements.push_back({ Text, path.filename().string()});
    }

    TygerFrameworkImguiElements.push_back({ TreePop });

    TygerFrameworkImguiElements.push_back({ CollapsingHeader, "Example Plugin Header 2" });
    TygerFrameworkImguiElements.push_back({ TextWrapped, "Example How to Use 2 Collapsing Headers" });

    API::SetTygerFrameworkImGuiElements(TygerFrameworkImguiElements);

    API::LogPluginMessage("Set TygerFramework ImGui Functions");
}
