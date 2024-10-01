#include "Debug/Log.h"
#include "Debug/Assert.h"

#include "Core/Camera/Camera.h"
#include "Core/Time.h"
#include "Inputs/InputManager.h"
#include "Inputs/Keys.h"
#include "ComponentSystem/GameObject.h"
#include "Physic/Transform.h"

using namespace Galatea;

Camera::Camera() noexcept
	:	UpdatableComponent(),
		front{ 0, 0, 1 },
		right{ 1, 0, 0 },
		up{ 0, 1, 0 }
{}

Camera::Camera(GameObject* _owner) noexcept
	:	UpdatableComponent(_owner),
		front{ 0, 0, 1 },
		right{ 1, 0, 0 },
		up{ 0, 1, 0 }
{}

Mat4 Camera::GetViewMatrix() noexcept
{
	Mat4 viewMatrix = Mat4::Identity();

	viewMatrix.line[0] = right;
	viewMatrix.line[1] = up;
	viewMatrix.line[2] = front;

	viewMatrix *= TRS::CreateTranslationMatrix(-owner->GetWorldPosition());
	return viewMatrix.Transposed();
}

void Camera::Update() noexcept
{
	front = (owner->GetWorldRotation() * Vec3::forward).Normalized();
	up = (owner->GetWorldRotation() * Vec3::up).Normalized();
	right = up.CrossProduct(front).Normalized();
}
