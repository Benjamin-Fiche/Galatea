#include "Core/Render/Texture.h"

#include "Core/Render/RHI.h"

using namespace Galatea;

Texture::Texture() noexcept
	: isCubeMap{ false }, textureID{ 0 }, name{}
{}

Texture::~Texture() noexcept
{

}

bool Texture::Load(const char* _texturePath, unsigned int _flag) noexcept
{
	isCubeMap = (_flag & RHI::CUBEMAP) == RHI::CUBEMAP;
	textureID = RHI::CreateTexture(_texturePath, _flag);
	name = _texturePath;

	return textureID != 0;
}

void Texture::Bind() const noexcept
{
	if (isCubeMap)
		RHI::BindTextureCubeMap(textureID);
	else
		RHI::BindTexture2D(textureID);
}