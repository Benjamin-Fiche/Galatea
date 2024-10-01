#include "Inputs/InputType.h"
#include "Inputs/InputManager.h"

using namespace Galatea;

#pragma region Constructors/Destructors

InputType::InputType() noexcept
	: isValid{ false }, name{}
{}

InputType::InputType(const std::string& _name) noexcept
	: isValid{ false }, name{ _name }
{}

InputType::InputType(std::string&& _name) noexcept
	: isValid{ false }, name{ std::move(_name) }
{}

#pragma endregion

#pragma region Methods
#pragma endregion

#pragma region Operators

InputType& InputType::operator=(const InputType& _ie) noexcept
{
	name	= _ie.name;
	isValid	= _ie.isValid;
	return *this;
}

InputType& InputType::operator=(InputType&& _ie) noexcept
{
	name	= std::move(_ie.name);
	isValid	= std::move(_ie.isValid);
	return *this;
}

#pragma endregion