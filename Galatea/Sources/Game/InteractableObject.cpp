#include <cmath>

#include "Core/Render/Mesh.h"
#include "Game/InteractableObject.h"

using namespace Galatea;
using namespace GravityGun;

#pragma region Constructors/Destructor

InteractableObject::InteractableObject() noexcept
	:	rigidBody{ nullptr }, material{ nullptr },
		positiveGravityColors{ { 255.f / 255.f, 155.f / 255.f, 0 }, { 0, 185.f / 255.f, 40.f / 255.f }, { 255.f / 255.f, 240 / 255.f, 0 } },
		negativeGravityColors{ { 0, 0, 255.f / 255.f }, { 255.f / 255.f, 0, 0 }, { 150.f / 255.f , 0, 255.f / 255.f } },
		colorSelector{ 1, 2, 3 }
{}

InteractableObject::~InteractableObject() noexcept
{
	rigidBody	= nullptr;
	material	= nullptr;
}

#pragma endregion

#pragma region Methods

void InteractableObject::Init() noexcept
{
	rigidBody = owner->GetComponent<RigidBody>();
	material = owner->GetComponent<Mesh>()->GetMaterial(0);

	SetColor(rigidBody->GetGravity());

	rigidBody->SetFreezeRotation({ 1, 1, 1 });
	rigidBody->SetMass(20);
	//rigidBody->SetIsStatic(true);
}

void InteractableObject::SetColor(const Vector3& _gravity) noexcept
{
	float	color{ _gravity.Normalized().DotProduct(colorSelector) };

	if (color < 0)
	{
		material->SetAmbientColor(negativeGravityColors[(int)fabsf(color) - 1]);
		material->SetDiffuseColor(negativeGravityColors[(int)fabsf(color) - 1 ]);
		material->SetSpecularColor(negativeGravityColors[(int)fabsf(color) - 1]);
	}
	else
	{
		material->SetAmbientColor(positiveGravityColors[(int)fabsf(color) - 1]);
		material->SetDiffuseColor(positiveGravityColors[(int)fabsf(color) - 1]);
		material->SetSpecularColor(positiveGravityColors[(int)fabsf(color) - 1]);
	}
}

void InteractableObject::SetGravity(const Vector3& _gravity) noexcept
{
	rigidBody->SetGravity(_gravity);
	rigidBody->ResetVelocity();
	SetColor(_gravity);
}

#pragma endregion