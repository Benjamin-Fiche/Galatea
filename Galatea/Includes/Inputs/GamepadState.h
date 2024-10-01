#pragma once

#include "DLL.h"

#include "EInputState.h"
#include "Debug/Log.h"

namespace Galatea
{
	class InputManager;

	class GALATEA_API GamepadState
	{
		friend InputManager;

	private:
		#pragma region Variables

		bool			isConnected;
		unsigned int	gamepadID;
		EInputState		buttons[15];
		float			axes[6];

		#pragma endregion

	public:
		#pragma region Constructors/Destructors

		GamepadState()							noexcept = default;
		GamepadState(const GamepadState& _gs)	noexcept = default;
		GamepadState(GamepadState&& _gs)		noexcept = default;
		GamepadState(unsigned int _gamepadID)	noexcept;
		~GamepadState()							noexcept = default;

		#pragma endregion

		#pragma region Properties

		inline const bool&			GetIsConnected()						const	noexcept;
		inline const unsigned int&	GetGamepadID()							const	noexcept;
		inline const EInputState*	GetButtonsState()						const	noexcept;
		inline EInputState			GetButtonState(unsigned int _button)	const	noexcept;
		inline bool					GetbuttonDown(unsigned int _button)		const	noexcept;
		inline bool					GetButtonUp(unsigned int _button)		const	noexcept;
		inline bool					GetButtonPressed(unsigned int _button)	const	noexcept;
		inline bool					GetButtonReleased(unsigned int _button)	const	noexcept;
		inline const float*			GetAxes()								const	noexcept;
		inline float				GetAxis(unsigned int _axis)				const	noexcept;

		#pragma endregion

		#pragma region Methods

		void	Update()	noexcept;

		#pragma endregion

		#pragma region Operators

		GamepadState&	operator=(const GamepadState& _gs)	noexcept = default;
		GamepadState&	operator=(GamepadState&& _gs)		noexcept = default;

		#pragma endregion
	};

	#include "GamepadState.inl"
}