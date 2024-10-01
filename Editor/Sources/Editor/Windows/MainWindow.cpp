#include "Editor/Windows/MainWindow.h"
#include "ImGui\imgui.h"

using namespace Galatea;

void MainWindow::Update(const int _windowPosX, const int _windowPosY,
						const unsigned int _windowWidth, const unsigned int _windowHeight) noexcept
{
	ImGui::Begin("Main Window", 0,	ImGuiWindowFlags_NoDecoration |
									ImGuiWindowFlags_NoMove	|
									ImGuiWindowFlags_NoBringToFrontOnFocus);
	
	bool show = true;
	ImGui::ShowDemoWindow(&show);

	/*ImGui::SetWindowPos(ImVec2(_windowPosX, _windowPosY), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(_windowWidth, _windowHeight), ImGuiCond_Always);*/

	ImGui::Text("Hello I'm the main window !");

	ImGui::End();
}