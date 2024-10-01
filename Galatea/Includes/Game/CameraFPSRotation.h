#pragma once

#include "ComponentSystem/UpdatableComponent.h"
#include "Core/Camera/Camera.h"
#include "Physic/Transform.h"
#include "Cereal/types/polymorphic.hpp"

namespace GravityGun	// TODO: choose a name
{
	class CameraFPSRotation : public Galatea::UpdatableComponent
	{
	private:
		#pragma region Variables

		Galatea::Transform*	trs;

		float				theta;
		float				phi;

		#pragma endregion

	public:
		#pragma region Variables

		float	mouseSensivity;
		float	gamepadSensivity;

		#pragma endregion

		#pragma region Constructors/Destructor

		CameraFPSRotation()								noexcept;
		CameraFPSRotation(const CameraFPSRotation& _c)	noexcept;
		CameraFPSRotation(CameraFPSRotation&& _c)		noexcept;
		~CameraFPSRotation()							noexcept;

		#pragma endregion

		#pragma region Methods

		void	Init()								noexcept override;
		void	OnMouseRotateX(float _rotation)		noexcept;
		void	OnMouseRotateY(float _rotation)		noexcept;
		void	OnGamepadRotateX(float _rotation)	noexcept;
		void	OnGamepadRotateY(float _rotation)	noexcept;

		void	Update()							noexcept override;

		template<class Archive>
		void serialize(Archive& _ar)
		{}

		#pragma endregion

		#pragma region Operators

		CameraFPSRotation&	operator=(const CameraFPSRotation& _c)	noexcept;
		CameraFPSRotation&	operator=(CameraFPSRotation && _c)		noexcept;

		#pragma endregion



		friend cereal::access;
	};
}
CEREAL_REGISTER_TYPE(GravityGun::CameraFPSRotation);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Galatea::UpdatableComponent, GravityGun::CameraFPSRotation)