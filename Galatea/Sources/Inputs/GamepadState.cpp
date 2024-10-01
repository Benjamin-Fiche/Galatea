#include <Libraries/GLFW/glfw3.h>

#include "Inputs/GamepadState.h"
#include "Inputs/GamepadAxes.h"

using namespace Galatea;

#pragma region Constructors/Destructors

GamepadState::GamepadState(unsigned int _gamepadID) noexcept
	: isConnected{ glfwJoystickPresent(_gamepadID) && glfwJoystickIsGamepad(_gamepadID) }, gamepadID{ _gamepadID }, buttons{}, axes{}
{
	for (unsigned int i = 0; i < 15; ++i)
		buttons[i] = EInputState::UP;
}

#pragma endregion

#pragma region Methods

void GamepadState::Update() noexcept
{
	GLFWgamepadstate	state;
	if (!glfwGetGamepadState(gamepadID, &state))
		return;

	for (int i = 0; i < 15; ++i)
	{
		if (state.buttons[i] == GLFW_PRESS)
		{
			if (buttons[i] == EInputState::UP)
				buttons[i] = EInputState::PRESSED;
			else if (buttons[i] == EInputState::PRESSED)
				buttons[i] = EInputState::DOWN;
		}
		else
		{
			if (buttons[i] == EInputState::DOWN)
				buttons[i] = EInputState::RELEASED;
			else if (buttons[i] == EInputState::RELEASED)
				buttons[i] = EInputState::UP;
		}
	}

	for (int i = 0; i < 6; ++i)
		axes[i] = state.axes[i];

	axes[G_GAMEPAD_AXIS_LEFT_Y] *= -1;
	axes[G_GAMEPAD_AXIS_RIGHT_Y] *= -1;
}

#pragma endregion