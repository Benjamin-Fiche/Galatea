#pragma once

#include <unordered_map>

#include "Core/Render/PostProcess/PostProcessEffect/PostProcessEffect.h"

namespace Galatea
{
	class PostProcessManager
	{
	private:
		std::unordered_map<unsigned char, PostProcessEffect*>	postProcessEffectList;

		static PostProcessManager instance;

		PostProcessManager()					noexcept;
	public:

		static void					AddPostProcessEffect(unsigned char _flagPostProcess, const char* _vertexShaderPath, const char* _fragmentShaderPath, PostProcessEffect* _newPostProcessEffect)	noexcept;
		static void					AddMeshToPostProcessEffect(class Mesh* _mesh, unsigned char _flagPostProcess)																					noexcept;
		static PostProcessEffect*	GetPostProcessEffect(unsigned char _flagPostProcess)																											noexcept;
	};
}