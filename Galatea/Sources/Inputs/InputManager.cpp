#include <Libraries/GLFW/glfw3.h>

#include "Inputs/InputManager.h"
#include "Inputs/Keys.h"
#include "Inputs/MouseButtons.h"
#include "Inputs/Axes.h"
#include "Core/Render/WindowManager.h"

using namespace Galatea;

#pragma region Variables

InputManager* InputManager::instance{ nullptr };

#pragma endregion

#pragma region Constructors/Destructors

InputManager::InputManager() noexcept
	: window{}, lastMousePos {}, mousePos{}, keys{}, mouseButtons{}, gamepadStates{}, mouseAxes{}, gamepadMaxCount{ G_GAMEPAD_MAX_COUNT }
{}

#pragma endregion

#pragma region Methods

void InputManager::Init() noexcept
{
	window = WindowManager::GetInstance().window;
	InitKeys();
	InitMouse(window);
	InitGamepads();

	glfwSetScrollCallback(window, ScrollCallback);
	glfwSetJoystickCallback(JoystickCallback);
}

void InputManager::InitKeys() noexcept
{
	keys[G_KEY_SPACE]			= EInputState::UP;
	keys[G_KEY_APOSTROPHE]		= EInputState::UP;
	keys[G_KEY_COMMA]			= EInputState::UP;
	keys[G_KEY_MINUS]			= EInputState::UP;
	keys[G_KEY_POINT]			= EInputState::UP;
	keys[G_KEY_SLASH]			= EInputState::UP;
	keys[G_KEY_0]				= EInputState::UP;
	keys[G_KEY_1]				= EInputState::UP;
	keys[G_KEY_2]				= EInputState::UP;
	keys[G_KEY_3]				= EInputState::UP;
	keys[G_KEY_4]				= EInputState::UP;
	keys[G_KEY_5]				= EInputState::UP;
	keys[G_KEY_6]				= EInputState::UP;
	keys[G_KEY_7]				= EInputState::UP;
	keys[G_KEY_8]				= EInputState::UP;
	keys[G_KEY_9]				= EInputState::UP;
	keys[G_KEY_SEMICOLON]		= EInputState::UP;
	keys[G_KEY_EQUAL]			= EInputState::UP;
	keys[G_KEY_A]				= EInputState::UP;
	keys[G_KEY_B]				= EInputState::UP;
	keys[G_KEY_C]				= EInputState::UP;
	keys[G_KEY_D]				= EInputState::UP;
	keys[G_KEY_E]				= EInputState::UP;
	keys[G_KEY_F]				= EInputState::UP;
	keys[G_KEY_G]				= EInputState::UP;
	keys[G_KEY_H]				= EInputState::UP;
	keys[G_KEY_I]				= EInputState::UP;
	keys[G_KEY_J]				= EInputState::UP;
	keys[G_KEY_K]				= EInputState::UP;
	keys[G_KEY_L]				= EInputState::UP;
	keys[G_KEY_M]				= EInputState::UP;
	keys[G_KEY_N]				= EInputState::UP;
	keys[G_KEY_O]				= EInputState::UP;
	keys[G_KEY_P]				= EInputState::UP;
	keys[G_KEY_Q]				= EInputState::UP;
	keys[G_KEY_R]				= EInputState::UP;
	keys[G_KEY_S]				= EInputState::UP;
	keys[G_KEY_T]				= EInputState::UP;
	keys[G_KEY_U]				= EInputState::UP;
	keys[G_KEY_V]				= EInputState::UP;
	keys[G_KEY_W]				= EInputState::UP;
	keys[G_KEY_X]				= EInputState::UP;
	keys[G_KEY_Y]				= EInputState::UP;
	keys[G_KEY_Z]				= EInputState::UP;
	keys[G_KEY_LEFT_BRACKET]	= EInputState::UP;
	keys[G_KEY_BACKSLASH]		= EInputState::UP;
	keys[G_KEY_RIGHT_BRACKET]	= EInputState::UP;
	keys[G_KEY_GRAVE_ACCENT]	= EInputState::UP;
	keys[G_KEY_WORLD_1]			= EInputState::UP;
	keys[G_KEY_WORLD_2]			= EInputState::UP;
	keys[G_KEY_ESCAPE]			= EInputState::UP;
	keys[G_KEY_ENTER]			= EInputState::UP;
	keys[G_KEY_TAB]				= EInputState::UP;
	keys[G_KEY_BACKSPACE]		= EInputState::UP;
	keys[G_KEY_INSERT]			= EInputState::UP;
	keys[G_KEY_DELETE]			= EInputState::UP;
	keys[G_KEY_RIGHT]			= EInputState::UP;
	keys[G_KEY_LEFT]			= EInputState::UP;
	keys[G_KEY_DOWN]			= EInputState::UP;
	keys[G_KEY_UP]				= EInputState::UP;
	keys[G_KEY_PAGE_UP]			= EInputState::UP;
	keys[G_KEY_PAGE_DOWN]		= EInputState::UP;
	keys[G_KEY_HOME]			= EInputState::UP;
	keys[G_KEY_END]				= EInputState::UP;
	keys[G_KEY_CAPS_LOCK]		= EInputState::UP;
	keys[G_KEY_SCROLL_LOCK]		= EInputState::UP;
	keys[G_KEY_NUM_LOCK]		= EInputState::UP;
	keys[G_KEY_PRINT_SCREEN]	= EInputState::UP;
	keys[G_KEY_PAUSE]			= EInputState::UP;
	keys[G_KEY_F1]				= EInputState::UP;
	keys[G_KEY_F2]				= EInputState::UP;
	keys[G_KEY_F3]				= EInputState::UP;
	keys[G_KEY_F4]				= EInputState::UP;
	keys[G_KEY_F5]				= EInputState::UP;
	keys[G_KEY_F6]				= EInputState::UP;
	keys[G_KEY_F7]				= EInputState::UP;
	keys[G_KEY_F8]				= EInputState::UP;
	keys[G_KEY_F9]				= EInputState::UP;
	keys[G_KEY_F10]				= EInputState::UP;
	keys[G_KEY_F11]				= EInputState::UP;
	keys[G_KEY_F12]				= EInputState::UP;
	keys[G_KEY_F13]				= EInputState::UP;
	keys[G_KEY_F14]				= EInputState::UP;
	keys[G_KEY_F15]				= EInputState::UP;
	keys[G_KEY_F16]				= EInputState::UP;
	keys[G_KEY_F17]				= EInputState::UP;
	keys[G_KEY_F18]				= EInputState::UP;
	keys[G_KEY_F19]				= EInputState::UP;
	keys[G_KEY_F20]				= EInputState::UP;
	keys[G_KEY_F21]				= EInputState::UP;
	keys[G_KEY_F22]				= EInputState::UP;
	keys[G_KEY_F23]				= EInputState::UP;
	keys[G_KEY_F24]				= EInputState::UP;
	keys[G_KEY_F25]				= EInputState::UP;
	keys[G_KEY_KP_0]			= EInputState::UP;
	keys[G_KEY_KP_1]			= EInputState::UP;
	keys[G_KEY_KP_2]			= EInputState::UP;
	keys[G_KEY_KP_3]			= EInputState::UP;
	keys[G_KEY_KP_4]			= EInputState::UP;
	keys[G_KEY_KP_5]			= EInputState::UP;
	keys[G_KEY_KP_6]			= EInputState::UP;
	keys[G_KEY_KP_7]			= EInputState::UP;
	keys[G_KEY_KP_8]			= EInputState::UP;
	keys[G_KEY_KP_9]			= EInputState::UP;
	keys[G_KEY_KP_POINT]		= EInputState::UP;
	keys[G_KEY_KP_DIVIDE]		= EInputState::UP;
	keys[G_KEY_KP_MULTIPLY]		= EInputState::UP;
	keys[G_KEY_KP_SUBTRACT]		= EInputState::UP;
	keys[G_KEY_KP_ADD]			= EInputState::UP;
	keys[G_KEY_KP_ENTER]		= EInputState::UP;
	keys[G_KEY_KP_EQUAL]		= EInputState::UP;
	keys[G_KEY_LEFT_SHIFT]		= EInputState::UP;
	keys[G_KEY_LEFT_CONTROL]	= EInputState::UP;
	keys[G_KEY_LEFT_ALT]		= EInputState::UP;
	keys[G_KEY_LEFT_SUPER]		= EInputState::UP;
	keys[G_KEY_RIGHT_SHIFT]		= EInputState::UP;
	keys[G_KEY_RIGHT_CONTROL]	= EInputState::UP;
	keys[G_KEY_RIGHT_ALT]		= EInputState::UP;
	keys[G_KEY_RIGHT_SUPER]		= EInputState::UP;
	keys[G_KEY_MENU]			= EInputState::UP;
}

void InputManager::InitMouse(GLFWwindow* _window) noexcept
{
	double x, y;
	glfwGetCursorPos(_window, &x, &y);
	lastMousePos = { static_cast<float>(x), static_cast<float>(y) };

	for (unsigned int i = 0; i < 8; ++i)
		mouseButtons[i] = EInputState::UP;
}

void InputManager::InitGamepads() noexcept
{
	glfwPollEvents();

	for (unsigned int i = 0; i < gamepadMaxCount; ++i)
		if (glfwJoystickPresent(i) && glfwJoystickIsGamepad(i))
			gamepadStates.push_back(GamepadState{ i });
}

void InputManager::ScrollCallback(GLFWwindow* window, double _xOffset, double _yOffset) noexcept
{
	GetInstance()->mouseAxes[G_AXIS_MOUSE_SCROLL_X] = static_cast<float>(_xOffset);
	GetInstance()->mouseAxes[G_AXIS_MOUSE_SCROLL_Y] = static_cast<float>(_yOffset);
}

void InputManager::JoystickCallback(int _joystick, int _event) noexcept
{
	if (_event == GLFW_CONNECTED)
	{
		if (!glfwJoystickIsGamepad(_joystick))
			LogWarning("It's not a gamepad");

		const char* gamepadName = glfwGetGamepadName(_joystick);

		if (glfwJoystickPresent(_joystick) && glfwJoystickIsGamepad(_joystick) && static_cast<unsigned int>(_joystick) < GetInstance()->gamepadMaxCount)
		{
			if (_joystick < GetInstance()->gamepadStates.size())
				GetInstance()->gamepadStates[_joystick].isConnected = true;
			else
				GetInstance()->gamepadStates.push_back(GamepadState{ static_cast<unsigned int>(_joystick) });
		}

		if (gamepadName != nullptr)
			LogMsg("Gamepad " + std::to_string(_joystick) + ": " + gamepadName + " connected");
	}
	else if (_event == GLFW_DISCONNECTED)
	{
		if (_joystick < GetInstance()->gamepadStates.size())
			GetInstance()->gamepadStates[_joystick].isConnected = false;
		LogMsg(std::string("Gamepad ") + std::to_string(_joystick) + " disconnected");
	}
}

void InputManager::UpdateKeys() noexcept
{
	std::map<int, EInputState>::iterator	it;
	for (it = keys.begin(); it != keys.end(); ++it)
	{
		int	state{ glfwGetKey(window, it->first) };
		if (state == GLFW_PRESS)
		{
			if (it->second == EInputState::RELEASED)
				it->second = EInputState::PRESSED;
			else if (it->second == EInputState::UP)
				it->second = EInputState::PRESSED;
			else if (it->second == EInputState::PRESSED)
				it->second = EInputState::DOWN;
		}
		else if (state == GLFW_RELEASE)
		{
			if (it->second == EInputState::PRESSED)
				it->second = EInputState::RELEASED;
			else if (it->second == EInputState::DOWN)
				it->second = EInputState::RELEASED;
			else if (it->second == EInputState::RELEASED)
				it->second = EInputState::UP;
		}
	}
}

void InputManager::UpdateMouseButtons() noexcept
{
	for (int i = 0; i < 8; ++i)
	{
		int	state{ glfwGetMouseButton(window, i) };
		if (state == GLFW_PRESS)
		{
			if (mouseButtons[i] == EInputState::UP)
				mouseButtons[i] = EInputState::PRESSED;
			else if (mouseButtons[i] == EInputState::PRESSED)
				mouseButtons[i] = EInputState::DOWN;
		}
		else
		{
			if (mouseButtons[i] == EInputState::DOWN)
				mouseButtons[i] = EInputState::RELEASED;
			else if (mouseButtons[i] == EInputState::RELEASED)
				mouseButtons[i] = EInputState::UP;
		}
	}
}

void InputManager::UpdateCursor() noexcept
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	Vector2	mousePos = { static_cast<float>(x), static_cast<float>(y) };
	Vector2 lastMousePos = GetInstance()->lastMousePos;
	
	GetInstance()->mouseAxes[G_AXIS_MOUSE_X] = mousePos.x - lastMousePos.x;
	GetInstance()->mouseAxes[G_AXIS_MOUSE_Y] = mousePos.y - lastMousePos.y;
	GetInstance()->mousePos = mousePos;
	GetInstance()->lastMousePos = mousePos;
}

InputManager* InputManager::AddAction() noexcept
{
	actionsMap["Action" + std::to_string(actionsMap.size())] = {};
	return this;
}

InputManager* InputManager::AddAction(const InputAction& _action) noexcept
{
	actionsMap[_action.name] = _action;
	return this;
}

InputManager* InputManager::AddAction(InputAction&& _action) noexcept
{
	actionsMap[_action.name] = std::move(_action);
	return this;
}

InputManager* InputManager::AddAxis() noexcept
{
	axesMap["Axis" + std::to_string(axesMap.size())] = {};
	return this;
}

InputManager* InputManager::AddAxis(const InputAxis& _axis) noexcept
{
	axesMap[_axis.name] = _axis;
	return this;
}

InputManager* InputManager::AddAxis(InputAxis&& _axis) noexcept
{
	axesMap[_axis.name] = std::move(_axis);
	return this;
}

bool InputManager::IsGamepadConnected(int _gamepadID) const noexcept
{
	return glfwJoystickPresent(_gamepadID);
}

void InputManager::Update() noexcept
{
	glfwPollEvents();

	UpdateKeys();
	UpdateMouseButtons();
	UpdateCursor();

	/* Update gamepadStates */
	std::vector<GamepadState>::iterator	gamepadIt;
	for (gamepadIt = gamepadStates.begin(); gamepadIt != gamepadStates.end(); ++gamepadIt)
		if ((*gamepadIt).isConnected)
			(*gamepadIt).Update();

	/* Update ActionMap*/
	std::map<std::string, InputAction>::iterator	actionIt;
	for (actionIt = actionsMap.begin(); actionIt != actionsMap.end(); ++actionIt)
		actionIt->second.Update();

	/* Update AxesMap*/
	std::map<std::string, InputAxis>::iterator	axisIt;
	for (axisIt = axesMap.begin(); axisIt != axesMap.end(); ++axisIt)
		axisIt->second.Update();
}

void InputManager::UpdateInEditor() noexcept
{
	glfwPollEvents();

	UpdateKeys();
	UpdateMouseButtons();
	UpdateCursor();
}
#pragma endregion