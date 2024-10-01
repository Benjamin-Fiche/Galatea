#pragma once

#pragma region Properties

InputManager* InputManager::GetInstance() noexcept
{
	if (instance == nullptr)
		instance = new InputManager;
	return instance;
}

const Vector2& InputManager::GetMousePos() const noexcept
{
	return mousePos;
}

EInputState InputManager::GetKeyState(int _key) const noexcept
{
	std::map<int, EInputState>::const_iterator	it{ keys.find(_key) };
	if (it != keys.end())
		return it->second;
	LogWarning("Unkown key");
	return EInputState::UNKNOWN;
}

bool InputManager::GetKeyUp(int _key) const noexcept
{
	std::map<int, EInputState>::const_iterator	it{ keys.find(_key) };
	if (it != keys.end())
		return it->second == EInputState::UP || it->second == EInputState::RELEASED;
	LogWarning("Unkown key");
	return false;
}

bool InputManager::GetKeyDown(int _key) const noexcept
{
	std::map<int, EInputState>::const_iterator	it{ keys.find(_key) };
	if (it != keys.end())
		return it->second == EInputState::DOWN || it->second == EInputState::PRESSED;
	LogWarning("Unkown key");
	return false;
}

bool InputManager::GetKeyPressed(int _key) const noexcept
{
	std::map<int, EInputState>::const_iterator	it{ keys.find(_key) };
	if (it != keys.end())
		return it->second == EInputState::PRESSED;
	LogWarning("Unkown key");
	return false;
}

bool InputManager::GetKeyReleased(int _key) const noexcept
{
	std::map<int, EInputState>::const_iterator	it{ keys.find(_key) };
	if (it != keys.end())
		return it->second == EInputState::RELEASED;
	LogWarning("Unkown key");
	return false;
}

EInputState InputManager::GetMouseButtonState(int _button) const noexcept
{
	if (_button < 8)
		return mouseButtons[_button];
	LogWarning("Unkown button");
	return EInputState::UNKNOWN;
}

bool InputManager::GetMouseButtonUp(int _button) const noexcept
{
	if (_button < 8)
		return mouseButtons[_button] == EInputState::UP || mouseButtons[_button] == EInputState::RELEASED;
	LogWarning("Unkown button");
	return false;
}

bool InputManager::GetMouseButtonDown(int _button) const noexcept
{
	if (_button < 8)
		return mouseButtons[_button] == EInputState::DOWN || mouseButtons[_button] == EInputState::PRESSED;
	LogWarning("Unkown button");
	return false;
}

bool InputManager::GetMouseButtonPressed(int _button) const noexcept
{
	if (_button < 8)
		return mouseButtons[_button] == EInputState::PRESSED;
	LogWarning("Unkown button");
	return false;
}

bool InputManager::GetMouseButtonReleased(int _button) const noexcept
{
	if (_button < 8)
		return mouseButtons[_button] == EInputState::RELEASED;
	LogWarning("Unkown button");
	return false;
}

GamepadState InputManager::GetGamepadState(int _gamepadID) const noexcept
{
	if (_gamepadID < gamepadStates.size())
		return gamepadStates[_gamepadID];
	//LogWarning("Unkown gamepad");
	return GamepadState{};
}

EInputState InputManager::GetGamepadButtonState(int _gamepadID, int _button) const noexcept
{
	if (_gamepadID < gamepadStates.size())
		return gamepadStates[_gamepadID].GetButtonState(_button);
	//LogWarning("Unkown gamepad");
	return EInputState::UP;
}

bool InputManager::GetGamepadButtonUp(int _gamepadID, int _button) const noexcept
{
	if (_gamepadID < gamepadStates.size())
		return gamepadStates[_gamepadID].GetButtonUp(_button);
	//LogWarning("Unkown gamepad");
	return false;
}

bool InputManager::GetGamepadButtonDown(int _gamepadID, int _button) const noexcept
{
	if (_gamepadID < gamepadStates.size())
		return gamepadStates[_gamepadID].GetbuttonDown(_button);
	//LogWarning("Unkown gamepad");
	return false;
}

bool InputManager::GetGamepadButtonPressed(int _gamepadID, int _button) const noexcept
{
	if (_gamepadID < gamepadStates.size())
		return gamepadStates[_gamepadID].GetButtonPressed(_button);
	//LogWarning("Unkown gamepad");
	return false;
}

bool InputManager::GetGamepadButtonReleased(int _gamepadID, int _button) const noexcept
{
	if (_gamepadID < gamepadStates.size())
		return gamepadStates[_gamepadID].GetButtonReleased(_button);
	//LogWarning("Unkown gamepad");
	return false;
}

const float* InputManager::GetGamepadAxes(int _gamepadID) const noexcept
{
	if (_gamepadID < gamepadStates.size())
		return gamepadStates[_gamepadID].GetAxes();
	//LogWarning("Unkown gamepad");
	return nullptr;
}

float InputManager::GetGamepadAxis(int _gamepadID, int _axis) const noexcept
{
	if (_gamepadID < gamepadStates.size())
		return gamepadStates[_gamepadID].GetAxis(_axis);
	//LogWarning("Unkown gamepad");
	return 0.f;
}

const unsigned int& InputManager::GetGamepadMaxCount() const noexcept
{
	return gamepadMaxCount;
}

const float* InputManager::GetMouseAxes() const noexcept
{
	return mouseAxes;
}

float InputManager::GetMouseAxis(unsigned int _axis) const noexcept
{
	if (_axis < 4)
		return mouseAxes[_axis];
	return 0.f;
}

bool InputManager::GetAction(const std::string& _action) const noexcept
{
	std::map<std::string, InputAction>::const_iterator	it{ actionsMap.find(_action) };
	if (it != actionsMap.end())
		return it->second.GetIsValid();
	return false;
}

float InputManager::GetAxis(const std::string& _axis) const noexcept
{
	std::map<std::string, InputAxis>::const_iterator	it{ axesMap.find(_axis) };
	if (it != axesMap.end())
		return it->second.GetValue();
	return 0.f;
}

/* TODO: test if it erase the good elements */
InputManager* InputManager::SetGamepadMaxCount(unsigned int _gamepadMaxCount) noexcept
{
	if (_gamepadMaxCount < gamepadStates.size())
		gamepadStates.erase(gamepadStates.end() - (gamepadStates.size() - _gamepadMaxCount), gamepadStates.end());

	gamepadMaxCount = std::min<unsigned int>(_gamepadMaxCount, G_GAMEPAD_MAX_COUNT);
	return this;
}

#pragma endregion

#pragma region Methods


#pragma endregion