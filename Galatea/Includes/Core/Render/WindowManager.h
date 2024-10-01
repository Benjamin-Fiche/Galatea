#pragma once

#include "DLL.h"
#include "Maths/Vec2.h"

struct GLFWwindow;

namespace Galatea
{
	class WindowManager final
	{
		friend class InputManager;
		friend class Engine;

	private:
		bool				isInit;
		bool				enableCursor;
		GLFWwindow*			window;

		WindowManager();

	public:
		GALATEA_API ~WindowManager();

		GALATEA_API static WindowManager&	GetInstance() noexcept
		{
			static WindowManager instance;
			return instance;
		}

		GALATEA_API WindowManager&			SetWindow(GLFWwindow* _window) noexcept
		{
			if (_window != nullptr)
			{
				window = _window;
				isInit = true;
			}
			return *this;
		}

		GALATEA_API bool		GetIsInit() const noexcept { return isInit; };

		#if defined(GALATEADLL_EXPORTS) || defined(_DEBUGEXE)
		bool					Init(float _version = 3.3f, bool _debugOpenGL = false)									noexcept;
		bool					OpenWindow(const char* _windowName = "Window", int _width = 1024, int _height = 800)	noexcept;
		
		void					SetResizeCallback(void(*_func)(GLFWwindow*, int, int))									noexcept;
		#endif

		GALATEA_API static void	SetVerticalSynchronization(bool active)													noexcept;
		GALATEA_API static void	GetWindowSize(int& _width, int& _height)												noexcept;
		GALATEA_API static void	SetWindowSize(int _width, int _height)													noexcept;
		GALATEA_API static bool	GetCursorEnabled()																		noexcept;
		GALATEA_API static void	SetCursor(bool _value)																	noexcept;
		GALATEA_API static void	SetCursorPos(const Vec2& _pos)															noexcept;
		GALATEA_API void		CloseWindow()																			noexcept;

		#if defined(GALATEADLL_EXPORTS) || defined(_DEBUGEXE)
		void					Update()																				noexcept;
		float					GetTime()																		const	noexcept;
		#endif
		GALATEA_API bool		IsWindowRunning()																const	noexcept;
	};
}