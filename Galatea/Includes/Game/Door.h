#pragma once

#include "Cereal/types/polymorphic.hpp"

#include "ComponentSystem/UpdatableComponent.h"
#include "ComponentSystem/GameObject.h"
#include "Physic/RigidBody.h"
#include "Sound/Sound.h"

namespace GravityGun
{
	class Door : public Galatea::UpdatableComponent
	{
	private:
		#pragma region Variables

		Galatea::GameObject*	doorLeaf;
		Galatea::RigidBody*		doorLeafRB;
		Galatea::RigidBody*		playerRB;
		Galatea::Sound*			doorOpenSound;
		Galatea::Sound*			doorCloseSound;

		Galatea::Vector3	LeafOpenedPosition;
		Galatea::Vector3	LeafClosedPosition;

		float				openingSpeed;
		bool				isOpen;

		#pragma endregion

	public:
		#pragma region Constructors/Destructor

		Door()	noexcept;
		~Door()	noexcept;

		#pragma endregion
		
		#pragma region Methods

		void	Init()		noexcept override;
		void	Update()	noexcept override;
		
		template<class Archive>
		void serialize(Archive& _ar)
		{}

		#pragma endregion

		friend cereal::access;
	};
}

CEREAL_REGISTER_TYPE(GravityGun::Door);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Galatea::UpdatableComponent, GravityGun::Door)