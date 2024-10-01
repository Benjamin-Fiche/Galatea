#include <iostream>
#include "Libraries/GL/glew.h"
#include "Libraries/GLFW/glfw3.h"
#include "ImGUI/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"

#include <Debug/Log.h>
#include <Core/Render/WindowManager.h>
#include <Core/ResourcesManager.h>
#include <Core/Scene.h>
#include <Inputs/InputManager.h>
#include <Inputs/Keys.h>
#include <Sound/SoundManager.h>

#include "Editor/Editor.h"
#include "Editor/EditorWindow.h"
#include "Editor/Windows/SceneWindow.h"
#include "Editor/Windows/GameWindow.h"
#include "Editor/Windows/ConsoleWindow.h"
#include "Editor/Windows/InspectorWindow.h"
#include "Editor/Windows/HierarchyWindow.h"
#include "Editor/Windows/ProjectWindow.h"

using namespace Galatea;

#pragma region Defines

#define HIERARCHY_WINDOW	0
#define INSPECTOR_WINDOW	1
#define SCENE_WINDOW		2
#define GAME_WINDOW			3
#define PROJECT_WINDOW		4
#define CONSOLE_wiNDOW		5

#pragma endregion

#pragma region Variables

int				Editor::windowPosX		{ 0 };
int				Editor::windowPosY		{ 0 };
unsigned int	Editor::windowWidth		{ 1024 };
unsigned int	Editor::windowHeight	{ 800 };

#pragma endregion

#pragma region Constructors/Destructor

Editor::Editor() noexcept
	: io{ ImGui::GetIO() }, dockspaceFlags{}, mainViewport{ nullptr }, engine{}, showDemoWindow{ false }, isPlaying{ false }, isPaused { false }
{}

Editor::~Editor() noexcept
{
}

#pragma endregion

#pragma region Methods

bool Editor::InitImGui() noexcept
{
	ImGui::StyleColorsDark();

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
	io.ConfigWindowsMoveFromTitleBarOnly = true;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	dockspaceFlags =	ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
						ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
						ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiDockNodeFlags_PassthruCentralNode;

	mainViewport = ImGui::GetMainViewport();

	return true;
}

bool Editor::InitWindows() noexcept
{
	//editorWindows.push_back(new MainWindow
    editorWindows.push_back(new HierarchyWindow("Hierarchy"));
    editorWindows.push_back(new InspectorWindow("Inspector"));
    editorWindows.push_back(new SceneWindow("Scene"));
    editorWindows.push_back(new GameWindow("Game"));
    editorWindows.push_back(new ProjectWindow("Project"));
    editorWindows.push_back(new ConsoleWindow("Console"));

	return true;
}

bool Editor::Init() noexcept
{
	engine.Init(true);
	InitImGui();
	InitWindows();
	playButtonsTexture = ResourcesManager::CreateTextureResource("Resources/Textures/pause-resume.png");
	Scene::UpdateCameraInEditor();

	return true;
}

void Editor::RenderPauseResumeButtons() noexcept
{
	ImGui::PushStyleColor(ImGuiCol_Button, ImGui::GetStyle().Colors[ImGuiCol_WindowBg]);
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 26.f / 255.f, 91.f / 255.f, 191.f / 255.f, 1 });
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 26.f / 255.f, 53.f / 255.f, 191.f / 255.f, 1 });

	unsigned int	textureID{ ResourcesManager::GetResource<Texture>(playButtonsTexture)->GetTextureID() };

	ImGui::SameLine(ImGui::GetWindowSize().x / 2 - 16);
	ImGui::PushID(0);
	if (ImGui::ImageButton((ImTextureID)textureID, ImVec2(32, 32), ImVec2(0.6f, 0.2f), ImVec2(0.8f, 0.7f), 4))
	{
		isPlaying = !isPlaying;
		if (isPlaying)
		{
			InspectorWindow::gameObject = nullptr;
			engine.SaveScene();
			engine.LoadScene();
			engine.Start();
			isPaused = false;
		}
		else
		{
			InspectorWindow::gameObject = nullptr;
			engine.Stop();
			engine.LoadScene();
			isPaused = false;
		}
	}
	ImGui::PopID();

	ImGui::SameLine();
	ImGui::PushID(1);
	if (ImGui::ImageButton((ImTextureID)textureID, ImVec2(32, 32), ImVec2(0.2f, 0.2f), ImVec2(0.4f, 0.7f), 4))
	{
		PauseUnpause();
	}
	ImGui::PopID();

	ImGui::PopStyleColor(3);
}

void Editor::RenderDockspace() noexcept
{
	if (ImGui::Begin("DockSpace", nullptr, dockspaceFlags))
	{
		/* TODO: remove */
		if (showDemoWindow)
			ImGui::ShowDemoWindow(&showDemoWindow);

		RenderPauseResumeButtons();

		ImGui::DockSpace(ImGui::GetID("DockSpace"), ImVec2(0, 0), ImGuiDockNodeFlags_PassthruCentralNode);
		ImGui::End();
	}
}

void Editor::RenderMainMenuBar() noexcept
{
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Create Scene", "Ctrl + N")) {}
			if (ImGui::MenuItem("Open Scene", "Ctrl + O")) {}
			ImGui::Separator();
			if (ImGui::MenuItem("Save", "Ctrl + S")) 
			{
				engine.SaveScene();
			}
			if (ImGui::MenuItem("Save As", "Ctrl + Shift + S")) {}
			ImGui::Separator();
			if (ImGui::MenuItem("Exit", "Alt + F4"))
			{ 
				WindowManager::GetInstance().CloseWindow();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "Ctrl + Z")) {}
			if (ImGui::MenuItem("Redo", "Ctrl + Y")) {}
			ImGui::Separator();
			if (ImGui::MenuItem("Copy", "Ctrl + C")) {}
			if (ImGui::MenuItem("Paste", "Ctrl + V")) {}
			if (ImGui::MenuItem("Cut", "Ctrl + X")) {}
			ImGui::Separator();
			if (ImGui::MenuItem("Duplicate", "Ctrl + D")) {}
			if (ImGui::MenuItem("Rename", "F2")) {}
			if (ImGui::MenuItem("Delete", "Delete")) {}
			ImGui::Separator();
			if (ImGui::MenuItem("Preferences")) {}
			if (ImGui::MenuItem("Project Settings")) {}
			if (ImGui::MenuItem("Shortcuts")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Windows"))
		{
			for (int i = 0; i < 6; ++i)
				ImGui::MenuItem(editorWindows[i]->name.c_str(), "", &editorWindows[i]->isOpen);

			ImGui::MenuItem("Imgui demo", "", &showDemoWindow);

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void Editor::UpdateWindows() noexcept
{
	for (std::vector<EditorWindow*>::iterator it = editorWindows.begin(); it != editorWindows.end(); ++it)
		(*it)->Update();
}

void Editor::Update() noexcept
{
	ImGui::SetNextWindowPos(mainViewport->Pos);
	ImGui::SetNextWindowSize(mainViewport->Size);
	ImGui::SetNextWindowViewport(mainViewport->ID);

	RenderDockspace();
	RenderMainMenuBar();
	UpdateWindows();

	if (isPlaying && !isPaused)
		engine.Update();

	if (InputManager::GetInstance()->GetKeyPressed(G_KEY_F5))
		PlayStop();
	if (InputManager::GetInstance()->GetKeyPressed(G_KEY_F6))
		PauseUnpause();
}

void Editor::Start() noexcept
{
	engine.UpdateInEditor(ImGui::GetCurrentContext(), [this]() {Update(); });
}

void Editor::PauseUnpause() noexcept
{
	if (!isPlaying)
		return;

	isPaused = !isPaused;
	if (!isPaused)
		engine.Start();
	else
		engine.Stop();
}

void Editor::PlayStop() noexcept
{
	isPlaying = !isPlaying;

	if (isPlaying)
	{
		InspectorWindow::gameObject = nullptr;
		engine.SaveScene();
		engine.LoadScene();
		engine.Start();
		isPaused = false;
	}
	//else if (isPaused)
	//{
	//	InspectorWindow::gameObject = nullptr;
	//	engine.LoadScene();
	//	engine.Start();
	//	isPaused = false;
	//}
	else
	{
		InspectorWindow::gameObject = nullptr;
		engine.Stop();
		engine.LoadScene();
		isPaused = false;
	}
}

void Editor::WindowPosCallback(GLFWwindow* _window, int _x, int _y) noexcept
{
	windowPosX = _x;
	windowPosY = _y;
}

void Editor::WindowSizeCallback(GLFWwindow* _window, int _width, int _height) noexcept
{
	windowWidth = _width;
	windowHeight = _height;
}

#pragma endregion