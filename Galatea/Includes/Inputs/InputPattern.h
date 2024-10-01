#pragma once

#include <vector>

#include "DLL.h"

#include "Input.h"

namespace Galatea
{
	class GALATEA_API InputPattern
	{
	private:
		#pragma region Variables

		std::vector<Input>	inputs;

		#pragma endregion

	public:
		#pragma region Constructors/Destructors

		InputPattern()																					noexcept = default;
		InputPattern(const InputPattern& _ip)															noexcept;
		InputPattern(InputPattern&& _ip)																noexcept;
		InputPattern(const Input& _input)																noexcept;
		InputPattern(Input&& _input)																	noexcept;
		InputPattern(EDeviceType _device, EInputState _state, int _code, unsigned int _gamepadID = 0)	noexcept;
		~InputPattern()																					noexcept = default;

		#pragma endregion

		#pragma region Properties

		inline const std::vector<Input>&	GetInputs() const noexcept;

		#pragma endregion

		#pragma region Methods

		InputPattern&	AddInput(const Input& _input)																noexcept;
		InputPattern&	AddInput(Input&& _input)																	noexcept;
		InputPattern&	AddInput(EDeviceType _device, EInputState _state, int _code, unsigned int _gamepadID = 0)	noexcept;
		bool			IsValid()																			const	noexcept;

		#pragma endregion

		#pragma region Operators

		InputPattern&	operator=(const InputPattern& _ip)	noexcept;
		InputPattern&	operator=(InputPattern&& _ip)		noexcept;

		#pragma endregion
	};

	#include "InputPattern.inl"
}