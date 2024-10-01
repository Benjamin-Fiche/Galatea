#include "Core/Render/Text2D.h"
#include "Core/ResourcesManager.h"
#include "Core/Render/Shader.h"
#include "Core/Scene.h"

#include "Libraries/GL/glew.h"

using namespace Galatea;

Text2D::Text2D() noexcept
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Text2D* Text2D::CreateText(const char* _text, const char* _fontPath, const Vec3& _color) noexcept
{
	Text2D* text = new Text2D;

	text->color = _color;
	text->text = _text;
	text->font = ResourcesManager::GetResource<Font>(_fontPath);
	text->fontName = text->font->GetName();

	return text;
}

void Text2D::RenderMesh(const Shader*) const noexcept
{
	Shader* shader = ResourcesManager::GetResource<Shader>("Resources/Shaders/FontVertexShader.vert Resources/Shaders/FontFragmentShader.frag");
	// Activate corresponding render state
	shader->Use();
	shader->SendVec3("textColor", color);
	
	glBindVertexArray(VAO);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	float scaleX{ owner->transform.scale.x };
	float scaleY{ owner->transform.scale.y };
	float x{ owner->transform.position.x };
	float y{ owner->transform.position.y };

	const std::map<char, Font::Character*>& characs{ font->GetCharacters() };

	for (char it : text)
	{
		const Font::Character* charac{ characs.at(it) };
		if (it == ' ')
		{
			x += charac->advance * scaleX;
			continue;
		}

		float xpos{ x + (charac->bearingX * scaleX) };
		float ypos{ y - ((charac->sizeY - charac->bearingY) * scaleY) };

		float w{ charac->sizeX * scaleX };
		float h{ charac->sizeY * scaleY };

		const float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
											 
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f }
		};

		glBindTexture(GL_TEXTURE_2D, charac->textureID);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		x += charac->advance * scaleX;
	}

	glBindVertexArray(0);
}

void Text2D::SetFont(const char* _newFontPath) noexcept
{
	font = ResourcesManager::GetResource<Font>(_newFontPath);
	fontName = font->GetName();
}
void Text2D::SetColor(const Vec3& _newColor) noexcept
{
	color = _newColor;
}
void Text2D::SetText(const char* _newText) noexcept
{
	text = _newText;
}

const char* Text2D::GetFontName() const noexcept
{
	return fontName.c_str();
}
const Vec3& Text2D::GetColor() const noexcept
{
	return color;
}
const char* Text2D::GetText() const noexcept
{
	return text.c_str();
}