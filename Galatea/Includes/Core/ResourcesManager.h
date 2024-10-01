#pragma once

#include <unordered_map>

#include "DLL.h"

#include "Core/Render/Font.h"
#include "Core/Render/Model.h"
#include "Core/Render/Texture.h"
#include "Core/Render/Shader.h"

#define MISSING_TEXTURE "Resources/Textures/MissingTexture.jpg"
#define MISSING_OBJECT "Resources/Meshes/Blender/Cube/Cube.obj Resources/Textures/MissingTexture.jpg"
#define MISSING_SHADER "Resources/Shaders/DefaultVertexShader.vs Resources/Shaders/DefaultFragmentShader.fs"
#define MISSING_FONT "Resources/Fonts/Arial.ttf"
#define CUBE_OBJ "Resources/Meshes/Blender/Cube/Cube.obj"
#define SPHERE_OBJ "Resources/Meshes/Blender/Sphere/Sphere.obj"
#define DEFAULT_NORMAL_MAP "Resources/Textures/NormalMap/defaultNormalMap.png"

namespace Galatea
{
	class GALATEA_API ResourcesManager	/* TODO: regarder ce qu'on doit passer en dll */
	{
	private:
		std::unordered_map<std::string, Font*>			fontResources;
		std::unordered_map<std::string, Model*>			modelResources;
		std::unordered_map<std::string, Texture*>		textureResources;
		std::unordered_map<std::string, Shader*>		shaderResources;
		
		static ResourcesManager instance;

		ResourcesManager() 																														noexcept;
	public:
		~ResourcesManager()																														noexcept;

		static void				Init()																											noexcept;

		/*
			return the name to use to get the resource with GetResource
		*/
		static const char*		CreateFontResource(const char* _name, unsigned int _flag = 0u)													noexcept;
		
		/*
			if _customTexture different of nullptr, force obj to take only this texture

			return the name to use to get the resource with GetResource
		*/
		static const char*		CreateMeshResource(const char* _name, const char* _customTexture = nullptr, unsigned int _flag = 0u)			noexcept;

		/*
			return the name to use to get the resource with GetResource
		*/
		static const char*		CreateTextureResource(const char* _name, unsigned int _flag = 0u)												noexcept;

		/*
			return the name to use to get the resource with GetResource
		*/
		static const char*		CreateShaderResource(const char* _vertexShaderPath, const char* _fragmentShaderPath, unsigned int _flag = 0u)	noexcept;

		template<class T>
		static T*				GetResource(const char* _name)																					noexcept
		{
			return nullptr;
		}

		template<>
		static Font*			GetResource<Font>(const char* _name)																			noexcept
		{
			Font* returnFont = instance.fontResources[_name];
			if (returnFont == nullptr)
			{
				returnFont = new Font;
				if (!returnFont->Load(_name))
				{
					delete returnFont;
					instance.fontResources[_name] = nullptr;
					return instance.fontResources[MISSING_FONT];
				}
				instance.fontResources[_name] = returnFont;
			}
			return returnFont;
		}

		template<>
		static Mesh*			GetResource<Mesh>(const char* _name)																			noexcept
		{
			Model* returnModel = instance.modelResources[_name];
			if (returnModel == nullptr)
			{
				returnModel = new Model;
				if (!returnModel->Load(_name))
				{
					delete returnModel;
					instance.modelResources[_name] = nullptr;
					return instance.modelResources[MISSING_OBJECT]->CreateMeshFromModel();
				}
				instance.modelResources[_name] = returnModel;
			}
			return returnModel->CreateMeshFromModel();
		}

		template<>
		static Texture*			GetResource<Texture>(const char* _name)																			noexcept
		{
			Texture* returnTexture = instance.textureResources[_name];
			if (returnTexture == nullptr)
			{
				returnTexture = new Texture;
				if (!returnTexture->Load(_name))
				{
					delete returnTexture;
					instance.textureResources[_name] = nullptr;
					return instance.textureResources[MISSING_TEXTURE];
				}
				instance.textureResources[_name] = returnTexture;
			}
			return returnTexture;
		}

		template<>
		static Shader*			GetResource<Shader>(const char* _name)																			 noexcept
		{
			Shader* returnShader = instance.shaderResources[_name];
			if (returnShader == nullptr)
			{
				return instance.shaderResources[MISSING_SHADER];
			}
			return returnShader;
		}
	};
}
