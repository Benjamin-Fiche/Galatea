#pragma once

#include <vector>

#include "Physic/Transform.h"
#include "Core/Render/Texture.h"

namespace Galatea
{
	class Skybox
	{
	private:
		unsigned int				VAO;
		std::vector<unsigned int>	indicesCount;
		std::vector<unsigned int>	indicesIndex;
		static Texture*				texture;
	public:
		void					InitFromMesh(const class Mesh* _mesh)		noexcept;
		void					RenderSkybox()						const	noexcept;

		static void				SetTexture(Texture* _newTexture)			noexcept { texture = _newTexture; }
	};
}