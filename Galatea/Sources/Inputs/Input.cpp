#include "Inputs/Input.h"
#include "Inputs/InputManager.h"

using namespace Galatea;

#pragma region Constructors/Destructors

Input::Input(EDeviceType _device, EInputState _state, int _code, unsigned int _gamepadID) noexcept
	: device{ _device }, state{ _state }, code{ _code }, gamepadID{ _gamepadID }
{}

#pragma endregion

#pragma region Methods

bool Input::IsValid() const noexcept
{
	switch (device)
	{
		case EDeviceType::KEYBOARD:
		{
			/* TODO: est ce que c'est rentable de faire ce test ? */
			EInputState currState{ InputManager::GetInstance()->GetKeyState(code) };
			if (state == EInputState::DOWN)
				return currState == EInputState::PRESSED || currState == EInputState::DOWN;
			else if (state == EInputState::UP)
				return currState == EInputState::RELEASED || currState == EInputState::UP;
			else
				return currState == state;
		}
		case EDeviceType::MOUSE:
		{
			EInputState currState{ InputManager::GetInstance()->GetMouseButtonState(code) };
			if (state == EInputState::DOWN)
				return currState == EInputState::PRESSED || currState == EInputState::DOWN;
			else if (state == EInputState::UP)
				return currState == EInputState::RELEASED || currState == EInputState::UP;
			else
				return currState == state;
		}
		case EDeviceType::GAMEPAD:
		{
			EInputState currState{ InputManager::GetInstance()->GetGamepadButtonState(gamepadID, code) };
			if (state == EInputState::DOWN)
				return currState == EInputState::PRESSED || currState == EInputState::DOWN;
			else if (state == EInputState::UP)
				return currState == EInputState::RELEASED || currState == EInputState::UP;
			else
				return currState == state;
		}
		default:
			return false;
	}
}

#pragma endregion