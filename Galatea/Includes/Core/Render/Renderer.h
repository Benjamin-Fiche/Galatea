#pragma once

#include "Core/Render/Framebuffer.h"
#include "Core/Render/Skybox.h"

#include "Core/Render/UniformBuffer.h"

namespace Galatea
{
	class Shader;

	class Renderer
	{
	private:
		unsigned int			quadVAO;

		Shader*					shaderDefault;
		Shader*					shaderFramebuffer;
		Shader*					shaderSkybox;
		Shader*					shader2D;
		Shader*					shaderFont;
		Shader*					shaderShadow;
		Skybox					skybox;

		Framebuffer*			shadowFramebuffer;

		void					DrawShadow(const Framebuffer* _FBO)										const	noexcept;
		void					DrawSceneRecursive(class GameObject* go, const struct Mat4& TRS)		const	noexcept;
		void					DrawSceneRecursive2D(class GameObject* go, const struct Mat4& TRS)		const	noexcept;
		void					DrawSkybox(const struct Vec3& _position)								const	noexcept;
		void					DrawPostProcess(const Framebuffer* _FBO)								const	noexcept;
	public:
		Renderer()																								noexcept;
		~Renderer()																								noexcept;

		void					RenderScene()															const	noexcept;
		void					RenderCameraEditor()													const	noexcept;
		void					DrawScene()																const	noexcept;
	};
}