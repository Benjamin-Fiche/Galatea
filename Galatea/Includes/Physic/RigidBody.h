#pragma once

#include "ComponentSystem/UpdatableComponent.h"

#include "Physic/Physics.h"
#include "Physic/Transform.h"
#include "Inputs/Event.h"

#include "rttr/registration_friend.h"

#include "Debug/Log.h"

#include "DLL.h"

namespace Galatea
{
	class RigidBody : public UpdatableComponent
	{
	private:
		Physics*			physics;
		void*				physicsActor;

		bool				isOnContact;
		Transform			lastTransform;

		Vec3				gravity;
		Vec3				colliderScale;
		bool				isStatic;
		bool				isTrigger;
		EGeometryType		geometry;
		Vec3				freezePosition;
		Vec3				freezeRotation;
		float				staticFriction;
		float				dynamicFriction;
		float				restitution;
		float				mass;

	public:
		Event<RigidBody*>	onBeginOverlapEvent;
		Event<RigidBody*>	onEndOverlapEvent;

		GALATEA_API RigidBody()														noexcept;
		GALATEA_API ~RigidBody()													noexcept;

		void				Init(Physics& _physics)									noexcept;
		void				CreateNewPhysicsActor()									noexcept;
		GALATEA_API void	AddForce(const Vec3& _force, const EForceType& _type)	noexcept;
		GALATEA_API void	ResetVelocity()											noexcept;

		void				FixedUpdate()											noexcept override;
		void				SetOwnerTransform(const Vec3& _pos, const Quat& _rot)	noexcept;
		GALATEA_API void	Enable(const bool _enable)								noexcept;

		void				OnContact(RigidBody* _other)							noexcept;
		void				OnBeginOverlap(RigidBody* _other)						noexcept;
		void				OnEndOverlap(RigidBody* _other)							noexcept;

		void*								GetPhysicsActor()		const			noexcept { return physicsActor; }
		GALATEA_API const Vec3&				GetGravity()			const			noexcept { return gravity; }
		GALATEA_API const Vec3&				GetColliderScale()		const			noexcept { return colliderScale; }
		GALATEA_API const bool&				GetIsStatic()			const			noexcept { return isStatic; }
		GALATEA_API const bool&				GetIsTrigger()			const			noexcept { return isTrigger; }
		GALATEA_API const EGeometryType&	GetGeometry()			const			noexcept { return geometry; }
		GALATEA_API const Vec3&				GetFreezePosition()		const			noexcept { return freezePosition; }
		GALATEA_API const Vec3&				GetFreezeRotation()		const			noexcept { return freezeRotation; }
		GALATEA_API const float&			GetStaticFriction()		const			noexcept { return staticFriction; }
		GALATEA_API const float&			GetDynamicFriction()	const			noexcept { return dynamicFriction; }
		GALATEA_API const float&			GetRestitution()		const			noexcept { return restitution; }
		GALATEA_API const float&			GetMass()				const			noexcept { return mass; }

		GALATEA_API void	SetGravity(const Vec3& _gravity)						noexcept;
		GALATEA_API void	SetColliderScale(const Vec3& _scale)					noexcept;
		GALATEA_API void	SetIsStatic(const bool& _isStatic)						noexcept;
		GALATEA_API void	SetIsTrigger(const bool& _isTrigger)					noexcept;
		GALATEA_API void	SetGeometry(const EGeometryType& _geom)					noexcept;
		GALATEA_API void	SetFreezePosition(const Vec3& _freezePosition)			noexcept;
		GALATEA_API void	SetFreezeRotation(const Vec3& _freezeRotation)			noexcept;
		GALATEA_API void	SetStaticFriction(const float& _staticFriction)			noexcept;
		GALATEA_API void	SetDynamicFriction(const float& _dynamicFriction)		noexcept;
		GALATEA_API void	SetRestitution(const float& _restitution)				noexcept;
		GALATEA_API void	SetMass(const float& _mass)								noexcept;

		template<class Archive>
		void serialize(Archive& _ar) 
		{
			_ar(gravity, colliderScale, isStatic, isTrigger, freezePosition, freezeRotation, staticFriction, dynamicFriction, restitution, mass);
			_ar(geometry);
		}

		RTTR_ENABLE(UpdatableComponent)
		RTTR_REGISTRATION_FRIEND
	};
}
CEREAL_REGISTER_TYPE(Galatea::RigidBody);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Galatea::UpdatableComponent, Galatea::RigidBody)
