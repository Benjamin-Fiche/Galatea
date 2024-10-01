#include "Inputs/InputAction.h"

using namespace Galatea;

#pragma region Constructors/Destructors

InputAction::InputAction(const InputAction& _ia) noexcept
	: InputType{}, event{ _ia.event }, patterns{ _ia.patterns }
{}

InputAction::InputAction(InputAction&& _ia) noexcept
	: InputType{ std::move(_ia) }, event{ std::move(_ia.event) }, patterns{ std::move(_ia.patterns) }
{}

InputAction::InputAction(const std::string& _name) noexcept
	: InputType{ _name }, event{}, patterns{}
{}

InputAction::InputAction(std::string&& _name) noexcept
	: InputType{ _name }, event{}, patterns{}
{}

#pragma endregion

#pragma region Methods

InputAction& InputAction::AddPattern() noexcept
{
	patterns.push_back({});
	return *this;
}

InputAction& InputAction::AddPattern(const InputPattern& _pattern) noexcept
{
	patterns.push_back(_pattern);
	return *this;
}

InputAction& InputAction::AddPattern(InputPattern&& _pattern) noexcept
{
	patterns.push_back(std::move(_pattern));
	return *this;
}

InputAction& InputAction::AddPattern(const Input& _input) noexcept
{
	patterns.push_back({ _input });
	return *this;
}

InputAction& InputAction::AddPattern(Input&& _input) noexcept
{
	patterns.push_back({ std::move(_input) });
	return *this;
}

InputAction& InputAction::AddPattern(EDeviceType _device, EInputState _state, int _code, unsigned int _gamepadID) noexcept
{
	patterns.push_back({ _device, _state, _code, _gamepadID });
	return *this;
}

int InputAction::AddCallback(const std::function<void()>& _callback) noexcept
{
	return event.Suscribe(_callback);
}

int InputAction::AddCallback(std::function<void()>&& _callback) noexcept
{
	return event.Suscribe(_callback);
}

int	InputAction::AddCallback(void(*_func)()) noexcept
{
	return event.Suscribe(std::move([_func]() { _func(); }));
}

void InputAction::Update() noexcept
{
	std::vector<InputPattern>::iterator	it;
	for (it = patterns.begin(); it != patterns.end(); ++it)
	{
		isValid = (*it).IsValid();
		if (isValid)
			event.Raise();
	}
}

#pragma endregion

#pragma region Operators

InputAction& InputAction::operator=(const InputAction& _ia) noexcept
{
	InputType::operator=(_ia);
	event = _ia.event;
	patterns = _ia.patterns;
	return *this;
}

InputAction& InputAction::operator=(InputAction&& _ia) noexcept
{
	InputType::operator=(std::move(_ia));
	event = std::move(_ia.event);
	patterns = std::move(_ia.patterns);
	return *this;
}

#pragma endregion