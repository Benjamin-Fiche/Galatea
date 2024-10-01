#pragma once

enum EModelCharacteristics : unsigned int
{
	HAS_NO_TEXTURE			= 0,
	HAS_EBO					= 1 << 0,
	HAS_DIFFUSE_TEXTURE		= 1 << 1,
	HAS_AMBIENT_TEXTURE		= 1 << 2,
	HAS_SPECULAR_TEXTURE	= 1 << 3,
	HAS_EMISSIVE_TEXTURE	= 1 << 4,
	HAS_BUMP_TEXTURE		= 1 << 5,
};