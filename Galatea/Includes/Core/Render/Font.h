#pragma once

#include <iostream>
#include <map>

namespace Galatea
{
	class Font
	{
	public:
		struct Character {
			unsigned	textureID;		// ID handle of the glyph texture
			float		sizeX;			// SizeX of glyph
			float		sizeY;			// SizeY of glyph
			float		bearingX; 		// OffsetX from baseline to left/top of glyph
			float		bearingY; 		// OffsetY from baseline to left/top of glyph
			float		advance;		// Horizontal offset to advance to next glyph
		};

	private:
		std::map<char, Character*>				characters;
		
		std::string								name;

		bool	Load(const char* _fontPath, unsigned int _flag = 0u)		noexcept;

		Font() = default;
	public:
		~Font()																noexcept;

		const char* GetName()										const	noexcept { return name.c_str(); }
		auto&		GetCharacters()									const	noexcept { return characters; }

		friend class ResourcesManager;
	};
}