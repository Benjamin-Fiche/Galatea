#pragma once

#include "DLL.h"

#include "EInputState.h"
#include "EDeviceType.h"

namespace Galatea
{
	struct GALATEA_API Input
	{
		#pragma region Variables

		EDeviceType		device;
		EInputState		state;
		int				code;
		unsigned int	gamepadID;

		#pragma endregion

		#pragma region Constructors/Destructors

		Input()																					noexcept = default;
		Input(const Input& _input)																noexcept = default;
		Input(Input&& _input)																	noexcept = default;
		Input(EDeviceType _device, EInputState _state, int _code, unsigned int _gamepadID = 0)	noexcept;
		~Input()																				noexcept = default;
		
		#pragma endregion

		#pragma region Properties
		#pragma endregion

		#pragma region Methods

		bool	IsValid()	const	noexcept;

		#pragma endregion

		#pragma region Operators

		Input&	operator=(const Input& _input)	noexcept = default;
		Input&	operator=(Input&& _input)		noexcept = default;

		#pragma endregion
	};

	#include "Input.inl"
}