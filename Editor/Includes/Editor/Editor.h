#pragma once

#include <vector>

#include "Libraries/GL/glew.h"
#include "Libraries/GLFW/glfw3.h"
#include "ImGui/imgui.h"
#include <Core/Engine.h>

namespace Galatea
{
	class EditorWindow;

	class Editor
	{
	private:
		#pragma region Variables

		ImGuiIO&					io;
		std::vector<EditorWindow*>	editorWindows;
		ImGuiDockNodeFlags			dockspaceFlags;
		ImGuiViewport*				mainViewport;
		Engine						engine;
		bool						showDemoWindow;
		const char*					playButtonsTexture;
		bool						isPlaying;
		bool						isPaused;


		#pragma endregion

		#pragma region Methods

		bool		InitImGui()															noexcept;
		bool		InitWindows()														noexcept;
		void		RenderPauseResumeButtons()											noexcept;
		void		RenderDockspace()													noexcept;
		void		RenderMainMenuBar()													noexcept;
		void		UpdateWindows()														noexcept;
		void		Update()															noexcept;
		void		PauseUnpause()														noexcept;
		void		PlayStop()															noexcept;

		static void	WindowPosCallback(GLFWwindow* _window, int _x, int _y)				noexcept;
		static void	WindowSizeCallback(GLFWwindow* _window, int _width, int _height)	noexcept;

		#pragma endregion

	public:
		#pragma region Variables

		/* TODO: remove */
		static int			windowPosX;		// TODO: better than static function ?
		static int			windowPosY;		// TODO: usefull ?
		static unsigned int	windowWidth;
		static unsigned int	windowHeight;

		#pragma endregion

		#pragma region Constructors/Destructor

		Editor()	noexcept;
		~Editor()	noexcept;

		#pragma endregion

		#pragma region Properties
		#pragma endregion

		#pragma region Methods

		bool	Init()	noexcept;
		void	Start()	noexcept;

		#pragma endregion

		#pragma region Operators
		#pragma endregion
	};
}