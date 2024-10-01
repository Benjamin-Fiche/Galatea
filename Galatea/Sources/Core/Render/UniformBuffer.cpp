#include <cstring>

#include "Core/Render/UniformBuffer.h"
#include "Libraries/GL/glew.h"

using namespace Galatea;

UniformBuffer::~UniformBuffer() noexcept
{
	glDeleteBuffers(1, &ubo);
}

void UniformBuffer::InitUbo(const void* _class) noexcept
{
	glGenBuffers(1, &ubo);															//Create uniformBuffer
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);											//Bind
	glBufferData(GL_UNIFORM_BUFFER, bufferSize, _class, GL_DYNAMIC_COPY);			//Set value
	glBindBuffer(GL_UNIFORM_BUFFER, 0);												//Unbind
}

void UniformBuffer::BindShader(unsigned int _program) const noexcept
{
	unsigned int blockIndex = glGetUniformBlockIndex(_program, bufferName);			//Get Index of uniformBuffer in shader
	glUniformBlockBinding(_program, blockIndex, currentPosition);					//Set it to the GPU uniformBuffer memory
}

void UniformBuffer::SendToGPU(const void* _class) const noexcept
{
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);											//Bind
	glBufferData(GL_UNIFORM_BUFFER, bufferSize, _class, GL_STATIC_DRAW);			//Send Class to GPU

	glBindBufferBase(GL_UNIFORM_BUFFER, currentPosition, ubo);						//Send uniformBuffer GPU position
}
