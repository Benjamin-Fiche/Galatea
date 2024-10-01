#pragma once

#include "ComponentSystem/UpdatableComponent.h"
#include "Physic/RigidBody.h"
#include <iostream>

using namespace Galatea;

namespace GravityGun
{
	class WinTrigger : public UpdatableComponent
	{
	private:
		std::string		menuSceneName;
		RigidBody*		rigidBody;
	public:
		WinTrigger()							noexcept = default;
		WinTrigger(std::string _menuSceneName)	noexcept;
		~WinTrigger()							noexcept = default;

		void Init()								noexcept;	
		void OnBegin(RigidBody* _other)			noexcept;


		template<class Archive>
		void serialize(Archive& _ar)
		{
			_ar(menuSceneName);
		}

		friend cereal::access;
	};
}
CEREAL_REGISTER_TYPE(GravityGun::WinTrigger);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Galatea::UpdatableComponent, GravityGun::WinTrigger)