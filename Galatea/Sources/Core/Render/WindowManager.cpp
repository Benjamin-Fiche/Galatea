#include <iostream>
#include <Libraries\GLFW\glfw3.h>

#include "Core/Render/WindowManager.h"
#include "Debug/Log.h"

using namespace Galatea;

void	GLFWDebugCallBack(int, const char* msg)
{
	std::cout << msg << '\n';
}

WindowManager::WindowManager() :
	isInit{ false },
	enableCursor{ true },
	window{ nullptr }
{}

WindowManager::~WindowManager()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool WindowManager::Init(float _Version, bool _DebugOpenGL) noexcept
{
	glfwSetErrorCallback(GLFWDebugCallBack);

	if (!glfwInit())
	{
		LogError("Error Init GLFW\n");
		return false;
	}

	if (_Version)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, (int)_Version);						// Major OpenGL version (4.)
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, (int)((_Version - (int)_Version) * 10));	// Minor OpenGL version (.5)
	}
	if (_DebugOpenGL)
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);							// Active OpenGL Debug

	//glfwWindowHint(GLFW_SAMPLES, 16); // TODO Check optimization (enable antialiasing)

	isInit = true;

	return isInit;
}

bool WindowManager::OpenWindow(const char* _windowName, int _width, int _height) noexcept
{
	if (isInit && !(window = glfwCreateWindow(_width, _height, _windowName, nullptr, nullptr)))
	{
		LogError("Error Create Window\n");
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	return true;
}

void WindowManager::SetResizeCallback(void(*_func)(GLFWwindow*, int, int)) noexcept
{
	glfwSetWindowSizeCallback(window, _func);
}

void WindowManager::SetVerticalSynchronization(bool active) noexcept
{
	if (GetInstance().window)
		glfwSwapInterval(active);				// Swap Buffer (vertical synchronization), FPS = Screen Max / param, 0 = Unlimited FPS
}

void WindowManager::GetWindowSize(int& width, int& height) noexcept
{
	glfwGetWindowSize(GetInstance().window, &width, &height);
}

void WindowManager::SetWindowSize(int width, int height) noexcept
{
	glfwSetWindowSize(GetInstance().window, width, height);
}

bool WindowManager::GetCursorEnabled() noexcept
{
	return GetInstance().enableCursor;
}

void WindowManager::SetCursor(bool _value) noexcept
{
	if (_value)
		glfwSetInputMode(GetInstance().window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	else
		glfwSetInputMode(GetInstance().window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void WindowManager::SetCursorPos(const Vec2& _pos) noexcept
{
	glfwSetCursorPos(GetInstance().window, _pos.x, _pos.y);
}

void WindowManager::Update() noexcept
{
	glfwSwapBuffers(window);
}

float WindowManager::GetTime() const noexcept
{
	return static_cast<float>(glfwGetTime());
}

void WindowManager::CloseWindow() noexcept
{
	if (window)
		glfwSetWindowShouldClose(window, GLFW_TRUE); 
}

bool WindowManager::IsWindowRunning() const noexcept
{ 
	return !glfwWindowShouldClose(window); 
}