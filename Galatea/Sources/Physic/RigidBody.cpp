#include "Physic/RigidBody.h"

#include "Core/SceneManager.h"
#include "ComponentSystem/GameObject.h"
#include "Physic/Transform.h"

#include "Debug/Assert.h"

using namespace Galatea;

RigidBody::RigidBody() noexcept :
	physics			{ nullptr },
	physicsActor	{ nullptr },
	isOnContact		{ false },
	gravity			{ Vec3{0.f, -9.81f, 0.f} },
	colliderScale	{ Vec3{1.f, 1.f, 1.f} },
	isStatic		{ true },
	isTrigger		{ false },
	geometry		{ EGeometryType::BOX },
	freezePosition	{ Vec3{0, 0, 0} },
	freezeRotation	{ Vec3{0, 0, 0} },
	staticFriction	{ 1.f },
	dynamicFriction	{ 1.f },
	restitution		{ 0.f },
	mass			{ 1.f}
{}

RigidBody::~RigidBody()
{
	physicsActor = nullptr;
}

void	RigidBody::Init(Physics& _physics)	noexcept
{
	physics = &_physics;
	CreateNewPhysicsActor();

	SetColliderScale(owner->GetWorldScale()); 
	physics->SetActorPos(physicsActor, owner->GetWorldPosition(), owner->GetWorldRotation());
}

void	RigidBody::CreateNewPhysicsActor()	noexcept
{
	if (physics != nullptr)
		physics->CreateObject(*this, physicsActor);
}

void	RigidBody::AddForce(const Vec3& _force, const EForceType& _type)	noexcept
{
	if (!isStatic)
		physics->AddForce(physicsActor, _force, _type);
}

void	RigidBody::ResetVelocity()	noexcept
{
	if (!isStatic)
		physics->ResetVelocity(physicsActor);
}

void	RigidBody::FixedUpdate()	noexcept
{
	if (isStatic)
		return;
	
	if (!(lastTransform.position == owner->GetWorldPosition()) || !(lastTransform.rotation == owner->GetWorldRotation()))
	{
		lastTransform.position = owner->GetWorldPosition();
		lastTransform.rotation = owner->GetWorldRotation();
		physics->SetActorPos(physicsActor, lastTransform.position, lastTransform.rotation);
	}
}

void	RigidBody::SetOwnerTransform(const Vec3& _pos, const Quat& _rot)	noexcept
{
	if (owner->parent == nullptr)
	{
		owner->transform.position = _pos;
		owner->transform.rotation = _rot;
	}
	else
	{
		owner->transform.position = _pos - owner->parent->GetWorldPosition();
		owner->transform.rotation = _rot * owner->parent->GetWorldRotation().Inversed();
	}

	lastTransform.position = owner->GetWorldPosition();
	lastTransform.rotation = owner->GetWorldRotation();
}

void	RigidBody::Enable(const bool _enable)	noexcept
{
	physics->EnableActor(physicsActor, _enable);
}

void	RigidBody::OnContact(RigidBody* _other)	noexcept
{
	if (isOnContact)
		OnEndOverlap(_other);
	else
		OnBeginOverlap(_other);

	isOnContact = !isOnContact;
}

void	RigidBody::OnBeginOverlap(RigidBody* _other)	noexcept
{
	onBeginOverlapEvent(_other);
}

void	RigidBody::OnEndOverlap(RigidBody* _other)	noexcept
{
	onEndOverlapEvent(_other);
}

#pragma region Setters
void	RigidBody::SetGravity(const Vec3& _gravity)	noexcept
{
	gravity = _gravity;
}

void	RigidBody::SetColliderScale(const Vec3& _scale)	noexcept
{
	colliderScale = _scale;
	physics->SetActorGeometry(physicsActor, geometry, colliderScale);
}

void	RigidBody::SetIsStatic(const bool& _isStatic)	noexcept
{
	if (isStatic != _isStatic)
	{
		isStatic = _isStatic;
		CreateNewPhysicsActor();
	}
}

void	RigidBody::SetIsTrigger(const bool& _isTrigger)	noexcept
{
	if (isTrigger != _isTrigger)
	{
		isTrigger = _isTrigger;
		physics->SetShapeFlags(physicsActor, isTrigger);
	}
}

void	RigidBody::SetGeometry(const EGeometryType& _geom)	noexcept
{
	if (geometry != _geom)
	{
		geometry = _geom;
		CreateNewPhysicsActor();
	}
}

/* Set -> 0 = false | 1 = true*/
void	RigidBody::SetFreezePosition(const Vec3& _freezePosition)	noexcept
{
	if ((_freezePosition.x == 0 || _freezePosition.x == 1) &&
		(_freezePosition.y == 0 || _freezePosition.y == 1) &&
		(_freezePosition.z == 0 || _freezePosition.z == 1))
	{
		freezePosition = _freezePosition;

		if (!isStatic)
			physics->SetActorLockFlags(physicsActor, freezePosition, freezeRotation);
	}
}

/* Set -> 0 = false | 1 = true*/
void	RigidBody::SetFreezeRotation(const Vec3& _freezeRotation)	noexcept
{
	if ((_freezeRotation.x == 0 || _freezeRotation.x == 1) &&
		(_freezeRotation.y == 0 || _freezeRotation.y == 1) &&
		(_freezeRotation.z == 0 || _freezeRotation.z == 1))
	{
		freezeRotation = _freezeRotation;

		if (!isStatic)
			physics->SetActorLockFlags(physicsActor, freezePosition, freezeRotation);
	}
}

void	RigidBody::SetStaticFriction(const float& _staticFriction)	noexcept
{
	staticFriction = _staticFriction;
	physics->SetActorMaterial(physicsActor, staticFriction, dynamicFriction, restitution);
}

void	RigidBody::SetDynamicFriction(const float& _dynamicFriction)	noexcept
{
	dynamicFriction = _dynamicFriction;
	physics->SetActorMaterial(physicsActor, staticFriction, dynamicFriction, restitution);
}

void	RigidBody::SetRestitution(const float& _restitution)	noexcept
{
	restitution = _restitution;
	physics->SetActorMaterial(physicsActor, staticFriction, dynamicFriction, restitution);
}

void	RigidBody::SetMass(const float& _mass)	noexcept
{
	if (_mass >= 0)
	{
		mass = _mass;
		if (!isStatic)
			physics->SetActorMass(physicsActor, mass);
	}
}
#pragma endregion
