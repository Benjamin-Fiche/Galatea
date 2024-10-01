#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>

#include "Core/Render/Font.h"
#include "Libraries/GL/glew.h"

using namespace Galatea;

Font::~Font() noexcept
{
	for (auto it : characters)
	{
		glDeleteTextures(1, &it.second->textureID);
		delete it.second;
	}
}


bool Font::Load(const char* _fontPath, unsigned int _flag) noexcept
{
	name = _fontPath;
	FT_Library  ftlib;

	if (FT_Init_FreeType(&ftlib))
		return false;

	FT_Face	face;
	if (FT_New_Face(ftlib, _fontPath, 0, &face))
		return false;

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte character{ 0 }; character < 128; character++)
	{
		if (FT_Load_Char(face, character, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Now store character for later use
		characters.insert(std::make_pair(character, new Character{
			texture,
			static_cast<float>(face->glyph->bitmap.width) / 1000.f, static_cast<float>(face->glyph->bitmap.rows) / 1000.f,
			static_cast<float>(face->glyph->bitmap_left) / 1000.f, static_cast<float>(face->glyph->bitmap_top) / 1000.f,
			static_cast<float>(face->glyph->advance.x >> 6) / 1000.f
			}));
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	FT_Done_Face(face);
	FT_Done_FreeType(ftlib);
	return true;
}