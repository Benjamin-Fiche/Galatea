#include "ImGui/imgui.h"
#include <Core/Scene.h>
#include <Debug/Log.h>
#include <Maths/Vec2.h>

#include "Editor/Windows/GameWindow.h"

using namespace Galatea;

#pragma region Constructors/Destructor

GameWindow::GameWindow(const char* _name) noexcept
	: EditorWindow{ _name }
{}

GameWindow::GameWindow(const std::string& _name) noexcept
	: EditorWindow{ _name }
{}

GameWindow::GameWindow(std::string&& _name) noexcept
	: EditorWindow{ _name }
{}

#pragma endregion

#pragma region Properties

Vec2 GameWindow::GetWindowSize() const noexcept
{
	return { size.x, size.y };
}

#pragma endregion

#pragma region Methods

void GameWindow::Update() noexcept
{
	if (isOpen)
	{
		ImGui::Begin("Game", &isOpen, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
		
		ImVec2	newSize = ImGui::GetWindowSize();
		if (newSize.x != size.x || newSize.y != size.y)
		{           
			size = newSize;
			Scene::ResizeScenes(size.x, size.y);
		}
	
		ImGui::Image((ImTextureID)Scene::GetCurrentScene()->GetFinalFramebuffer()->GetColorBuffer(), size, { 0, 1 }, { 1, 0 });

		ImGui::End();
	}
}

#pragma endregion