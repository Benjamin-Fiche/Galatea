#include "Core/Render/Skybox.h"
#include "Core/Render/RHI.h"
#include "Core/Render/Mesh.h"
#include "Core/Render/Material.h"

using namespace Galatea;

Texture* Skybox::texture;

void Skybox::InitFromMesh(const Mesh* _mesh) noexcept
{
	VAO = _mesh->GetVAO();
	indicesCount = _mesh->GetIndicesCount();
	indicesIndex = _mesh->GetIndicesIndex();
	texture = _mesh->GetMaterial(0)->diffuseTexture;
}

void Skybox::RenderSkybox() const noexcept
{
	RHI::BindVAO(VAO);

	RHI::SetActiveTexture(0);
	texture->Bind();
	RHI::DrawElements(indicesCount[0], (void*)(indicesIndex[0] * sizeof(unsigned int)));
}