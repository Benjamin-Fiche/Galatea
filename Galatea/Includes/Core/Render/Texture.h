#pragma once

#include "DLL.h"

#include <string>
#include "rttr/registration_friend.h"

namespace Galatea
{
	class GALATEA_API Texture
	{
	private:
		bool			isCubeMap;
		unsigned int	textureID;
		std::string		name;

		Texture()																		noexcept;

		bool					Load(const char* _texturePath, unsigned int _flag = 0)	noexcept;

	public:
		~Texture()																		noexcept;

		unsigned int			GetTextureID()									const	noexcept { return textureID; }
		const std::string&		GetName()										const	noexcept { return name; }
		void					Bind()											const	noexcept;

		friend class ResourcesManager;
		RTTR_REGISTRATION_FRIEND
	};

}