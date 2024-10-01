#pragma once

#include "DLL.h"

namespace Galatea
{
	class Shader;

	class Framebuffer
	{
		private:
			unsigned int	FBO;
			unsigned int	depthBuffer;
			unsigned int	textureColorBuffer;

			int				width;
			int				height;

			void			CreateFBO(int _width, int _height)		noexcept;
		public:
			Framebuffer()											noexcept;
			~Framebuffer()											noexcept;

			unsigned int	GetDepthBuffer()					const	noexcept { return depthBuffer; }
			unsigned int	GetColorBuffer()					const	noexcept { return textureColorBuffer; }
			unsigned int	GetFBO()							const	noexcept { return FBO; }
			unsigned int	GetWidth()							const	noexcept { return width; };
			unsigned int	GetHeight()							const	noexcept { return height; };
			
			void				UseFBO()						const	noexcept;
			GALATEA_API void	Resize(int _width, int height)			noexcept;
	};
}