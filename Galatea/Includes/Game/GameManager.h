#pragma once

#include "Cereal/types/polymorphic.hpp"

#include "ComponentSystem/UpdatableComponent.h"
#include "Sound/Sound.h"

namespace GravityGun
{
	class GameManager : public Galatea::UpdatableComponent
	{
	private:
		#pragma region Variables

		Galatea::Sound*	backgroundMusic;

		#pragma endregion

	public:
		#pragma region Constructors/Destructor

		GameManager()	noexcept;
		~GameManager()	noexcept;

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

CEREAL_REGISTER_TYPE(GravityGun::GameManager);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Galatea::UpdatableComponent, GravityGun::GameManager)