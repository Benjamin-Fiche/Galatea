#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Core/Render/RHI.h"

#include "GL/glew.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace Galatea;

bool RHI::Init() noexcept
{
	glewInit();		/// OpenGL Init

	//glEnable(GL_MULTISAMPLE);	//TODO Check Optimization (enable antialiasing)
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH);
	glFrontFace(GL_CW);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}


void RHI::EnableDebug() noexcept
{
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	auto func = [](GLenum Source, GLenum Type, GLuint Id, GLenum Severity, GLsizei Length, const GLchar* Message, const void* UserParam)
	{
		fprintf(stderr, "OpenGL log (0x%x): %s\n", Id, Message);
	};

	glDebugMessageCallback(func, nullptr);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_OTHER, GL_DONT_CARE, 0, nullptr, GL_FALSE);
	glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_PERFORMANCE, GL_DONT_CARE, 0, nullptr, GL_FALSE);

}

unsigned int RHI::CreateVAO(unsigned int _flag, const void* _verticesBuffer, unsigned int _verticesBufferSize, const void* _indicesBuffer, unsigned int _indicesBufferSize, bool _generateEBO) noexcept
{
	constexpr unsigned char pos2DSize = 2, pos3DSize = 3, UVSize = 2, normalSize = 3, tangentSize = 3;

	unsigned int VAO, VBO, EBO;

	auto floatSize = sizeof(float);

	/// Generate/Bind VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	/// Generate/Bind VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, _verticesBufferSize, _verticesBuffer, GL_STATIC_DRAW);

	unsigned char 	attribLocation = 0,
					position = 0,
					size =	pos2DSize * ((_flag & POSITION2D) == POSITION2D) +
							pos3DSize * ((_flag & POSITION3D) == POSITION3D) + 
							UVSize * ((_flag & UV) == UV) + 
							normalSize * ((_flag & NORMAL) == NORMAL) +
							tangentSize * ((_flag & TANGENT) == TANGENT);

	if (_flag & POSITION3D)
	{
		glEnableVertexAttribArray(attribLocation);
		glVertexAttribPointer(attribLocation, pos3DSize, GL_FLOAT, GL_FALSE, unsigned(size * floatSize), (void*)position);
		++attribLocation;
		position += pos3DSize;
	}
	else if (_flag & POSITION2D)
	{
		glEnableVertexAttribArray(attribLocation);
		glVertexAttribPointer(attribLocation, pos2DSize, GL_FLOAT, GL_FALSE, unsigned(size * floatSize), (void*)position);
		++attribLocation;
		position += pos2DSize;
	}
	if (_flag & UV)
	{
		glEnableVertexAttribArray(attribLocation);
		glVertexAttribPointer(attribLocation, UVSize, GL_FLOAT, GL_FALSE, unsigned(size * floatSize), (void*)(position * floatSize));
		++attribLocation;
		position += UVSize;
	}
	if (_flag & NORMAL)
	{
		glEnableVertexAttribArray(attribLocation);
		glVertexAttribPointer(attribLocation, normalSize, GL_FLOAT, GL_FALSE, unsigned(size * floatSize), (void*)(position * floatSize));
		++attribLocation;
		position += normalSize;
	}
	if (_flag & TANGENT)
	{
		glEnableVertexAttribArray(attribLocation);
		glVertexAttribPointer(attribLocation, normalSize, GL_FLOAT, GL_FALSE, unsigned(size * floatSize), (void*)(position * floatSize));
		++attribLocation;
		position += normalSize;
	}

	if (_generateEBO)
	{
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicesBufferSize, _indicesBuffer, GL_STATIC_DRAW);
	}

	glBindVertexArray(0);

	return VAO;
}

unsigned int RHI::CreateShader(const char* _shader, unsigned int _shaderType) noexcept
{
	unsigned int newShader = glCreateShader(_shaderType);

	// Read the Vertex Shader code from the file
	std::string shaderCode;
	std::ifstream shaderStream(_shader, std::ios::in);
	if (shaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();
		shaderCode = sstr.str();
		shaderStream.close();
	}
	else
		std::cout << _shader << " NO SUCH FILE IN DIRECTORY" << '\n';

	// Compile New Shader
	char const* sourcePointer = shaderCode.c_str();
	glShaderSource(newShader, 1, &sourcePointer, NULL);
	glCompileShader(newShader);

	int success;

	glGetShaderiv(newShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(newShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	return newShader;
}

unsigned int RHI::CreateShaderProgram(const char* _vertexShader, const char* _fragmentShader) noexcept
{
	GLuint VertexShader = CreateShader(_vertexShader, GL_VERTEX_SHADER);
	GLuint FragmentShader = CreateShader(_fragmentShader, GL_FRAGMENT_SHADER);

	GLuint program = glCreateProgram();
	glAttachShader(program, VertexShader);
	glAttachShader(program, FragmentShader);
	glLinkProgram(program);

	int success;

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	glDeleteShader(FragmentShader);
	glDeleteShader(VertexShader);

	return program;
}

unsigned int RHI::CreateTexture(const char* _texturePath, unsigned int _flag) noexcept
{
	int width, height, channels;
	stbi_set_flip_vertically_on_load(_flag & FLIP_TEXTURE_ON_LOAD);
	unsigned char* data = stbi_load(_texturePath, &width, &height, &channels, STBI_rgb_alpha);
	if (data == nullptr)
		return 0u;
	unsigned int texture = CreateTextureFromData(width, height, data, _texturePath, _flag);
	stbi_image_free(data);
	stbi_set_flip_vertically_on_load(0);
	return texture;
}

unsigned int RHI::CreateTextureFromData(int _width, int _height, void* _data, const char* _name, unsigned int _flag) noexcept
{
	unsigned int textureType = (_flag & CUBEMAP) ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D;
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(textureType, texture);
	if (_name != nullptr)
		glObjectLabel(GL_TEXTURE, texture, -1, _name);
	glTexImage2D(textureType, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data);
	glGenerateMipmap(textureType);
	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return texture;
}

void RHI::BindTexture2D(unsigned int _texture) noexcept
{
	glBindTexture(GL_TEXTURE_2D, _texture);
}

void RHI::BindTextureCubeMap(unsigned int _texture) noexcept
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);
}

void RHI::BindFrameBuffer(unsigned int _framebuffer) noexcept
{
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
}

void RHI::Enable(bool _value, unsigned int _flag) noexcept
{
	if (_value)
		glEnable(_flag);
	else
		glDisable(_flag);
}

void RHI::EnableDepthMask(bool _value) noexcept
{
	glDepthMask(_value);
}

void RHI::UseProgram(unsigned int _program) noexcept
{
	glUseProgram(_program);
}

void RHI::DeleteProgram(unsigned int _program) noexcept
{
	glDeleteProgram(_program);
}

unsigned int RHI::GetLocation(unsigned int _program, const char* _name) noexcept
{
	return glGetUniformLocation(_program, _name);
}

unsigned int RHI::GetAttribute(unsigned int _program, const char* _name) noexcept
{
	return glGetAttribLocation(_program, _name);
}

void RHI::BindVAO(unsigned int _VAO) noexcept
{
	glBindVertexArray(_VAO);
}

void RHI::SetViewport(int _width, int _height) noexcept
{
	glViewport(0, 0, _width, _height);
}

void RHI::SetActiveTexture(int _index) noexcept
{
	glActiveTexture(GL_TEXTURE0 + _index);
}

void RHI::SendBool(unsigned int _location, const bool _value) noexcept
{
	glUniform1i(_location, _value);
}

void RHI::SendInt(unsigned int _location, const int _value) noexcept
{
	glUniform1i(_location, _value);
}

void RHI::SendUint(unsigned int _location, const unsigned int _value) noexcept
{
	glUniform1ui(_location, _value);
}

void RHI::SendFloat(unsigned int _location, const float _value) noexcept
{
	glUniform1f(_location, _value);
}

void RHI::SendFloat2(unsigned int _location, const float _value[2]) noexcept
{
	glUniform2fv(_location, 1, _value);
}

void RHI::SendFloat3(unsigned int _location, const float _value[3]) noexcept
{
	glUniform3fv(_location, 1, _value);
}

void RHI::SendFloat4(unsigned int _location, const float _value[4]) noexcept
{
	glUniform4fv(_location, 1, _value);
}

void RHI::SendMatrix3(unsigned int _location, const float _matrix[9], bool _transpose) noexcept
{
	glUniformMatrix3fv(_location, 1, _transpose, _matrix);
}

void RHI::SendMatrix4(unsigned int _location, const float _matrix[16], bool _transpose) noexcept
{
	glUniformMatrix4fv(_location, 1, _transpose, _matrix);
}

void RHI::Clear(unsigned int _flag) noexcept
{
	glClear(_flag);
}

void RHI::ClearColor(const float _value[4]) noexcept
{
	glClearColor(_value[0], _value[1], _value[2], _value[3]);
}

void RHI::DrawArray(unsigned int _startIndex, unsigned int _count) noexcept
{
	glDrawArrays(GL_TRIANGLES, _startIndex, _count);
}

/*
	_count = Numbers of element in indices's list
	_indices = If VAO has been create with EBO, indices = 0,
	else give indices list
*/
void RHI::DrawElements(unsigned int _count, const void* _indices) noexcept
{
	glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, _indices);
}

void RHI::DrawRangeElements(unsigned int _start, unsigned int _count, const void* _indices) noexcept
{
	glDrawRangeElements(GL_TRIANGLES, _start, _start + _count, _count, GL_UNSIGNED_INT, _indices);
}
