#pragma once

#include "ComponentSystem/UpdatableComponent.h"
#include "Cereal/types/polymorphic.hpp"
#include "Sound/Sound.h"

namespace GravityGun
{
	class Gun : public Galatea::UpdatableComponent
	{
	private:
		Galatea::Sound* gravityChangeSound;
		Galatea::Sound* freezeSound;
		Galatea::Sound* unfreezeSound;
		
		bool			isRotating = false;
		float			advencement = 0;
		float			rotationSpeed = 0.3f;

	public:
		Gun()	noexcept;
		~Gun()	noexcept {};

		void	GetObjectGravity()	noexcept;
		void	SetObjectGravity()	noexcept;
		void	FreezeObject()		noexcept;

		void	Init()				noexcept override;
		void	Update()			noexcept override;
		void	SLerpRotation()		noexcept;

		template<class Archive>
		void serialize(Archive& _ar)
		{}

		friend cereal::access;
	};
}
CEREAL_REGISTER_TYPE(GravityGun::Gun);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Galatea::UpdatableComponent, GravityGun::Gun)