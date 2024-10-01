#include "Core/Render/ShaderManager.h"

using namespace Galatea;

ShaderManager ShaderManager::instance;

ShaderManager::ShaderManager() noexcept
{

}

ShaderManager::~ShaderManager() noexcept
{
	for (auto it = uniformBufferList.begin(); it != uniformBufferList.end(); ++it)
		delete it->second;
}

void ShaderManager::AddShader(Shader* _shader, const char* _name) noexcept
{
	instance.shaderList[_name] = _shader;
}

const UniformBuffer* ShaderManager::GetUniformBuffer(const char* _name) noexcept
{
	return instance.uniformBufferList[_name];
}

const Shader* ShaderManager::GetShaderProgram(const char* _name) noexcept
{
	return instance.shaderList[_name];
}

void ShaderManager::SendUniformBlock(const char* _name, const void* _class) noexcept
{
	instance.uniformBufferList[_name]->SendToGPU(_class);
}

void ShaderManager::BindUniformBlockToShader(const char* _uniformName, const char* _shaderName) noexcept
{
	instance.uniformBufferList[_uniformName]->BindShader(instance.shaderList[_shaderName]->GetShader());
}
