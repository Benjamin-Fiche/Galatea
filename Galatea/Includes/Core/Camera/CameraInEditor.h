#pragma once

#include "DLL.h"

#include "Maths/Mat4.h"
#include "Physic/Transform.h"

namespace Galatea
{
	class CameraInEditor
	{
	private:
		float		theta{ 0.0f };
		float		phi{ 0.0f };
		float		speed{ 10.f };
		float		sensivity{ 10.f };

		Transform	trs{};

		Vec3		front;
		Vec3		right;
		Vec3		up;
	public:
		Mat4	projectionMatrix = Mat4::CreatePerspectiveMatrix(1024, 800, 0.001f, 1000, 60);;
		#if defined(GALATEADLL_EXPORTS) || defined(_DEBUGEXE)

		CameraInEditor()	noexcept = default;
		~CameraInEditor()	noexcept = default;

		void				Update()					noexcept;
		Mat4				GetViewProjMatrix()	const	noexcept;
		const Vec3&			GetPosition()		const	noexcept;

		/* function used by the cereal library to serialize */
		//template<class Archive>
		//void	serialize(Archive& _ar)
		//{
		//	_ar(theta, phi, speed, sensivity, trs, front, right, up);
		//}

		#endif

		GALATEA_API void	ResetRotation()			noexcept;
	};
}