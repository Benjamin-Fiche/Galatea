#include "Core/Camera/CameraFreeFlyMovement.h"
#include "Inputs/InputManager.h"
#include "Inputs/Keys.h"
#include "Inputs/Axes.h"
#include "Core/Time.h"

using namespace Galatea;

#pragma region Constructors/Destructors

CameraFreeFlyMovement::CameraFreeFlyMovement() noexcept
	: UpdatableComponent{}, camera{ nullptr }, trs{ nullptr }, theta{ 0 }, phi{ 0 }, speed{ 10 }, sensivity{ 10 }
{}

//CameraFreeFlyMovement::CameraFreeFlyMovement(const CameraFreeFlyMovement& _c) noexcept
//	: camera{ _c.camera }, trs{ _c.trs }, theta{ _c.theta }, phi{ _c.phi },
//	speed{ _c.speed }, sensivity{ _c.sensivity }
//{}
//
//CameraFreeFlyMovement::CameraFreeFlyMovement(CameraFreeFlyMovement&& _c) noexcept
//	: camera{ std::move(_c.camera) }, trs{ std::move(_c.trs) }, theta{ std::move(_c.theta) },
//	phi{ std::move(_c.phi) }, speed{ std::move(_c.speed) }, sensivity{ std::move(_c.sensivity) }
//{}

CameraFreeFlyMovement::~CameraFreeFlyMovement() noexcept
{
	camera = nullptr;
	trs = nullptr;
}

#pragma endregion

#pragma region Properties
#pragma endregion

#pragma region Methods

void CameraFreeFlyMovement::Init() noexcept
{
	camera = owner->GetComponent<Camera>();
	trs = &owner->transform;
}

void CameraFreeFlyMovement::Update() noexcept
{
	if (camera->isActive == false)
		return;
	theta += InputManager::GetInstance()->GetMouseAxis(G_AXIS_MOUSE_X) * sensivity * (float)Time::GetDeltaTime();
	phi += InputManager::GetInstance()->GetMouseAxis(G_AXIS_MOUSE_Y) * sensivity * (float)Time::GetDeltaTime();

	theta = theta > 360 ? -360 : theta < -360 ? 360 : theta;
	phi = phi > 80 ? 80 : phi < -80 ? -80 : phi;

	trs->rotation = Quaternion::FromEulerAngle({ phi, theta, 0 });
	
	if (InputManager::GetInstance()->GetKeyDown(G_KEY_W))
		trs->Translate(camera->GetFront() * speed * (float)Time::GetDeltaTime());
	if (InputManager::GetInstance()->GetKeyDown(G_KEY_S))
		trs->Translate(-camera->GetFront() * speed * (float)Time::GetDeltaTime());
	if (InputManager::GetInstance()->GetKeyDown(G_KEY_A))
		trs->Translate(-camera->GetRight() * speed * (float)Time::GetDeltaTime());
	if (InputManager::GetInstance()->GetKeyDown(G_KEY_D))
		trs->Translate(camera->GetRight() * speed * (float)Time::GetDeltaTime());
	if (InputManager::GetInstance()->GetKeyDown(G_KEY_SPACE))
		trs->Translate(Vector3::up * speed * (float)Time::GetDeltaTime());
	if (InputManager::GetInstance()->GetKeyDown(G_KEY_LEFT_SHIFT))
		trs->Translate(-Vector3::up * speed * (float)Time::GetDeltaTime());
}

#pragma endregion

#pragma region Operators

CameraFreeFlyMovement& CameraFreeFlyMovement::operator=(const CameraFreeFlyMovement& _c) noexcept
{
	camera		= _c.camera;
	trs			= _c.trs;
	theta		= _c.theta;
	phi			= _c.phi;
	speed		= _c.speed;
	sensivity	= _c.sensivity;
	return *this;
}

CameraFreeFlyMovement& CameraFreeFlyMovement::operator=(CameraFreeFlyMovement&& _c) noexcept
{
	camera		= std::move(_c.camera);
	trs			= std::move(_c.trs);
	theta		= std::move(_c.theta);
	phi			= std::move(_c.phi);
	speed		= std::move(_c.speed);
	sensivity	= std::move(_c.sensivity);
	return *this;
}

#pragma endregion
