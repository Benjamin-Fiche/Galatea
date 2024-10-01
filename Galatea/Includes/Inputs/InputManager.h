#pragma once

#include <map>
#include <vector>
#include <algorithm>

#include "DLL.h"

#include "Maths/Vec2.h"
#include "Debug/Log.h"
#include "EInputState.h"
#include "GamepadState.h"
#include "InputAction.h"
#include "InputAxis.h"

#define G_GAMEPAD_MAX_COUNT 16

struct GLFWwindow;

namespace Galatea
{
	class GALATEA_API InputManager
	{
	private:
		#pragma region Variables

		static InputManager*				instance;

		GLFWwindow*							window;

		Vector2								lastMousePos;
		Vector2								mousePos;
		std::map<int, EInputState>			keys;
		EInputState							mouseButtons[8];
		std::vector<GamepadState>			gamepadStates;
		float								mouseAxes[4];

		std::map<std::string, InputAction>	actionsMap;		/* TODO: public ? */
		std::map<std::string, InputAxis>	axesMap;		/* TODO: public ? */

		unsigned int						gamepadMaxCount;

		#pragma endregion

		#pragma region Constructors/Destructors

		InputManager()	noexcept;

		#pragma endregion

		#pragma region Methods

		void		InitKeys()																			noexcept;
		void		InitMouse(GLFWwindow* _window)														noexcept;
		void		InitGamepads()																		noexcept;
		void		UpdateKeys()																		noexcept;
		void		UpdateMouseButtons()																noexcept;
		void		UpdateCursor()																		noexcept;

		static void	ScrollCallback(GLFWwindow* _window, double _xOffset, double _yOffset)				noexcept;
		static void	JoystickCallback(int _joystick, int _event)											noexcept;

		#pragma endregion

	public:
		#pragma region Constructors/Destructors

		~InputManager() noexcept = default;

		#pragma endregion
		
		#pragma region Properties

		static inline InputManager*	GetInstance()																	noexcept;

		inline const Vector2&		GetMousePos()															const	noexcept;
		inline EInputState			GetKeyState(int _key)													const	noexcept;
		inline bool					GetKeyUp(int _key)														const	noexcept;
		inline bool					GetKeyDown(int _key)													const	noexcept;
		inline bool					GetKeyPressed(int _key)													const	noexcept;
		inline bool					GetKeyReleased(int _key)												const	noexcept;
		inline EInputState			GetMouseButtonState(int _key)											const	noexcept;
		inline bool					GetMouseButtonUp(int _button)											const	noexcept;
		inline bool					GetMouseButtonDown(int _button)											const	noexcept;
		inline bool					GetMouseButtonPressed(int _button)										const	noexcept;
		inline bool					GetMouseButtonReleased(int _button)										const	noexcept;
		inline GamepadState			GetGamepadState(int _gamepadID)											const	noexcept;
		inline EInputState			GetGamepadButtonState(int _gamepadID, int _button)						const	noexcept;
		inline bool					GetGamepadButtonUp(int _gamepadID, int _button)							const	noexcept;
		inline bool					GetGamepadButtonDown(int _gamepadID, int _button)						const	noexcept;
		inline bool					GetGamepadButtonPressed(int _gamepadID, int _button)					const	noexcept;
		inline bool					GetGamepadButtonReleased(int _gamepadID, int _button)					const	noexcept;
		inline const float*			GetGamepadAxes(int _gamepadID)											const	noexcept;
		inline float				GetGamepadAxis(int _gamepadID, int _axis)								const	noexcept;
		inline const unsigned int&	GetGamepadMaxCount()													const	noexcept;
		inline const float*			GetMouseAxes()															const	noexcept;
		inline float				GetMouseAxis(unsigned int _axis)										const	noexcept;
		inline bool					GetAction(const std::string& _action)									const	noexcept;
		inline float				GetAxis(const std::string& _axis)										const	noexcept;

		inline InputManager*		SetGamepadMaxCount(unsigned int _gamepadMaxCount = G_GAMEPAD_MAX_COUNT)			noexcept;

		#pragma endregion

		#pragma region Methods

		void			Init()											noexcept;
		InputManager*	AddAction()										noexcept;
		InputManager*	AddAction(const InputAction& _action)			noexcept;
		InputManager*	AddAction(InputAction&& _action)				noexcept;
		InputManager*	AddAxis()										noexcept;
		InputManager*	AddAxis(const InputAxis& _axis)					noexcept;
		InputManager*	AddAxis(InputAxis&& _axis)						noexcept;
		bool			IsGamepadConnected(int _gamepadID)		const	noexcept;
		void			Update()										noexcept;
		void			UpdateInEditor()								noexcept;

		#pragma endregion
	};
	
	#include "InputManager.inl"
}