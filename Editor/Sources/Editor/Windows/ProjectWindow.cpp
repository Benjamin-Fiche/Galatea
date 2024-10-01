#include "Editor/Windows/ProjectWindow.h"

#include <iostream>
#include <filesystem>
#include <functional>

using namespace Galatea;

#pragma region Constructors/Destructor

ProjectWindow::ProjectWindow(const char* _name) noexcept
	: EditorWindow{ _name }
{
	fileDialog.SetTitle("title");
}

ProjectWindow::ProjectWindow(const std::string& _name) noexcept
	: EditorWindow{ _name }
{
	fileDialog.SetTitle("title");
}

ProjectWindow::ProjectWindow(std::string&& _name) noexcept
	: EditorWindow{ _name }
{
	fileDialog.SetTitle("File Browser");
}

#pragma endregion

#pragma region Methods

void ProjectWindow::Update() noexcept
{
	if (isOpen)
	{
		ImGui::Begin("Project", &isOpen, ImGuiWindowFlags_NoCollapse);
	
		fileDialog.Display();

		if (fileDialog.HasSelected())
		{
			// Selected file will be used to add custom component
			std::cout << "Selected filename" << fileDialog.GetSelected().string() << std::endl;
			fileDialog.ClearSelected(); 
		}
		ImGui::End();
	}
}

#pragma endregion