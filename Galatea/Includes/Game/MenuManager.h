#pragma once

#include "Cereal/types/polymorphic.hpp"

#include "ComponentSystem/UpdatableComponent.h"

namespace GravityGun
{
	class MenuManager : public Galatea::UpdatableComponent
	{
	private:
#pragma region Variables
#pragma endregion

	public:
#pragma region Constructors/Destructor

		MenuManager()	noexcept;
		~MenuManager()	noexcept;

#pragma endregion

#pragma region Methods

		void	ChangeScene()	noexcept;

		template<class Archive>
		void serialize(Archive& _ar)
		{}

#pragma endregion

		friend cereal::access;
	};
}

CEREAL_REGISTER_TYPE(GravityGun::MenuManager);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Galatea::UpdatableComponent, GravityGun::MenuManager)