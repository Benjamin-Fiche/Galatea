#pragma once

#include "Cereal/types/polymorphic.hpp"
#include "rttr/registration_friend.h"

#include "Core/Render/Mesh2D.h"
#if defined(GALATEADLL_EXPORTS) || defined(_DEBUGEXE)
#include "Core/ResourcesManager.h"
#endif

namespace Galatea
{
	class Text2D : public Mesh2D
	{
		friend class cereal::access;

	private:
		unsigned int			VAO;
		unsigned int			VBO;
		Vec3					color;
		std::string				text;
		std::string				fontName;
		class Font*				font;

		void RenderMesh(const class Shader* _shader)	const	noexcept	override;

		Text2D() noexcept;
	public:

		GALATEA_API static Text2D*	CreateText(const char* _text, const char* _font, const Vec3& _color = Vec3{ 1, 1, 1 })	noexcept;

		GALATEA_API void			SetFont(const char* _newFontPath)														noexcept;
		GALATEA_API void			SetColor(const Vec3& _newColor)															noexcept;
		GALATEA_API void			SetText(const char* _newText)															noexcept;

		GALATEA_API const char*		GetFontName()																	const	noexcept;
		GALATEA_API const Vec3&		GetColor()																		const	noexcept;
		GALATEA_API const char*		GetText()																		const	noexcept;

		#if defined(GALATEADLL_EXPORTS) || defined(_DEBUGEXE)

		template<class Archive>
		void save(Archive& _ar) const
		{
			_ar(color, text, fontName);
		}

		template<class Archive>
		void load(Archive& _ar)
		{
			_ar(color, text, fontName);
			font = ResourcesManager::GetResource<Font>(fontName.c_str());
		}

		#endif
		RTTR_ENABLE(Mesh2D)
		RTTR_REGISTRATION_FRIEND
	};
}

namespace cereal
{
	template <class Archive>
	struct specialize<Archive, Galatea::Text2D, cereal::specialization::member_load_save> {};
	// cereal no longer has any ambiguity when serializing Mesh
}

CEREAL_REGISTER_TYPE(Galatea::Text2D);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Galatea::Mesh2D, Galatea::Text2D)