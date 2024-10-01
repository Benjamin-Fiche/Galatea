#pragma once

#include "Cereal/types/polymorphic.hpp"
#include "rttr/registration_friend.h"

#include "DLL.h"

#include "Core/Render/Mesh2D.h"
#if defined(GALATEADLL_EXPORTS) || defined(_DEBUGEXE)
#include "Core/ResourcesManager.h"
#endif

namespace Galatea
{
	class Quad2D : public Mesh2D
	{
		friend class cereal::access;
	private:
		unsigned int	VAO;
		std::string		textureName;
		class Texture*	texture;

		void RenderMesh(const class Shader* _shader)				const	noexcept	override;

		Quad2D()															noexcept;
	public:
		GALATEA_API ~Quad2D()												noexcept = default;

		GALATEA_API static Quad2D*	CreateQuad2D(const char* _texturePath)	noexcept;

		GALATEA_API void			SetTexture(const char* _texturePath)	noexcept;
		GALATEA_API std::string		GetTextureName()				const	noexcept;

		#if defined(GALATEADLL_EXPORTS) || defined(_DEBUGEXE)

		template<class Archive>
		void save(Archive& _ar) const
		{
			_ar(textureName);
		}

		template<class Archive>
		void load(Archive& _ar)
		{
			_ar(textureName);
			texture = ResourcesManager::GetResource<Texture>(textureName.c_str());
		}

		#endif

		RTTR_ENABLE(Mesh2D)
		RTTR_REGISTRATION_FRIEND
	};
}

namespace cereal
{
	template <class Archive>
	struct specialize<Archive, Galatea::Quad2D, cereal::specialization::member_load_save> {};
	// cereal no longer has any ambiguity when serializing Mesh
}

CEREAL_REGISTER_TYPE(Galatea::Quad2D);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Galatea::Mesh2D, Galatea::Quad2D)