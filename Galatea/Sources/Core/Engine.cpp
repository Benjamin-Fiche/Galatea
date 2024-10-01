#include <iostream>
#include "Libraries/ImGui/imgui.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

#include "Core/Render/WindowManager.h"
#include "Core/Render/Renderer.h"
#include "Core/Engine.h"
#include "Core/Render/RHI.h"
#include "Maths/Vec4.h"
#include "Core/SceneManager.h"
#include "Core/SerializationManager.h"
#include "Core/Time.h"
#include "Core/ResourcesManager.h"
#include "Inputs/InputManager.h"
#include "Inputs/Keys.h"
#include "Core/Scene.h"
#include "Maths/Vec2.h"
#include "Sound/SoundManager.h"
#include "Sound/Sound.h"	/* TODO: remove */

using namespace Galatea;

float Engine::numberFixUpdatePerSeconds = 0;

Engine::Engine()	noexcept :
	windowManager{ WindowManager::GetInstance() },
	sceneManager{ SceneManager::GetInstance() },
	renderer{ nullptr },
	isRunning{ false },
	isEditor{ false },
	displayFramebuffer{ false }
{
	numberFixUpdatePerSeconds = 1.f / 120.f;
	//Init nullptr window/renderer/sceneMgr
}

Engine::~Engine()	noexcept
{
	//destroy window/renderer
	if (renderer != nullptr)
		delete renderer;
	
	if (isEditor)
		ImGui::DestroyContext();
	
	sceneManager.Destroy();

	delete InputManager::GetInstance();
	delete SoundManager::GetInstance();
	delete Log::GetInstance();
}


bool Engine::Init(bool _initForEditor) noexcept
{
	if (!windowManager.Init(4.5, true) || !windowManager.OpenWindow("Galatea") || !RHI::Init() || !SoundManager::GetInstance()->Init())
		return false;

	RHI::EnableDebug();

	windowManager.SetResizeCallback([](GLFWwindow*, int _width, int _height) { Scene::ResizeScenes(_width, _height); }); /// TODO : Link resize with real function
	windowManager.SetVerticalSynchronization(true);

	InputManager::GetInstance()->Init();
	ResourcesManager::Init();
	Time::Init();
	SerializationManager::LoadScene(sceneManager);
	sceneManager.Init();
	renderer = new Renderer();

	isEditor = _initForEditor;
	displayFramebuffer = !_initForEditor;
	LogValue(displayFramebuffer);

	if (!_initForEditor)
	{
		// TODO: (debug only) remove 
		InputAction	escape{ "Escape" };
		escape.AddPattern(EDeviceType::KEYBOARD, EInputState::PRESSED, G_KEY_ESCAPE);
		escape.AddCallback(&Engine::Stop, *this);
		InputManager::GetInstance()->AddAction(escape);
	}
	

	return true;
}

void Engine::ChangeNumberFixUpdatePerSeconds(unsigned int value) noexcept
{
	numberFixUpdatePerSeconds = 1.f / (float)value;
}

void Engine::Update() noexcept
{
	Time::Update();

	sceneManager.Update();

	if (Time::instance.currentTime - Time::instance.previousTimeFixUpdate >= numberFixUpdatePerSeconds)
	{
		sceneManager.FixedUpdate();
		Time::instance.fixUpdatedeltaTime = Time::instance.currentTime - Time::instance.previousTimeFixUpdate;
		Time::instance.previousTimeFixUpdate = Time::instance.currentTime;
	}

	#if _DEBUG
	if (Time::instance.secondTime >= 1)
	{
		std::cout << "FPS : " << Time::instance.frameCount << '\n';

		Time::instance.frameCount = 0;
		Time::instance.secondTime = 0.f;
	}
	#endif

	sceneManager.LateUpdate();

	SoundManager::GetInstance()->Update();

	renderer->RenderScene();
	renderer->DrawScene();
	//windowManager.Update();

}

float Engine::GetNumberFixUpdatePerSeconds() noexcept
{
	return numberFixUpdatePerSeconds;
}


void Engine::MainLoop()	noexcept
{
	Start();
	while (isRunning)
	{
		InputManager::GetInstance()->Update();
		Update();
		windowManager.Update();

		if (!windowManager.IsWindowRunning())
			Stop();
	}

	windowManager.CloseWindow();
}


void Engine::UpdateInEditor(ImGuiContext* _context, const std::function<void()>& _editorUpdate) noexcept
{
	ImGui::SetCurrentContext(_context);
	ImGui_ImplGlfw_InitForOpenGL(windowManager.window, true);
	ImGui_ImplOpenGL3_Init("#version 450");

	while (windowManager.IsWindowRunning())
	{
		if (!isRunning)
			Time::Update();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		if (!isRunning)
			InputManager::GetInstance()->UpdateInEditor();
		else
			InputManager::GetInstance()->Update();

		renderer->RenderScene();
		renderer->RenderCameraEditor();

		if (_editorUpdate != nullptr)
			_editorUpdate();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		windowManager.Update();

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backupCurrentContext{ glfwGetCurrentContext() };
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupCurrentContext);
		}
		
		ImGui::EndFrame();
		
		if (!windowManager.IsWindowRunning())
			Stop();
	}

	windowManager.CloseWindow();
}

void Engine::Start() noexcept
{
	int	width, height;
	windowManager.GetWindowSize(width, height);
	glfwSetCursorPos(windowManager.window, width / 2, height / 2);
	windowManager.SetCursor(false);
	isRunning = true;
	Time::instance.previousTimeFixUpdate = Time::instance.currentTime;
	SoundManager::GetInstance()->PauseAll(false);
	/*Scene::GetCurrentScene()->GetCurrentCamera()->ResetRotation();
	Scene::GetCurrentScene()->GetCameraInEditor().ResetRotation();*/
}

void Engine::Restart() noexcept
{
	isRunning = false;
	
	//SerializationManager::SaveCurrentScene();
	//sceneManager.GetCurrentScene()->Reload();

	isRunning = true;
}

void Engine::Stop() noexcept
{
	windowManager.SetCursor(true);
	isRunning = false;
	SoundManager::GetInstance()->PauseAll(true);
	Time::instance.fixUpdatedeltaTime = 0;
}

void Engine::SaveScene() noexcept
{
	SerializationManager::SaveScene(sceneManager);
}

void Engine::LoadScene() noexcept
{
	//delete renderer;
	sceneManager.Destroy();
	SerializationManager::LoadScene(sceneManager);
	sceneManager.Init();
	//renderer = new Renderer();
}
