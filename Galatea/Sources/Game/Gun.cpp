#include "Game/Gun.h"

#include "Inputs/InputManager.h"
#include "Inputs/MouseButtons.h"
#include "Inputs/Keys.h"
#include "Inputs/GamepadButtons.h"

#include "Physic/Physics.h"
#include "Physic/RigidBody.h"
#include "Game/Player.h"
#include "Core/Time.h"
#include "Game/InteractableObject.h"

using namespace Galatea;
using namespace GravityGun;

Gun::Gun()	noexcept
{}

void	Gun::Init() noexcept
{
	gravityChangeSound = owner->GetComponents<Sound>()[0];
	freezeSound = owner->GetComponents<Sound>()[1];
	unfreezeSound = owner->GetComponents<Sound>()[2];

	InputAction	getObjectGravity{ "leftShoot" };
	getObjectGravity.AddPattern(EDeviceType::MOUSE, EInputState::PRESSED, G_MOUSE_BUTTON_LEFT);
	getObjectGravity.AddPattern(EDeviceType::GAMEPAD, EInputState::PRESSED, G_GAMEPAD_BUTTON_LEFT_BUMPER);
	getObjectGravity.AddCallback(&Gun::GetObjectGravity, *this);
	InputManager::GetInstance()->AddAction(getObjectGravity);

	InputAction	setObjectGravity{ "rightShoot" };
	setObjectGravity.AddPattern(EDeviceType::MOUSE, EInputState::PRESSED, G_MOUSE_BUTTON_RIGHT);
	setObjectGravity.AddPattern(EDeviceType::GAMEPAD, EInputState::PRESSED, G_GAMEPAD_BUTTON_RIGHT_BUMPER);
	setObjectGravity.AddCallback(&Gun::SetObjectGravity, *this);
	InputManager::GetInstance()->AddAction(setObjectGravity);

	InputAction	freezeObject{ "freeze" };
	freezeObject.AddPattern(EDeviceType::KEYBOARD, EInputState::PRESSED, G_KEY_E);
	freezeObject.AddPattern(EDeviceType::GAMEPAD, EInputState::PRESSED, G_GAMEPAD_BUTTON_Y);
	freezeObject.AddCallback(&Gun::FreezeObject, *this);
	InputManager::GetInstance()->AddAction(freezeObject);

	freezeSound->SetVolume(0.2f);
	unfreezeSound->SetVolume(0.2f);
}

void	Gun::GetObjectGravity()	noexcept
{
	Player* player = GetOwner()->GetComponent<Player>();

	if (player != nullptr)
	{
		Vec3 origin = player->GetCamera().GetOwner()->GetWorldPosition();
		Vec3 dir = player->GetCamera().GetFront();
		RigidBody* playerRigidBody = GetOwner()->GetComponent<RigidBody>();

		if (playerRigidBody != nullptr)
		{
			Galatea::RigidBody* rb = &Physics::Raycast(origin, dir, 1000);

			if (rb != nullptr)
			{
				Vec3 gravity{ rb->GetGravity() };
				if (gravity.Normalized() == playerRigidBody->GetGravity().Normalized())
					return;

				playerRigidBody->SetGravity(gravity * player->GetFallingSpeed());
				playerRigidBody->ResetVelocity();

				gravityChangeSound->Play();

				advencement = 0;
				isRotating = true;
			}
		}
	}
}

void	Gun::SetObjectGravity()	noexcept
{
	Player* player = GetOwner()->GetComponent<Player>();

	if (player != nullptr)
	{
		Vec3 origin = player->GetCamera().GetOwner()->GetWorldPosition();
		Vec3 dir = player->GetCamera().GetFront();
		RigidBody* playerRigidBody = GetOwner()->GetComponent<RigidBody>();

		if (playerRigidBody != nullptr)
		{
			Galatea::RigidBody* rb = &Physics::Raycast(origin, dir, 1000);

			if (rb != nullptr)
			{
				InteractableObject* object{ rb->owner->GetComponent<GravityGun::InteractableObject>() };
				if (object != nullptr)
				{
					object->SetGravity(playerRigidBody->GetGravity() / player->GetFallingSpeed());
					gravityChangeSound->Play();
				}
			}
		}
	}
}

void	Gun::FreezeObject()	noexcept
{
	Player* player = GetOwner()->GetComponent<Player>();

	if (player != nullptr)
	{
		Vec3 origin = player->GetCamera().GetOwner()->GetWorldPosition();
		Vec3 dir = player->GetCamera().GetFront();
		RigidBody* playerRigidBody = GetOwner()->GetComponent<RigidBody>();

		if (playerRigidBody != nullptr)
		{
			Galatea::RigidBody* rb = &Physics::Raycast(origin, dir, 1000);

			if (rb != nullptr)
			{
				InteractableObject* object{ rb->owner->GetComponent<GravityGun::InteractableObject>() };
				if (object != nullptr)
				{
					rb->SetIsStatic(!rb->GetIsStatic());
					if (rb->GetIsStatic())
					{
						unfreezeSound->Stop();
						freezeSound->Play();
					}
					else
					{
						freezeSound->Stop();
						unfreezeSound->Play();
					}
				}
			}
		}
	}
}

void Gun::SLerpRotation() noexcept
{
	advencement += (float)Time::GetDeltaTime() * rotationSpeed; 

	if (advencement >= 1)
	{
		isRotating = false;
		return;
	}
	else
	{
		Vec3 gravity{ owner->GetComponent<RigidBody>()->GetGravity() };
		Vec3 down = -GetOwner()->transform.GetUpVector();

		Quaternion rot = Quaternion::RotationBetweenVector(down, gravity).Normalized();

		if (rot == Quaternion::identity)
		{
			isRotating = false;
			return;
		}

		owner->transform.rotation = owner->transform.rotation.Slerp((rot * owner->transform.rotation).Normalized(), advencement).Normalized();
	}
}

void Gun::Update() noexcept
{
	if (isRotating)
		SLerpRotation();
}