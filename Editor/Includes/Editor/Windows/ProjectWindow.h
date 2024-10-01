#pragma once

#include "ImGui/imgui.h"
#include "ImGui/imfilebrowser.h"
#include "Editor/EditorWindow.h"

namespace Galatea
{
	class ProjectWindow : public EditorWindow
	{
	private:
		ImGui::FileBrowser fileDialog;
	public:
		#pragma region Constructors/Destructor

		ProjectWindow()							noexcept = default;
		ProjectWindow(const ProjectWindow& _w)	noexcept = default;
		ProjectWindow(ProjectWindow&& _w)		noexcept = default;
		ProjectWindow(const char* _name)		noexcept;
		ProjectWindow(const std::string& _name)	noexcept;
		ProjectWindow(std::string&& _name)		noexcept;
		~ProjectWindow()						noexcept = default;

		#pragma endregion

		#pragma region Methods

		void Update()	noexcept override;

		#pragma endregion
	};
}