#include "Game/CameraFPSRotation.h"
#include "Inputs/InputManager.h"
#include "Inputs/Axes.h"
#include "Inputs/GamepadAxes.h"
#include "Core/Time.h"

using namespace Galatea;
using namespace GravityGun;

#pragma region Constructors/Destructor

CameraFPSRotation::CameraFPSRotation() noexcept
	: trs{ nullptr }, theta{ 0 }, phi{ 0 }, mouseSensivity{ 10 }, gamepadSensivity{ 200 }
{}

CameraFPSRotation::CameraFPSRotation(const CameraFPSRotation& _c) noexcept
	:	trs{ _c.trs }, theta{ _c.theta }, phi{ _c.phi },
		mouseSensivity{ _c.mouseSensivity }, gamepadSensivity{ _c.gamepadSensivity }
{}

CameraFPSRotation::CameraFPSRotation(CameraFPSRotation&& _c) noexcept
	:   trs{ std::move(_c.trs) }, theta{ std::move(_c.theta) },
		phi{ std::move(_c.phi) }, mouseSensivity{ std::move(_c.mouseSensivity) },
		gamepadSensivity{ std::move(_c.gamepadSensivity) }
{}

CameraFPSRotation::~CameraFPSRotation() noexcept
{
	trs = nullptr;
}

#pragma endregion

#pragma region Methods

void CameraFPSRotation::Init() noexcept
{
	trs = &owner->transform;

	InputAxis	mouseRotateX{ "mouseRotateX" };
	mouseRotateX.axisType = EAxisType::MOUSE;
	mouseRotateX.axis = G_AXIS_MOUSE_X;
	mouseRotateX.AddCallback(&CameraFPSRotation::OnMouseRotateX, *this);
	InputManager::GetInstance()->AddAxis(mouseRotateX);

	InputAxis	mouseRotateY{ "mouseRotateY" };
	mouseRotateY.axisType = EAxisType::MOUSE;
	mouseRotateY.axis = G_AXIS_MOUSE_Y;
	mouseRotateY.AddCallback(&CameraFPSRotation::OnMouseRotateY, *this);
	InputManager::GetInstance()->AddAxis(mouseRotateY);

	InputAxis	gamepadRotateX{ "gamepadRotateX" };
	gamepadRotateX.axisType = EAxisType::GAMEPAD;
	gamepadRotateX.axis = G_GAMEPAD_AXIS_RIGHT_X;
	gamepadRotateX.AddCallback(&CameraFPSRotation::OnGamepadRotateX, *this);
	InputManager::GetInstance()->AddAxis(gamepadRotateX);

	InputAxis	gamepadRotateY{ "gamepadRotateY" };
	gamepadRotateY.axisType = EAxisType::GAMEPAD;
	gamepadRotateY.axis = G_GAMEPAD_AXIS_RIGHT_Y;
	gamepadRotateY.inverse = true;
	gamepadRotateY.AddCallback(&CameraFPSRotation::OnGamepadRotateY, *this);
	InputManager::GetInstance()->AddAxis(gamepadRotateY);
}

void CameraFPSRotation::OnMouseRotateX(float _rotation) noexcept
{
	theta = _rotation * mouseSensivity * (float)Time::GetDeltaTime();
}

void CameraFPSRotation::OnMouseRotateY(float _rotation) noexcept
{
	phi += _rotation * mouseSensivity * (float)Time::GetDeltaTime();
}

void CameraFPSRotation::OnGamepadRotateX(float _rotation) noexcept
{
	theta = _rotation * gamepadSensivity * (float)Time::GetDeltaTime();
}

void CameraFPSRotation::OnGamepadRotateY(float _rotation) noexcept
{
	phi += _rotation * gamepadSensivity * (float)Time::GetDeltaTime();
}

void CameraFPSRotation::Update() noexcept
{
	theta = theta > 360 ? -360 : theta < -360 ? 360 : theta;
	phi = phi > 80 ? 80 : phi < -80 ? -80 : phi;

	owner->parent->transform.Rotate(Quaternion(owner->parent->transform.GetUpVector(), theta).Normalized());
	theta = 0;
	trs->rotation = Quaternion::FromEulerAngle({ phi, 0, 0 });
}

#pragma endregion

#pragma region Operators

CameraFPSRotation& CameraFPSRotation::operator=(const CameraFPSRotation& _c) noexcept
{
	trs					= _c.trs;
	theta				= _c.theta;
	phi					= _c.phi;
	mouseSensivity		= _c.mouseSensivity;
	gamepadSensivity	= _c.gamepadSensivity;
	return *this;
}

CameraFPSRotation& CameraFPSRotation::operator=(CameraFPSRotation&& _c) noexcept
{
	trs					= std::move(_c.trs);
	theta				= std::move(_c.theta);
	phi					= std::move(_c.phi);
	mouseSensivity		= std::move(_c.mouseSensivity);
	gamepadSensivity	= std::move(_c.gamepadSensivity);
	return *this;
}

#pragma endregion