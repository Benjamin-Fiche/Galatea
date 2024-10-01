#include "Debug/Log.h"
#include "Core/Camera/CameraInEditor.h"
#include "Core/Time.h"
#include "Inputs/InputManager.h"
#include "Inputs/Keys.h"
#include "Inputs/Axes.h"
#include "Physic/Transform.h"

using namespace Galatea;

void CameraInEditor::Update() noexcept
{
	theta += InputManager::GetInstance()->GetMouseAxis(G_AXIS_MOUSE_X) * sensivity * (float)Time::GetDeltaTime();
	phi += InputManager::GetInstance()->GetMouseAxis(G_AXIS_MOUSE_Y) * sensivity * (float)Time::GetDeltaTime();

	theta = theta > 360 ? -360 : theta < -360 ? 360 : theta;
	phi = phi > 80 ? 80 : phi < -80 ? -80 : phi;

	trs.rotation = Quaternion::FromEulerAngle({ phi, theta, 0 });

	front = (trs.rotation * Vec3::forward).Normalized();
	right = Vec3::up.CrossProduct(front).Normalized();
	up = front.CrossProduct(right).Normalized();

	if (InputManager::GetInstance()->GetKeyDown(G_KEY_LEFT_CONTROL))
		speed = 1.f;
	else
		speed = 10.f;

	if (InputManager::GetInstance()->GetKeyDown(G_KEY_W))
		trs.Translate(front * speed * (float)Time::GetDeltaTime());
	if (InputManager::GetInstance()->GetKeyDown(G_KEY_S))
		trs.Translate(-front * speed * (float)Time::GetDeltaTime());
	if (InputManager::GetInstance()->GetKeyDown(G_KEY_A))
		trs.Translate(-right * speed * (float)Time::GetDeltaTime());
	if (InputManager::GetInstance()->GetKeyDown(G_KEY_D))
		trs.Translate(right * speed * (float)Time::GetDeltaTime());
	if (InputManager::GetInstance()->GetKeyDown(G_KEY_SPACE))
		trs.Translate(Vector3::up * speed * (float)Time::GetDeltaTime());
	if (InputManager::GetInstance()->GetKeyDown(G_KEY_LEFT_SHIFT))
		trs.Translate(-Vector3::up * speed * (float)Time::GetDeltaTime());
}

Mat4 CameraInEditor::GetViewProjMatrix() const noexcept
{
	Mat4 rotate = Mat4::Identity();

	rotate.line[0] = right;
	rotate.line[1] = up;
	rotate.line[2] = front;

	Mat4 translate = TRS::CreateTranslationMatrix(-trs.position);

	Mat4 viewMatrix = rotate * translate;

	return viewMatrix.Transposed() * projectionMatrix;
}

const Vec3& CameraInEditor::GetPosition() const	noexcept
{
	return trs.position;
}

void CameraInEditor::ResetRotation() noexcept
{
	/*Vector2	mousePos{ InputManager::GetInstance()->GetMousePos() };

	lastX = mousePos.x;
	lastY = mousePos.y;*/
}