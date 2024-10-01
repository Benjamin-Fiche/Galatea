#pragma once

#include "DLL.h"

#include "Maths/Mat4.h"
#include "Maths/Vec3.h"
#include "Maths/Quaternion.h"
#include "ComponentSystem/UpdatableComponent.h"
#include "rttr/registration_friend.h"

namespace Galatea 
{
	GALATEA_API class Camera : public UpdatableComponent
	{
		friend cereal::access;

	private:
		Vector3	front;
		Vector3	right;
		Vector3	up;

	public:
		GALATEA_API Camera()					noexcept;
		GALATEA_API Camera(GameObject* _owner)	noexcept;
		~Camera()								noexcept = default;

		inline const Vec3&	GetFront()		const	noexcept { return front; };
		inline const Vec3&	GetRight()		const	noexcept { return right; };
		inline const Vec3&	GetUp()			const	noexcept { return up; };
		Mat4				GetViewMatrix()			noexcept;

		#if defined(GALATEADLL_EXPORTS) || defined(_DEBUGEXE)

		void	Update() noexcept override;
		
		/* function used by the cereal librarie to serialize */
		template<class Archive>
		void	serialize(Archive& _ar)
		{
			_ar(isActive, front, right, up);
		}

		#endif

		friend cereal::access;
		RTTR_ENABLE(Component)
		RTTR_REGISTRATION_FRIEND
	};
}

CEREAL_REGISTER_TYPE(Galatea::Camera);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Galatea::Component, Galatea::Camera)
