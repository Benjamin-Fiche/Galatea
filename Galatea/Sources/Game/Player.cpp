#include <cmath>

#include "Game/Player.h"
#include "Core/Time.h"
#include "Inputs/InputManager.h"
#include "Inputs/Keys.h"
#include "Inputs/GamepadAxes.h"

using namespace Galatea;
using namespace GravityGun;

#pragma region Constructors/Destructor

Player::Player() noexcept
	: direction{ 0, 0, 0 }, camera{ nullptr }, speed{ 10 }, jumpForce{ 1 }
{}

Player::~Player() noexcept
{}

#pragma endregion

#pragma region Methods

void Player::Init() noexcept
{
	camera = owner->GetChild("Camera")->GetComponent<Camera>();
	rigidBody = owner->GetComponent<RigidBody>();

	InputAxis	moveFront{ "moveFront" };
	moveFront.axisType = EAxisType::BUTTONS;
	moveFront.AddPositiveButton(EDeviceType::KEYBOARD, EInputState::DOWN, G_KEY_W);
	moveFront.AddNegativeButton(EDeviceType::KEYBOARD, EInputState::DOWN, G_KEY_S);
	moveFront.AddCallback(&Player::OnMoveFront, *this);
	InputManager::GetInstance()->AddAxis(moveFront);

	InputAxis	moveRight{ "moveRight" };
	moveRight.axisType = EAxisType::BUTTONS;
	moveRight.AddPositiveButton(EDeviceType::KEYBOARD, EInputState::DOWN, G_KEY_D);
	moveRight.AddNegativeButton(EDeviceType::KEYBOARD, EInputState::DOWN, G_KEY_A);
	moveRight.AddCallback(&Player::OnMoveRight, *this);
	InputManager::GetInstance()->AddAxis(moveRight);

	InputAxis	moveFrontGamepad{ "moveFrontGamepad" };
	moveFrontGamepad.axisType = EAxisType::GAMEPAD;
	moveFrontGamepad.axis = G_GAMEPAD_AXIS_LEFT_Y;
	moveFrontGamepad.gamepadID = 0;
	moveFrontGamepad.AddCallback(&Player::OnMoveFront, *this);
	InputManager::GetInstance()->AddAxis(moveFrontGamepad);

	InputAxis	moveRightGamepad{ "moveRightGamepad" };
	moveRightGamepad.axisType = EAxisType::GAMEPAD;
	moveRightGamepad.axis = G_GAMEPAD_AXIS_LEFT_X;
	moveRightGamepad.gamepadID = 0;
	moveRightGamepad.AddCallback(&Player::OnMoveRight, *this);
	InputManager::GetInstance()->AddAxis(moveRightGamepad);

	InputAction jumpAction{ "Jump" };
	jumpAction.AddPattern(EDeviceType::KEYBOARD, EInputState::PRESSED, G_KEY_SPACE);
	jumpAction.AddCallback(&Player::OnJump, *this);
	InputManager::GetInstance()->AddAction(jumpAction);

	jumpForce = 50;
	fallingSpeed = 3;

	rigidBody->SetGravity(rigidBody->GetGravity().Normalized() * 9.81f * fallingSpeed);
	rigidBody->SetFreezeRotation({ 1, 1, 1 });
	rigidBody->SetMass(5);
	rigidBody->SetRestitution(0);
}

void Player::OnMoveFront(float _movement) noexcept
{
	direction += (owner->GetWorldRotation() * Vec3::forward).Normalized() * _movement;
}

void Player::OnMoveRight(float _movement) noexcept
{
	direction += (owner->GetWorldRotation() * Vec3::right).Normalized() * _movement;
}

void Player::Update() noexcept
{
	float	directionMagnitude{ fminf(direction.Length(), 1.f) };

	if (directionMagnitude > 0)
	{
		owner->transform.Translate(direction.Normalized() * directionMagnitude * speed * (float)Time::GetDeltaTime());
	}

	direction = Vector3::zero;

	UpdateIsGrounded();
}

void Player::UpdateIsGrounded() noexcept
{
	Galatea::RigidBody* rb = &Physics::Raycast(
									owner->transform.position + rigidBody->GetGravity().Normalized() * (rigidBody->GetColliderScale().y / 2 + 0.1f),
									rigidBody->GetGravity(),
									0.01f);
	if (rb != nullptr)
		isGrounded = true;
	else
		isGrounded = false;
}

void Player::OnJump() noexcept
{ 
	if (!isGrounded)
		return;

	rigidBody->AddForce(rigidBody->GetGravity().Normalized() * -jumpForce, EForceType::IMPULSE);
}

#pragma endregion

#pragma region Operators
#pragma endregion