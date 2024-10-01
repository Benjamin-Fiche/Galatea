#include "Core/Render/PostProcess/PostProcessEffect/PostProcessEffect.h"
#include "Core/Render/RHI.h"
#include "Core/Render/Mesh.h"

using namespace Galatea;

PostProcessEffect::PostProcessEffect() noexcept
{
	framebuffer = new Framebuffer;

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