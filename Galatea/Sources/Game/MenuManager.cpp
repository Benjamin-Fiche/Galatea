#include "Game/MenuManager.h"

#include "Core/Scene.h"
#include "Inputs/InputManager.h"
#include "Inputs/Keys.h"
#include "Inputs/GamepadButtons.h"

using namespace Galatea;
using namespace GravityGun;

#pragma region Constructors/Destructor

MenuManager::MenuManager() noexcept
{
	InputAction	space{ "space" };
	space.AddPattern(EDeviceType::KEYBOARD, EInputState::PRESSED, G_KEY_SPACE);
	space.AddPattern(EDeviceType::GAMEPAD, EInputState::PRESSED, G_GAMEPAD_BUTTON_A);
	space.AddCallback(&MenuManager::ChangeScene, *this);
	InputManager::GetInstance()->AddAction(space);
}

MenuManager::~MenuManager() noexcept
{}

#pragma endregion

#pragma region Methods

void MenuManager::ChangeScene() noexcept
{
	Scene::ChangeScene("Game");
}

#pragma endregion