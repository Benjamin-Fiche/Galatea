#include "Core/Render/Quad2D.h"
#include "Core/ResourcesManager.h"
#include "Libraries/GL/glew.h"
#include "Core/Render/RHI.h"

using namespace Galatea;

Quad2D::Quad2D() noexcept
{
	const float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	// positions   // texCoords
	-1.0f,  1.0f,  0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	 1.0f,  1.0f,  1.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f
	};

	VAO = RHI::CreateVAO(RHI::POSITION2D | RHI::UV, quadVertices, sizeof(quadVertices));
}

Quad2D* Quad2D::CreateQuad2D(const char* _texturePath) noexcept
{
	Quad2D* quad = new Quad2D;

	quad->textureName = _texturePath;
	quad->texture = ResourcesManager::GetResource<Texture>(_texturePath);

	return quad;
}

void Quad2D::RenderMesh(const Shader* _shader) const noexcept
{
	_shader->Use();
	
	_shader->SendMat4("TRS", owner->transform.GetMatrix());

	RHI::BindVAO(VAO);
	texture->Bind();
	RHI::DrawArray(0, 6);
}

void Quad2D::SetTexture(const char* _texturePath) noexcept
{
	textureName = _texturePath;
	texture = ResourcesManager::GetResource<Texture>(_texturePath);
}

std::string Quad2D::GetTextureName() const noexcept
{
	return textureName;
}