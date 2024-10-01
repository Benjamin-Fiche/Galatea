#pragma once

#include "PxPhysicsAPI.h"
#include "Physic/Transform.h"
#include "Physic/SimulationEventCallback.h"

using namespace physx;

namespace Galatea
{
	class RigidBody;

	enum class EGeometryType
	{
		BOX,
		SPHERE,
		CAPSULE
	};

	enum class EForceType
	{
		ACCELERATION,
		FORCE,
		IMPULSE,
		VELOCITY_CHANGE
	};

	class Physics
	{
	private:
		PxDefaultAllocator			allocator;
		PxDefaultErrorCallback		errorCallback;

		PxFoundation*				foundation;
		PxPvd*						pvd;
		PxPhysics*					physics;
		PxDefaultCpuDispatcher*		dispatcher;

		SimulationEventCallback		simulationEventCallback;
		PxScene*					currentScene;
		std::vector<PxScene*>		scenes;

		PxGeometry* CreateGeometry(const EGeometryType& _geomType, const Vec3& _colliderScale)	noexcept;
		PxMaterial*	GetExistingMaterial(const Vec3& _matValue)									noexcept;

	public:
		Physics();
		~Physics();

		void					Init()																						noexcept;
		void					Destroy()																					noexcept;

		void					CreateScene()																				noexcept;
		void					CreateObject(RigidBody& _rigidBody, void*& _actor)											noexcept;

		void					FixedUpdate()																				noexcept;
		void					SetActiveActorsPos()																		noexcept;

		bool					SetCurrentScene(unsigned int _sceneID)														noexcept;
		void					RemoveScene(unsigned int _sceneID)															noexcept;

		void					EnableActor(void* _actor, const bool _enable)												noexcept;
		void					SetActorPos(void* _actor, const Vec3& _pos, const Quat& _rot)								noexcept;
		void					SetActorGeometry(void* _actor, const EGeometryType& _geom, const Vec3& _colliderScale)		noexcept;
		void					SetActorLockFlags(void* _actor, const Vec3& _freezePosition, const Vec3& _freezeRotation)	noexcept;
		void					SetActorMaterial(void* _actor, const float _staticFriction, 
												const float _dynamicFriction, const float _restitution)						noexcept;
		void					SetActorMass(void* _actor, const float _mass)												noexcept;
		void					SetShapeFlags(void* _actor, const bool _isTrigger)											noexcept;

		void					AddForce(void* _actor, const Vec3& _force, const EForceType& _type)							noexcept;
		void					ResetVelocity(void* _actor)																	noexcept;
		static RigidBody&		Raycast(const Vec3& _origin, const Vec3& _dir, const float _maxDist)						noexcept;

	};
}
