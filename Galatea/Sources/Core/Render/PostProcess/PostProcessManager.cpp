#include "Core/Render/PostProcess/PostProcessManager.h"

using namespace Galatea;

PostProcessManager PostProcessManager::instance;

PostProcessManager::PostProcessManager() noexcept
{

}

void PostProcessManager::AddPostProcessEffect(unsigned char _flagPostProcess, const char* _vertexShaderPath, const char* _fragmentShaderPath, PostProcessEffect* _newPostProcessEffect) noexcept
{

}

void PostProcessManager::AddMeshToPostProcessEffect(class Mesh* _mesh, unsigned char _flagPostProcess) noexcept
{

}

PostProcessEffect* PostProcessManager::GetPostProcessEffect(unsigned char _flagPostProcess) noexcept
{
	return instance.postProcessEffectList[_flagPostProcess];
}