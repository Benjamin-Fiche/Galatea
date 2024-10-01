#pragma once

#pragma region Properties

const bool& GamepadState::GetIsConnected() const noexcept
{
	return isConnected;
}

const unsigned int& GamepadState::GetGamepadID() const noexcept
{
	return gamepadID;
}

const EInputState* GamepadState::GetButtonsState() const noexcept
{
	return buttons;
}

EInputState GamepadState::GetButtonState(unsigned int _button) const noexcept
{
	if (_button < 15)
		return buttons[_button];
	LogWarning("Unknown button");
	return EInputState::UP;
}

bool GamepadState::GetbuttonDown(unsigned int _button) const noexcept
{
	if (_button < 15)
		return buttons[_button] == EInputState::DOWN || buttons[_button] == EInputState::PRESSED;
	LogWarning("Unknown button");
	return false;
}

bool GamepadState::GetButtonUp(unsigned int _button) const noexcept
{
	if (_button < 15)
		return buttons[_button] == EInputState::UP || buttons[_button] == EInputState::RELEASED;
	LogWarning("Unknown button");
	return false;
}

bool GamepadState::GetButtonPressed(unsigned int _button) const noexcept
{
	if (_button < 15)
		return buttons[_button] == EInputState::PRESSED;
	LogWarning("Unknown button");
	return false;
}

bool GamepadState::GetButtonReleased(unsigned int _button) const noexcept
{
	if (_button < 15)
		return buttons[_button] == EInputState::RELEASED;
	LogWarning("Unknown button");
	return false;
}

const float* GamepadState::GetAxes() const noexcept
{
	return axes;
}

float GamepadState::GetAxis(unsigned int _axis) const noexcept
{
	if (_axis < 6)
		return axes[_axis];
	LogWarning("Unknown axis");
	return 0.f;
}

#pragma endregion