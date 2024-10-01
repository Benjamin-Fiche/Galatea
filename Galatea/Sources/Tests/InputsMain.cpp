#include <iostream>

#include "Inputs/Event.h"
#include "Inputs/InputManager.h"
#include "Inputs/Keys.h"
#include "Inputs/Axes.h"
#include "Inputs/MouseButtons.h"
#include "Inputs/GamepadAxes.h"
#include "Inputs/GamepadButtons.h"
#include "Core/Render/WindowManager.h"

class InputTest
{
private:
	void	Jump() noexcept
	{
		std::cout << "Jump\n";
	}

	void	MoveX(float _x) noexcept
	{
		std::cout << "x: " << _x << std::endl;
	}

	void	MoveY(float _y) noexcept
	{
		std::cout << "y: " << _y << std::endl;
	}

	void	Shoot() noexcept
	{
		std::cout << "piew\n";
	}

public:
	void Init() noexcept
	{
		using namespace Galatea;

		InputAction	jump{ "jump" };
		jump.AddPattern(EDeviceType::KEYBOARD, EInputState::PRESSED, G_KEY_SPACE);
		jump.AddPattern(EDeviceType::GAMEPAD, EInputState::PRESSED, G_GAMEPAD_BUTTON_A, 0);
		jump.AddPattern(EDeviceType::GAMEPAD, EInputState::PRESSED, G_GAMEPAD_BUTTON_CROSS, 1);
		jump.AddCallback(&InputTest::Jump, *this);
		InputManager::GetInstance()->AddAction(jump);

		InputAction	shoot{ "shoot" };
		shoot.AddPattern(EDeviceType::MOUSE, EInputState::DOWN, G_MOUSE_BUTTON_LEFT);
		shoot.AddPattern(EDeviceType::GAMEPAD, EInputState::DOWN, G_GAMEPAD_BUTTON_LEFT_BUMPER, 0);
		shoot.AddPattern(EDeviceType::GAMEPAD, EInputState::DOWN, G_GAMEPAD_BUTTON_LEFT_BUMPER, 1);
		shoot.AddCallback(&InputTest::Shoot, *this);
		InputManager::GetInstance()->AddAction(shoot);

		InputAxis moveXButtons{ "moveXButtons" };
		moveXButtons.axisType = EAxisType::BUTTONS;
		moveXButtons.AddPositiveButton(EDeviceType::KEYBOARD, EInputState::DOWN, G_KEY_D);
		moveXButtons.AddPositiveButton(EDeviceType::KEYBOARD, EInputState::DOWN, G_KEY_RIGHT);
		moveXButtons.AddPositiveButton(EDeviceType::GAMEPAD, EInputState::DOWN, G_GAMEPAD_BUTTON_DPAD_RIGHT, 0);
		moveXButtons.AddPositiveButton(EDeviceType::GAMEPAD, EInputState::DOWN, G_GAMEPAD_BUTTON_DPAD_RIGHT, 1);
		moveXButtons.AddNegativeButton(EDeviceType::KEYBOARD, EInputState::DOWN, G_KEY_A);
		moveXButtons.AddNegativeButton(EDeviceType::KEYBOARD, EInputState::DOWN, G_KEY_LEFT);
		moveXButtons.AddNegativeButton(EDeviceType::GAMEPAD, EInputState::DOWN, G_GAMEPAD_BUTTON_DPAD_LEFT, 0);
		moveXButtons.AddNegativeButton(EDeviceType::GAMEPAD, EInputState::DOWN, G_GAMEPAD_BUTTON_DPAD_LEFT, 1);
		moveXButtons.AddCallback(&InputTest::MoveX, *this);
		InputManager::GetInstance()->AddAxis(moveXButtons);

		InputAxis moveXAxisGamepad1{ "moveXAxisGamepad1" };
		moveXAxisGamepad1.axisType = EAxisType::GAMEPAD;
		moveXAxisGamepad1.axis = G_GAMEPAD_AXIS_LEFT_X;
		moveXAxisGamepad1.gamepadID = 0;
		moveXAxisGamepad1.AddCallback(&InputTest::MoveX, *this);
		InputManager::GetInstance()->AddAxis(moveXAxisGamepad1);

		InputAxis moveXAxisGamepad2{ "moveXAxisGamepad2" };
		moveXAxisGamepad2.axisType = EAxisType::GAMEPAD;
		moveXAxisGamepad2.axis = G_GAMEPAD_AXIS_LEFT_X;
		moveXAxisGamepad2.gamepadID = 1;
		moveXAxisGamepad2.AddCallback(&InputTest::MoveX, *this);
		InputManager::GetInstance()->AddAxis(moveXAxisGamepad2);

		InputAxis moveYButtons{ "moveYButtons" };
		moveYButtons.axisType = EAxisType::BUTTONS;
		moveYButtons.AddPositiveButton(EDeviceType::KEYBOARD, EInputState::DOWN, G_KEY_W);
		moveYButtons.AddPositiveButton(EDeviceType::KEYBOARD, EInputState::DOWN, G_KEY_UP);
		moveYButtons.AddPositiveButton(EDeviceType::GAMEPAD, EInputState::DOWN, G_GAMEPAD_BUTTON_DPAD_UP, 0);
		moveYButtons.AddPositiveButton(EDeviceType::GAMEPAD, EInputState::DOWN, G_GAMEPAD_BUTTON_DPAD_UP, 1);
		moveYButtons.AddNegativeButton(EDeviceType::KEYBOARD, EInputState::DOWN, G_KEY_S);
		moveYButtons.AddNegativeButton(EDeviceType::KEYBOARD, EInputState::DOWN, G_KEY_DOWN);
		moveYButtons.AddNegativeButton(EDeviceType::GAMEPAD, EInputState::DOWN, G_GAMEPAD_BUTTON_DPAD_DOWN, 0);
		moveYButtons.AddNegativeButton(EDeviceType::GAMEPAD, EInputState::DOWN, G_GAMEPAD_BUTTON_DPAD_DOWN, 1);
		moveYButtons.AddCallback(&InputTest::MoveY, *this);
		InputManager::GetInstance()->AddAxis(moveYButtons);

		InputAxis moveYAxisGamepad1{ "moveYAxisGamepad1" };
		moveYAxisGamepad1.axisType = EAxisType::GAMEPAD;
		moveYAxisGamepad1.axis = G_GAMEPAD_AXIS_LEFT_X;
		moveYAxisGamepad1.gamepadID = 0;
		moveYAxisGamepad1.AddCallback(&InputTest::MoveY, *this);
		InputManager::GetInstance()->AddAxis(moveYAxisGamepad1);

		InputAxis moveYAxisGamepad2{ "moveYAxisGamepad2" };
		moveYAxisGamepad2.axisType = EAxisType::GAMEPAD;
		moveYAxisGamepad2.axis = G_GAMEPAD_AXIS_LEFT_X;
		moveYAxisGamepad2.gamepadID = 1;
		moveYAxisGamepad2.AddCallback(&InputTest::MoveY, *this);
		InputManager::GetInstance()->AddAxis(moveYAxisGamepad2);
	}
};

int main()
{
	using namespace Galatea;

	WindowManager& wm{ WindowManager::GetInstance() };
	if (!wm.Init(4.5, true) || !wm.OpenWindow("Inputs"))
		return EXIT_FAILURE;

	InputManager::GetInstance()->Init();
	InputTest	test;
	test.Init();
	

	while (wm.IsWindowRunning())
	{
		glfwPollEvents();
		InputManager::GetInstance()->Update();
	}

	delete Log::GetInstance();
}