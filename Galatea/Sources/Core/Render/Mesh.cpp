#include <iostream>

#include "Core/Render/Mesh.h"
#include "Core/Render/RHI.h"
#include "Core/ResourcesManager.h"
#include "ComponentSystem/GameObject.h"
#include "Core/Render/Shader.h"
#include "Core/EModelCharacteristics.h"
#include "Core/Render/Material.h"

using namespace Galatea;

Mesh::Mesh(GameObject* _owner)  noexcept 
	: Component{ _owner }
{}

Mesh::~Mesh() noexcept
{
	for (auto it : materials)
		delete it;
}

Mesh* Mesh::CreateCube(std::string _texture) noexcept
{
	return ResourcesManager::GetResource<Mesh>(ResourcesManager::CreateMeshResource(CUBE_OBJ, _texture.c_str()));
}

Mesh* Mesh::CreateSphere(std::string _texture) noexcept
{
	return ResourcesManager::GetResource<Mesh>(ResourcesManager::CreateMeshResource(SPHERE_OBJ, _texture.c_str()));
}

void Mesh::RenderMesh(const Shader* _shader) const noexcept
{
	RHI::BindVAO(VAO);

	_shader->SendMat4("TRS", owner->transform.globalMatrix, true);

	if (flagCharacteristics & HAS_EBO)
	{
		for (unsigned int i = 0; i < indicesCount.size(); ++i)
		{
			materials[i]->BindMaterial(_shader);
			RHI::DrawElements(indicesCount[i], (void*)(indicesIndex[i] * sizeof(unsigned int)));
		}
	}
	else if (materials.size() != 0)
	{
		materials[0]->BindMaterial(_shader);
		RHI::DrawArray(0, indicesIndex[0]);
	}
}

void Mesh::AddPostProcessEffect(unsigned char _postProcessIndex) noexcept
{
	//TODO add postProcessEffect
}

void Mesh::RemovePostProcessEffect(unsigned char _postProcessIndex) noexcept
{
	//TODO remove postProcessEffect
}

unsigned char Mesh::GetPostProcessFlag() noexcept
{
	return flagPostProcess;
}