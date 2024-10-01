#pragma once

namespace Galatea
{
	namespace RHI
	{
		enum RHIOption
		{
			NONE					= 0x0000,
			POSITION2D				= 0x0001,
			POSITION3D				= 0x0002,
			UV						= 0x0004,
			NORMAL					= 0x0008,
			TANGENT					= 0x0010,
			FLIP_TEXTURE_ON_LOAD	= 0x0020,
			CUBEMAP					= 0x0040,
			ALPHA_TEST				= 0x0BC0,
			BLEND					= 0x0BE2,
			CULL_FACE				= 0x0B44,
			DEPTH_TEST				= 0x0B71,
			MULTISAMPLE				= 0x809D,
			STENCIL_TEST			= 0x0B90,
			COLOR_BUFFER_BIT		= 0x4000,
			DEPTH_BUFFER_BIT		= 0x0100,
			STENCIL_BUFFER_BIT		= 0x0400,
		};

		bool			Init()				noexcept;
		void			EnableDebug()		noexcept;

		unsigned int	CreateVAO(unsigned int _flag, const void* _verticesBuffer, unsigned int _verticesBufferSize, const void* _indicesBuffer = nullptr, unsigned int _indicesBufferSize = 0, bool _generateEBO = false) noexcept;
		unsigned int	CreateShader(const char* _shader, unsigned int _shaderType)													noexcept;
		unsigned int	CreateShaderProgram(const char* _vertexShaderPath, const char* fragmentShaderPath)							noexcept;
		unsigned int	CreateTexture(const char* _texturePath, unsigned int _flag = 0)												noexcept;
		unsigned int	CreateTextureFromData(int _width, int _height, void* _data, const char* _name, unsigned int _flag)			noexcept;

		void			BindTexture2D(unsigned int _texture)																		noexcept;
		void			BindTextureCubeMap(unsigned int _texture)																	noexcept;
		void			BindFrameBuffer(unsigned int _framebuffer)																	noexcept;
		void			BindVAO(unsigned int _VAO)																					noexcept;

		void			SetViewport(int _width, int _height)																		noexcept;
		void			SetActiveTexture(int _index)																				noexcept;

		void			Enable(bool _value, unsigned int _flag)																		noexcept;
		void			EnableDepthMask(bool _value)																				noexcept;

		void			UseProgram(unsigned int _program)																			noexcept;

		void			DeleteProgram(unsigned int _program)																		noexcept;

		unsigned int	GetLocation(unsigned int _program, const char* _name)														noexcept;
		unsigned int	GetAttribute(unsigned int _program, const char* _name)														noexcept;


		void			SendBool(unsigned int _location, const bool _value)															noexcept;
		void			SendInt(unsigned int _location, const int _value)															noexcept;
		void			SendUint(unsigned int _location, const unsigned int _value)													noexcept;
		void			SendFloat(unsigned int _location, const float _value)														noexcept;
		void			SendFloat2(unsigned int _location, const float _value[2])													noexcept;
		void			SendFloat3(unsigned int _location, const float _value[3])													noexcept;
		void			SendFloat4(unsigned int _location, const float _value[4])													noexcept;
		void			SendMatrix3(unsigned int _location, const float _matrix[9], bool _transpose = false)						noexcept;
		void			SendMatrix4(unsigned int _location, const float _matrix[16], bool _transpose = false)						noexcept;

		void			Clear(unsigned int _flag)																					noexcept;
		void			ClearColor(const float _value[4])																			noexcept;

		void			DrawArray(unsigned int _startIndex, unsigned int _count)													noexcept;

		/*
			_count = Numbers of element in indices's list
			_indices = If VAO has been create with EBO, indices = 0,
			else give indices list
		*/
		void			DrawElements(unsigned int _count, const void* _indices = 0)													noexcept;
		void			DrawRangeElements(unsigned int _start, unsigned int _end, const void* _indices = 0)							noexcept;
	};
}