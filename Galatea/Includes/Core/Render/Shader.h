#pragma once

#include <string>

#include "DLL.h"
#include "Core/EModelCharacteristics.h"
#include "Maths/Mat4.h"

namespace Galatea
{
	class GALATEA_API Shader
	{
	private:
		unsigned int								program	{};
		unsigned int								flag	{};

		std::string									name;

		bool	Load(const char* _vertexShader, const char* _fragmentShader, unsigned int _flag = 0u)	noexcept;

		Shader() = default;
	public:
		~Shader()																						noexcept;

		void	Use()																			const	noexcept;

		void	SendBool(const char* _location, const bool _value)								const	noexcept;
		void	SendInt(const char* _location, const int _value)								const	noexcept;
		void	SendUint(const char* _location, const unsigned int _value)						const	noexcept;
		void	SendFloat(const char* _location, const float _value)							const	noexcept;
		void	SendVec2(const char* _location, const Vec2& _value)								const	noexcept;
		void	SendVec3(const char* _location, const Vec3& _value)								const	noexcept;
		void	SendVec4(const char* _location, const Vec4& _value)								const	noexcept;
		void	SendMat4(const char* _location, const Mat4& _matrix, bool _transpose = false)	const	noexcept;

		inline unsigned int			GetShader()													const	noexcept { return program; };
		inline unsigned int			GetFlag()													const	noexcept { return flag; }
		inline const std::string&	GetName()													const	noexcept { return name; };

		friend class ResourcesManager;
	};
}
