#pragma once

#include <string>

#include "DLL.h"

namespace Galatea
{
	class GALATEA_API InputType abstract
	{
	protected:
		#pragma region Variables

		bool		isValid;

		#pragma endregion

	public:
		#pragma region Variables

		std::string	name;

		#pragma endregion

		#pragma region Constructors/Destructors

		InputType()							noexcept;
		InputType(const InputType& _ie)		noexcept = default;
		InputType(InputType&& _ie)			noexcept = default;
		InputType(const std::string& _name)	noexcept;
		InputType(std::string&& _name)		noexcept;
		~InputType()						noexcept = default;

		#pragma endregion

		#pragma region Properties

		inline const bool&	GetIsValid()	const noexcept;

		#pragma endregion

		#pragma region Methods

		virtual void	Update() noexcept = 0;

		#pragma endregion

		#pragma region Operators

		InputType&	operator=(const InputType& _ie)	noexcept;
		InputType&	operator=(InputType&& _ie)		noexcept;

		#pragma endregion
	};

	#include "InputType.inl"
}