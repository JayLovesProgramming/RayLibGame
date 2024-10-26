#include "imgui_manager.h"

void InitImGui()
{
    std::cout << "Initialized ImGui" << std::endl;
    rlImGuiSetup(true);
};

bool open = true;

void DrawImGui()
{
    std::cout << "Drawing Imgui" << std::endl;
    rlImGuiBegin();
    ImGui::ShowDemoWindow(&open);
    rlImGuiEnd();
};

void UnloadImGui()
{
    rlImGuiShutdown();
}
