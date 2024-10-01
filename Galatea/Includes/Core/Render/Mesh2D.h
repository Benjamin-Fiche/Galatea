#pragma once

#include "DLL.h"

#include "Cereal/types/polymorphic.hpp"
#include "rttr/registration_friend.h"

#include "ComponentSystem/Component.h"

namespace Galatea
{
	class Mesh2D : public Component
	{
		friend class cereal::access;

	protected:
		bool			useProportion{true};

		int				width{};
		int				height{};

		virtual void RenderMesh(const class Shader* _shader)			const	noexcept {};

		Mesh2D() noexcept;
	public:
		GALATEA_API virtual ~Mesh2D() noexcept {};


		#if defined(GALATEADLL_EXPORTS) || defined(_DEBUGEXE)

		template<class Archive>
		void serialize(Archive& _ar)
		{
			_ar(useProportion, width, height);
		}

		virtual void Resize(int _width, int _height) noexcept;

		#endif

		inline void	SetUseProportion(bool _useProportion)	noexcept { useProportion = _useProportion; }

		RTTR_ENABLE(Component)
		RTTR_REGISTRATION_FRIEND
		friend class Renderer;
	};
}

CEREAL_REGISTER_TYPE(Galatea::Mesh2D);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Galatea::Component, Galatea::Mesh2D)