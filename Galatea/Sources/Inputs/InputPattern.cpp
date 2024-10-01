#include "Inputs/InputPattern.h"

using namespace Galatea;

#pragma region Constructors/Desturctors

InputPattern::InputPattern(const InputPattern& _ip) noexcept
	: inputs{ _ip.inputs }
{}

InputPattern::InputPattern(InputPattern&& _ip) noexcept
	: inputs{ std::move(_ip.inputs) }
{}

InputPattern::InputPattern(const Input& _input) noexcept
	: inputs{ _input }
{}

InputPattern::InputPattern(Input&& _input) noexcept
	: inputs{ std::move(_input) }
{}

InputPattern::InputPattern(EDeviceType _device, EInputState _state, int _code, unsigned int _gamepadID) noexcept
	: inputs{ { _device, _state, _code, _gamepadID } }
{}

#pragma endregion

#pragma region Methods

InputPattern& InputPattern::AddInput(const Input& _input) noexcept
{
	inputs.push_back(_input);
	return *this;
}

InputPattern& InputPattern::AddInput(Input&& _input) noexcept
{
	inputs.push_back(std::move(_input));
	return *this;
}

InputPattern& InputPattern::AddInput(EDeviceType _device, EInputState _state, int _code, unsigned int _gamepadID) noexcept
{
	inputs.push_back({ _device, _state, _code, _gamepadID });
	return *this;
}

bool InputPattern::IsValid() const noexcept
{
	std::vector<Input>::const_iterator it;
	for (it = inputs.begin(); it != inputs.end(); ++it)
		if (!(*it).IsValid())
			return false;
	return true;
}

#pragma endregion

#pragma region Operators

InputPattern& InputPattern::operator=(const InputPattern& _ip) noexcept
{
	inputs = _ip.inputs;
	return *this;
}

InputPattern& InputPattern::operator=(InputPattern&& _ip) noexcept
{
	inputs = std::move(_ip.inputs);
	return *this;
}

#pragma endregion