#include "Core/Render/Shader.h"
#include "Core/Render/RHI.h"

using namespace Galatea;

Shader::~Shader() noexcept
{
	RHI::DeleteProgram(program);
}

bool Shader::Load(const char* _vertexShader, const char* _fragmentShader, unsigned int _flag)	noexcept
{
	name = _vertexShader;
	name += " ";
	name += _fragmentShader;
	program = RHI::CreateShaderProgram(_vertexShader, _fragmentShader);
	flag = HAS_DIFFUSE_TEXTURE | _flag;

	return program != 0;
}

void Shader::Use() const noexcept 
{ 
	RHI::UseProgram(program); 
}

void Shader::SendBool(const char* _location, const bool _value) const noexcept
{
	RHI::SendBool(RHI::GetLocation(program, _location), _value);
}

void Shader::SendInt(const char* _location, const int _value) const noexcept
{
	RHI::SendInt(RHI::GetLocation(program, _location), _value);
}

void Shader::SendUint(const char* _location, const unsigned int _value) const noexcept
{
	RHI::SendUint(RHI::GetLocation(program, _location), _value);
}

void Shader::SendFloat(const char* _location, const float _value) const noexcept
{
	RHI::SendFloat(RHI::GetLocation(program, _location), _value);
}

void Shader::SendVec2(const char* _location, const Vec2& _value) const noexcept
{
	RHI::SendFloat2(RHI::GetLocation(program, _location), _value.xy);
}

void Shader::SendVec3(const char* _location, const Vec3& _value) const noexcept
{
	RHI::SendFloat3(RHI::GetLocation(program, _location), _value.xyz);
}

void Shader::SendVec4(const char* _location, const Vec4& _value) const noexcept
{
	RHI::SendFloat4(RHI::GetLocation(program, _location), _value.xyzw);
}

void Shader::SendMat4(const char* _location, const Mat4& _matrix, bool _transpose) const noexcept
{
	RHI::SendMatrix4(RHI::GetLocation(program, _location), _matrix.data, _transpose);
}