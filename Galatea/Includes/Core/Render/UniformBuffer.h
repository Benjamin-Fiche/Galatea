#pragma once

namespace Galatea
{
	class UniformBuffer
	{
	private:
		unsigned int				ubo;
		unsigned int				currentPosition;

		unsigned int				bufferSize;
		const char*					bufferName;

		inline static unsigned int	totalUniformBuffer = 0;

		void InitUbo(const void* _class)									noexcept;
	public:
		UniformBuffer()														noexcept = default;

		~UniformBuffer()													noexcept;

		template<typename Class>
		void	InitUniformBuffer(const char* _bufferName, Class* _class)	noexcept
		{
			currentPosition = totalUniformBuffer;
			bufferSize = sizeof(Class);
			bufferName = _bufferName;

			InitUbo(_class);
			++totalUniformBuffer;
		}

		void	BindShader(unsigned int _program)					const	noexcept;

		void	SendToGPU(const void* _class)						const	noexcept;
	};
}