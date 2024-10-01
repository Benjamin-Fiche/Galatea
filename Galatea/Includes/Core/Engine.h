#pragma once

#include <functional>

#include "DLL.h"

struct ImGuiContext;

namespace Galatea
{
	struct Vec2;

	class GALATEA_API Engine
	{
	private:
		//renderer
		class WindowManager&		windowManager;
		class SceneManager&			sceneManager;
		class Renderer*				renderer;

		bool						isRunning;
		bool						isEditor;
		bool						displayFramebuffer;

		static float				numberFixUpdatePerSeconds;

	public:
		Engine()			noexcept;
		~Engine()			noexcept;

		bool			GetIsRunning()	const	noexcept { return isRunning; };

		bool			Init(bool _initForEditor = false)													noexcept;
		void			Update()																			noexcept;
		void			MainLoop()																			noexcept;
		void			UpdateInEditor(ImGuiContext* _context, const std::function<void()>& _editorUpdate)	noexcept;
		void			Start()																				noexcept;
		void			Restart()																			noexcept;
		void			Stop()																				noexcept;
		void			LoadScene()																			noexcept;
		void			SaveScene()																			noexcept;

		static void		ChangeNumberFixUpdatePerSeconds(unsigned int value)	noexcept;
		static float	GetNumberFixUpdatePerSeconds()						noexcept;
	};
}

