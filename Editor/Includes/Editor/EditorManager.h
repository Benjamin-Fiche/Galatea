#pragma once

#include <vector>
#include <iostream>

#include "Libraries/GL/glew.h"
#include "Libraries/GLFW/glfw3.h"
#include "ImGui/imgui.h"

#include "Editor/EditorWindow.h"

namespace Galatea
{
	class EditorManager
	{
	private:
		#pragma region Variables

		GLFWwindow*				window;
		ImGuiIO&				io;
		//std::vector<EditorWindow*>	editorWindows;

		static int				windowPosX;
		static int				windowPosY;
		static unsigned int		windowWidth;
		static unsigned int		windowHeight;

		#pragma endregion

		#pragma region Methods

		bool	InitGLFW(float _version)												noexcept;
		bool	InitImGuiconst(const char* _glslVersion)								noexcept;
		bool	InitWindows()															noexcept;

		static void	WindowPosCallback(GLFWwindow* _window, int _w, int _y)				noexcept;
		static void	WindowSizeCallback(GLFWwindow* _window, int _width, int _height)	noexcept;

		#pragma endregion

	public:
		#pragma region Consturctors/Destructor

		EditorManager()		noexcept;
		~EditorManager()	noexcept;

		#pragma endregion

		#pragma region Methods

		bool	Init(float _version, const char* _glslVersion)			noexcept;
		void	MainLoop()												noexcept;

		#pragma endregion
	};
}
