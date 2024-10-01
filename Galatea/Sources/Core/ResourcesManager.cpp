#include "Core/ResourcesManager.h"
#include "Core/Render/Mesh.h"
#include "Core/Render/ShaderManager.h"

using namespace Galatea;

ResourcesManager ResourcesManager::instance;

ResourcesManager::ResourcesManager() noexcept
{
}

ResourcesManager::~ResourcesManager() noexcept
{
	for (auto it = fontResources.begin(); it != fontResources.end(); ++it)
		delete it->second;
	for (auto it = modelResources.begin(); it != modelResources.end(); ++it)
		delete it->second;
	for (auto it = textureResources.begin(); it != textureResources.end(); ++it)
		delete it->second;
	for (auto it = shaderResources.begin(); it != shaderResources.end(); ++it)
		delete it->second;
}

void ResourcesManager::Init() noexcept
{
	ResourcesManager::CreateTextureResource(MISSING_TEXTURE);
	ResourcesManager::CreateTextureResource(DEFAULT_NORMAL_MAP);
	ResourcesManager::CreateMeshResource(CUBE_OBJ, MISSING_TEXTURE);
	ResourcesManager::CreateFontResource(MISSING_FONT);
}

const char* ResourcesManager::CreateFontResource(const char* _name, unsigned int _flag)		noexcept
{
	if (instance.fontResources[_name] == nullptr)
	{
		Font* returnFont = new Font;
		if (!returnFont->Load(_name, _flag))
		{
			delete returnFont;
			return nullptr;
		}

		instance.fontResources[_name] = returnFont;
		return returnFont->name.c_str();
	}
	return nullptr;
}
/*
	if _customTexture different of nullptr, force obj to take only this texture

	return the name to use to get the resource with GetResource
*/
const char* ResourcesManager::CreateMeshResource(const char* _name, const char* _customTexture, unsigned int _flag)		noexcept
{
	std::string newName = _name;
	if (_customTexture != nullptr)
		newName = newName + " " + _customTexture;
	if (instance.modelResources.find(newName) == instance.modelResources.end())
	{
		Model* returnModel = new Model;
		if (!returnModel->Load(_name, _customTexture, _flag))
		{
			delete returnModel;
			return nullptr;
		}
		instance.modelResources[newName] = returnModel;

		return returnModel->name.c_str();
	}
	return instance.modelResources[newName]->name.c_str();
}

/*
	return the name to use to get the resource with GetResource
*/
const char* ResourcesManager::CreateTextureResource(const char* _name, unsigned int _flag)	noexcept
{
	if (instance.textureResources[_name] == nullptr)
	{
		Texture* returnTexture = new Texture;
		if (!returnTexture->Load(_name, _flag))
		{
			delete returnTexture;
			return nullptr;
		}
		instance.textureResources[_name] = returnTexture;
		return _name;
	}
	return _name;
}

/*
	return the name to use to get the resource with GetResource
*/
const char* ResourcesManager::CreateShaderResource(const char* _vertexShaderPath, const char* _fragmentShaderPath, unsigned int _flag) noexcept
{
	std::string name = _vertexShaderPath;
	name += " ";
	name += _fragmentShaderPath;
	if (instance.shaderResources.find(name) == instance.shaderResources.end())
	{
		Shader* returnShader = new Shader;
		if (!returnShader->Load(_vertexShaderPath, _fragmentShaderPath, _flag))
		{
			delete returnShader;
			return nullptr;
		}

		instance.shaderResources[name] = returnShader;
		ShaderManager::AddShader(instance.shaderResources[name], instance.shaderResources[name]->GetName().c_str());

		return returnShader->GetName().c_str();
	}
	return instance.shaderResources[name]->GetName().c_str();
}