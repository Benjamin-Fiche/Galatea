#include "ImGui/imgui.h"
#include "Editor/Windows/ConsoleWindow.h"

using namespace Galatea;

#pragma region Constructors/Destructor

ConsoleWindow::ConsoleWindow(const char* _name) noexcept
	: EditorWindow{ _name }
{}

ConsoleWindow::ConsoleWindow(const std::string& _name) noexcept
	: EditorWindow{ _name }
{}

ConsoleWindow::ConsoleWindow(std::string&& _name) noexcept
	: EditorWindow{ _name }
{}

#pragma endregion

#pragma region Methods

void ConsoleWindow::Update() noexcept
{
	if (isOpen)
	{
		ImGui::Begin("Console", &isOpen, ImGuiWindowFlags_NoCollapse);

		ImGui::Text("I'm the console");

		ImGui::End();
	}
}

#pragma endregion