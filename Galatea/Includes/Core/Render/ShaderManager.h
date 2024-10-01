#pragma once

#include <unordered_map>

#include "Core/Render/Shader.h"
#include "Core/Render/UniformBuffer.h"

namespace Galatea
{
	class ShaderManager
	{
	private:
		std::unordered_map<const char*, UniformBuffer*>		uniformBufferList;
		std::unordered_map<const char*, Shader*>			shaderList;

		static ShaderManager								instance;

		static void	AddShader(Shader* _shader, const char* _name)													noexcept;

		ShaderManager()																								noexcept;
	public:
		~ShaderManager()																							noexcept;

		static void					Init()																			noexcept;
		template<typename Class>
		static void					CreateUniformBuffer(const char* _name, Class* _class)							noexcept
		{
			UniformBuffer* newUbo = new UniformBuffer;
			newUbo->InitUniformBuffer(_name, _class);
			instance.uniformBufferList[_name] = newUbo;
		}


		static const UniformBuffer*	GetUniformBuffer(const char* _name)												noexcept;
		static const Shader*		GetShaderProgram(const char* _name)												noexcept;

		static void					SendUniformBlock(const char* _name, const void* _class)							noexcept;
		static void					BindUniformBlockToShader(const char* _uniformName, const char* _shaderName)		noexcept;

		friend class ResourcesManager;
	};
}