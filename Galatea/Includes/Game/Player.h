#pragma once

#include "ComponentSystem/UpdatableComponent.h"
#include "Maths/Vec3.h"
#include "Core/Camera/Camera.h"
#include "Cereal/types/polymorphic.hpp"
#include "Physic/RigidBody.h"

namespace GravityGun
{
	class Player : public Galatea::UpdatableComponent
	{
	private:
		#pragma region Variables

		Galatea::Vec3		direction;
		Galatea::Camera*	camera;
		Galatea::RigidBody* rigidBody;

		float				speed;
		float				fallingSpeed;
		float				jumpForce;

		bool isGrounded = false;
		
		#pragma endregion

	public:
		#pragma region Constructors/Destructor

		Player()	noexcept;
		~Player()	noexcept;

		#pragma endregion

		#pragma region Properties

		const Galatea::Camera&	GetCamera()			noexcept { return *camera; }
		const float&			GetFallingSpeed()	noexcept { return fallingSpeed; }
		
		#pragma endregion

		#pragma region Methods

		void	Init()							noexcept override;
		void	OnMoveFront(float _movement)	noexcept;
		void	OnMoveRight(float _movement)	noexcept;
		void	Update()						noexcept override;
		void	UpdateIsGrounded()				noexcept;
		void	OnJump()						noexcept;

		template<class Archive>
		void serialize(Archive& _ar)
		{}

		#pragma endregion

		#pragma region Operators
		#pragma endregion

		friend cereal::access;
	};
}
CEREAL_REGISTER_TYPE(GravityGun::Player);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Galatea::UpdatableComponent, GravityGun::Player)