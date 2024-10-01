#include "Inputs/InputAxis.h"
#include "Inputs/InputManager.h"

using namespace Galatea;

#pragma region Constructors/Destructors

InputAxis::InputAxis() noexcept
	:	InputType{}, event{}, positiveButtons{}, negativeButtons{}, value{ 0.f },
		axisType{ G_DEFAULT_AXIS_TYPE }, axis{ 0 }, gamepadID{ 0 }, inverse{ false }, deadZone{ G_DEFAULT_DEADZONE }
{}

InputAxis::InputAxis(const InputAxis& _ia) noexcept
	:	InputType{}, event{ _ia.event }, positiveButtons{ _ia.positiveButtons }, negativeButtons{ _ia.negativeButtons }, value{ _ia.value },
		axisType{ _ia.axisType }, axis{ _ia.axis }, gamepadID{ _ia.gamepadID }, inverse{ _ia.inverse }, deadZone{ _ia.deadZone }
{}

InputAxis::InputAxis(InputAxis&& _ia) noexcept
	:	InputType{}, event{ std::move(_ia.event) }, positiveButtons{ std::move(_ia.positiveButtons) },
		negativeButtons{ std::move(_ia.negativeButtons) }, value{ std::move(_ia.value) }, axisType{ std::move(_ia.axisType) },
		axis{ std::move(_ia.axis) }, gamepadID{ std::move(_ia.gamepadID) }, inverse{ std::move(_ia.inverse) }, deadZone{ std::move(_ia.deadZone) }
{}

InputAxis::InputAxis(const std::string& _name) noexcept
	:	InputType{ _name }, event{}, positiveButtons{}, negativeButtons{}, value{ 0.f },
		axisType{ G_DEFAULT_AXIS_TYPE }, axis{ 0 }, gamepadID{ 0 }, inverse{ false }, deadZone{ G_DEFAULT_DEADZONE }
{}

InputAxis::InputAxis(std::string&& _name) noexcept
	:	InputType{ std::move(_name) }, event{}, positiveButtons{}, negativeButtons{}, value{ 0.f },
		axisType{ G_DEFAULT_AXIS_TYPE }, axis{ 0 }, gamepadID{ 0 }, inverse{ false }, deadZone{ G_DEFAULT_DEADZONE }
{}

#pragma endregion

#pragma region Methods

InputAxis& InputAxis::AddPositiveButton() noexcept
{
	positiveButtons.push_back({});
	return *this;
}

InputAxis& InputAxis::AddPositiveButton(const InputPattern& _pattern) noexcept
{
	positiveButtons.push_back(_pattern);
	return *this;
}

InputAxis& InputAxis::AddPositiveButton(InputPattern&& _pattern) noexcept
{
	positiveButtons.push_back(std::move(_pattern));
	return *this;
}

InputAxis& InputAxis::AddPositiveButton(const Input& _input) noexcept
{
	positiveButtons.push_back({ _input });
	return *this;
}

InputAxis& InputAxis::AddPositiveButton(Input&& _input) noexcept
{
	positiveButtons.push_back({ std::move(_input) });
	return *this;
}

InputAxis& InputAxis::AddPositiveButton(EDeviceType _device, EInputState _state, int _code, unsigned int _gamepadID) noexcept
{
	positiveButtons.push_back({ _device, _state, _code, _gamepadID });
	return *this;
}

InputAxis& InputAxis::AddNegativeButton() noexcept
{
	negativeButtons.push_back({});
	return *this;
}

InputAxis& InputAxis::AddNegativeButton(const InputPattern& _pattern) noexcept
{
	negativeButtons.push_back(_pattern);
	return *this;
}

InputAxis& InputAxis::AddNegativeButton(InputPattern&& _pattern) noexcept
{
	negativeButtons.push_back(_pattern);
	return *this;
}

InputAxis& InputAxis::AddNegativeButton(const Input& _input) noexcept
{
	negativeButtons.push_back({ _input });
	return *this;
}

InputAxis& InputAxis::AddNegativeButton(Input&& _input) noexcept
{
	negativeButtons.push_back({ std::move(_input) });
	return *this;
}

InputAxis& InputAxis::AddNegativeButton(EDeviceType _device, EInputState _state, int _code, unsigned int _gamepadID) noexcept
{
	negativeButtons.push_back({ _device, _state, _code, _gamepadID });
	return *this;
}

int InputAxis::AddCallback(const std::function<void(float)>& _callback) noexcept
{
	return event.Suscribe(_callback);
}

int InputAxis::AddCallback(std::function<void(float)>&& _callback) noexcept
{
	return event.Suscribe(_callback);
}

int	InputAxis::AddCallback(void(*_func)(float)) noexcept
{
	return event.Suscribe(std::move([_func](float _value) { _func(_value); }));
}

void InputAxis::Update() noexcept
{
	value = 0;
	switch (axisType)
	{
		case EAxisType::BUTTONS:
		{
			std::vector<InputPattern>::iterator	posIt;
			for (posIt = positiveButtons.begin(); posIt != positiveButtons.end(); ++posIt)
				if ((*posIt).IsValid())
				{
					value += 1.f;
					break;
				}

			std::vector<InputPattern>::iterator	negIt;
			for (negIt = negativeButtons.begin(); negIt != negativeButtons.end(); ++negIt)
				if ((*negIt).IsValid())
				{
					value -= 1.f;
					break;
				}

			if (std::abs(value) > deadZone)
				event.Raise(value);

			return;
		}
		case EAxisType::MOUSE:
		{
			value = InputManager::GetInstance()->GetMouseAxis(axis);

			if (std::abs(value) > deadZone)
				event.Raise(value);

			return;
		}
		case EAxisType::GAMEPAD:
		{
			value = InputManager::GetInstance()->GetGamepadAxis(gamepadID, axis);

			if (std::abs(value) > deadZone)
			{
				if (inverse)
					event.Raise(-value);
				else
					event.Raise(value);
			}

			return;
		}
	}
}

#pragma endregion

#pragma region Operators

InputAxis& InputAxis::operator=(const InputAxis& _ia) noexcept
{
	InputType::operator=(_ia);
	event			= _ia.event;
	positiveButtons = _ia.positiveButtons;
	negativeButtons = _ia.negativeButtons;
	value			= _ia.value;
	axisType		= _ia.axisType;
	axis			= _ia.axis;
	gamepadID		= _ia.gamepadID;
	inverse			= _ia.inverse;
	deadZone		= _ia.deadZone;
	//sensivity		= _ia.sensivity;
	return *this;
}

InputAxis& InputAxis::operator=(InputAxis&& _ia) noexcept
{
	InputType::operator=(_ia);
	event			= std::move(_ia.event);
	positiveButtons = std::move(_ia.positiveButtons);
	negativeButtons = std::move(_ia.negativeButtons);
	value			= std::move(_ia.value);
	axisType		= std::move(_ia.axisType);
	axis			= std::move(_ia.axis);
	gamepadID		= std::move(_ia.gamepadID);
	inverse			= std::move(_ia.inverse);
	deadZone		= std::move(_ia.deadZone);
	//sensivity		= std::move(_ia.sensivity);
	return *this;
}

#pragma endregion