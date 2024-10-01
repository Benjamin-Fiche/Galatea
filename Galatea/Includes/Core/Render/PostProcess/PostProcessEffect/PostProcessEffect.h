#pragma once

#include <vector>

#include "Core/Render/Framebuffer.h"
#include "Core/Render/PostProcess/PostProcessPass.h"

namespace Galatea
{
	class PostProcessEffect
	{
	protected:
		Framebuffer*					framebuffer;
		unsigned int					quadVAO;
		std::vector<class Mesh*>		meshToDraw;
	public:
		PostProcessEffect()														noexcept;

		void SendValueToShader(const PostProcessPass& _postProcessPass)	const	noexcept;
	};
}