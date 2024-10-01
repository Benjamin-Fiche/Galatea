#pragma once

#include "Cereal/types/polymorphic.hpp"
#include "ComponentSystem/UpdatableComponent.h"
#include "Camera.h"
#include "Physic/Transform.h"

namespace Galatea
{
	class CameraFreeFlyMovement : public UpdatableComponent
	{
	private:
		#pragma region Variables

		Camera*		camera;
		Transform*	trs;

		float		theta;
		float		phi;

		#pragma endregion

	public:
		#pragma region Variables

		float	speed;
		float	sensivity;

		#pragma endregion

		#pragma region Constructors/Destructor

		CameraFreeFlyMovement()									noexcept;
		/*CameraFreeFlyMovement(const CameraFreeFlyMovement& _c)	noexcept;
		CameraFreeFlyMovement(CameraFreeFlyMovement&& _c)		noexcept;*/
		~CameraFreeFlyMovement()								noexcept;

		#pragma endregion

		#pragma region Properties
		#pragma endregion

		#pragma region Methods

		#if defined(GALATEADLL_EXPORTS) || defined(_DEBUGEXE)

		void	Init()		noexcept override;
		void	Update()	noexcept override;

		template<class Archive>
		void	serialize(Archive& _ar)
		{
			_ar(isActive, theta, phi, speed, sensivity);
		}

		#endif

		#pragma endregion

		#pragma region Operators

		CameraFreeFlyMovement& operator=(const CameraFreeFlyMovement& _c)	noexcept;
		CameraFreeFlyMovement& operator=(CameraFreeFlyMovement&& _c)		noexcept;

		#pragma endregion

		friend cereal::access;
		RTTR_ENABLE(UpdatableComponent)
		RTTR_REGISTRATION_FRIEND
	};
}

CEREAL_REGISTER_TYPE(Galatea::CameraFreeFlyMovement);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Galatea::UpdatableComponent, Galatea::CameraFreeFlyMovement)
