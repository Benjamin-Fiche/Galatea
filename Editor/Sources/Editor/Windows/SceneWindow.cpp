#include "ImGui/imgui.h"
#include <Core/Scene.h>
#include <Core/Render/WindowManager.h>

#include "Editor/Windows/SceneWindow.h"

using namespace Galatea;

#pragma region Constructors/Destructor

SceneWindow::SceneWindow(const char* _name) noexcept
	: EditorWindow{ _name }
{}

SceneWindow::SceneWindow(const std::string& _name) noexcept
	: EditorWindow{ _name }
{}

SceneWindow::SceneWindow(std::string&& _name) noexcept
	: EditorWindow{ _name }
{}

#pragma endregion

#pragma region Methods

void SceneWindow::Update() noexcept
{
	if (isOpen)
	{
		ImGui::Begin(" Scene ", &isOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

		ImVec2	newSize = ImGui::GetWindowSize();
		if (newSize.x != size.x || newSize.y != size.y)
		{
			size = newSize;
			Scene::ResizeCameraEditor(size.x, size.y);
		}
			
		if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(1))
			ImGui::SetWindowFocus();

		if (ImGui::IsWindowFocused() && ImGui::IsMouseDown(1))
		{
			WindowManager::SetCursor(false);
			Scene::UpdateCameraInEditor();
		}
		else if (ImGui::IsWindowFocused() && ImGui::IsMouseReleased(1))
			WindowManager::SetCursor(true);

		ImGui::Image((ImTextureID)Scene::GetCurrentScene()->GetSceneFramebuffer()->GetColorBuffer(), size, { 0, 1 }, { 1, 0 });

		ImGui::End();
	}
}

#pragma endregion