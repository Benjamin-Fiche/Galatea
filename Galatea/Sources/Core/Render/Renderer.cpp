#include "Core/Render/Renderer.h"
#include "Core/Render/RHI.h"
#include "Core/ResourcesManager.h"
#include "Libraries/GL/glew.h"
#include "Core/Camera/Camera.h"
#include "Core/EModelCharacteristics.h"
#include "Core/Render/ShaderManager.h"
#include "Core/Scene.h"
#include "Core/Render/Mesh2D.h"
#include "Core/Render/Mesh.h"

#include "Libraries/GL/glew.h"

using namespace Galatea;

Renderer::Renderer() noexcept
{
	shaderDefault = ResourcesManager::GetResource<Shader>(ResourcesManager::CreateShaderResource("Resources/Shaders/DefaultVertexShader.vert", "Resources/Shaders/DefaultFragmentShader.frag", HAS_BUMP_TEXTURE));
	shaderSkybox = ResourcesManager::GetResource<Shader>(ResourcesManager::CreateShaderResource("Resources/Shaders/SkyboxVertexShader.vert", "Resources/Shaders/SkyboxFragmentShader.frag"));
	shaderFramebuffer = ResourcesManager::GetResource<Shader>(ResourcesManager::CreateShaderResource("Resources/Shaders/FramebufferVertexShader.vert", "Resources/Shaders/FramebufferFragmentShader.frag"));
	shader2D = ResourcesManager::GetResource<Shader>(ResourcesManager::CreateShaderResource("Resources/Shaders/2DVertexShader.vert", "Resources/Shaders/2DFragmentShader.frag"));
	shaderFont = ResourcesManager::GetResource<Shader>(ResourcesManager::CreateShaderResource("Resources/Shaders/FontVertexShader.vert", "Resources/Shaders/FontFragmentShader.frag"));
	shaderShadow = ResourcesManager::GetResource<Shader>(ResourcesManager::CreateShaderResource("Resources/Shaders/ShadowVertexShader.vert", "Resources/Shaders/ShadowFragmentShader.frag"));

	ShaderManager::CreateUniformBuffer<Mat4>("ViewProj", nullptr);
	ShaderManager::GetUniformBuffer("ViewProj")->BindShader(shaderDefault->GetShader());
	ShaderManager::GetUniformBuffer("ViewProj")->BindShader(shaderSkybox->GetShader());
	ShaderManager::CreateUniformBuffer<Mat4>("Orthogonal", nullptr);
	ShaderManager::GetUniformBuffer("Orthogonal")->BindShader(shader2D->GetShader());
	ShaderManager::GetUniformBuffer("Orthogonal")->BindShader(shaderFont->GetShader());

	skybox.InitFromMesh(ResourcesManager::GetResource<Mesh>(ResourcesManager::CreateMeshResource("Resources/Meshes/CubeNet.obj")));
	skybox.SetTexture(ResourcesManager::GetResource<Texture>(ResourcesManager::CreateTextureResource("Resources/Textures/sky.png")));

	shadowFramebuffer = new Framebuffer;

	const float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	// positions   // texCoords
	-1.0f,  1.0f,  0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	 1.0f,  1.0f,  1.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f
	};

	quadVAO = RHI::CreateVAO(RHI::POSITION2D | RHI::UV, quadVertices, sizeof(quadVertices));
}

Renderer::~Renderer() noexcept
{
	glDeleteVertexArrays(1, &quadVAO);
}

void Renderer::DrawShadow(const Framebuffer* _FBO) const noexcept
{
	///TODO
	/*shaderShadow->Use();
	shaderShadow->SendMat4("TRS", Mat4::CreateOrthogonalMatrix(-10.f, 10.f, ), true);

	shadowFramebuffer->UseFBO();

	glDrawBuffer(GL_NONE);

	//something

	glDrawBuffer(GL_FRONT);*/
}

void Renderer::DrawSceneRecursive(GameObject* _gameObject, const Mat4& TRS) const noexcept
{
	if (!_gameObject->isActive)
		return;

	Mat4 result = _gameObject->transform.globalMatrix = TRS * _gameObject->transform.GetMatrix();

	if (Mesh* mesh = _gameObject->GetComponent<Mesh>())
		if (mesh->isActive)
			mesh->RenderMesh(shaderDefault);
	
	for (auto it :_gameObject->GetChildren())
		DrawSceneRecursive(it.get(), result);
}

void Renderer::DrawSceneRecursive2D(GameObject* _gameObject, const Mat4& TRS) const noexcept
{
	if (!_gameObject->isActive)
		return;

	Mat4 result = _gameObject->transform.globalMatrix = TRS * _gameObject->transform.GetMatrix();

	if (Mesh2D* mesh = _gameObject->GetComponent<Mesh2D>())
		if (mesh->isActive)
			mesh->RenderMesh(shader2D);

	for (auto it : _gameObject->GetChildren())
		DrawSceneRecursive2D(it.get(), result);
}

void Renderer::DrawSkybox(const Vec3& _position) const noexcept
{
	shaderSkybox->Use();
	shaderSkybox->SendMat4("TRS", TRS::CreateTranslationMatrix(_position), true);

	skybox.RenderSkybox();
}

void Renderer::DrawPostProcess(const Framebuffer* _FBO) const noexcept
{

}

void Renderer::RenderScene() const noexcept
{
	Scene* scene = Scene::GetCurrentScene();
	glBindFramebuffer(GL_FRAMEBUFFER, scene->GetFinalFramebuffer()->GetFBO());
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Camera* currentCamera = scene->GetCurrentCamera();

	Mat4 projViewMatrix = currentCamera->GetViewMatrix() * scene->GetPerspectiveMatrix();

	DrawShadow(shadowFramebuffer);

	shaderDefault->Use();
	scene->GetComponentsManager()->SendLights(shaderDefault, currentCamera->GetOwner()->transform.GetMatrix() * Vec3 { 0.0, 0.0, 0.0 });

	ShaderManager::SendUniformBlock("ViewProj", &projViewMatrix);

	DrawSceneRecursive(scene->GetWorld(), Mat4::Identity());

	DrawSkybox(scene->GetCurrentCamera()->GetOwner()->GetWorldPosition());
	DrawPostProcess(scene->GetFinalFramebuffer());
	shader2D->Use();

	ShaderManager::SendUniformBlock("Orthogonal", &scene->GetOrthogonalMatrix());

	DrawSceneRecursive2D(scene->GetWorld2D(), Mat4::Identity());
}

void Renderer::RenderCameraEditor() const noexcept
{
	Scene* scene = Scene::GetCurrentScene();

	RHI::SetViewport(scene->GetSceneFramebuffer()->GetWidth(), scene->GetSceneFramebuffer()->GetHeight());

	shaderDefault->Use();
	Mat4 projViewMatrixEditor = scene->GetCameraInEditor().GetViewProjMatrix();

	ShaderManager::SendUniformBlock("ViewProj", &projViewMatrixEditor);

	glBindFramebuffer(GL_FRAMEBUFFER, scene->GetSceneFramebuffer()->GetFBO());
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	DrawSceneRecursive(scene->GetWorld(), Mat4::Identity());
	DrawSkybox(scene->GetCameraInEditor().GetPosition());
	DrawPostProcess(scene->GetSceneFramebuffer());

	glBindVertexArray(quadVAO);
	shaderFramebuffer->Use();
	scene->GetSceneFramebuffer()->UseFBO();

	RHI::SetViewport(scene->GetFinalFramebuffer()->GetWidth(), scene->GetFinalFramebuffer()->GetHeight());
}

void Renderer::DrawScene() const noexcept
{
	glBindVertexArray(quadVAO);
	shaderFramebuffer->Use();
	Scene::GetCurrentScene()->GetFinalFramebuffer()->UseFBO();
	/*glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_2D, _FBO->GetDepthSpencil());*/
	glDrawArrays(GL_TRIANGLES, 0, 6);
}
