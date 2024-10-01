#pragma once

#pragma region Properties

const std::vector<InputPattern>& InputAxis::GetPositiveButtons() const noexcept
{
	return positiveButtons;
}

const std::vector<InputPattern>& InputAxis::GetNegativeButtons() const noexcept
{
	return negativeButtons;
}

const float& InputAxis::GetValue() const noexcept
{
	return value;
}

#pragma endregion

#pragma region Methods

template<class Class>
int InputAxis::AddCallback(void(Class::* _func)(float), Class& _instance) noexcept
{
	return event.Suscribe(std::move([_func, &_instance](float _value) { (_instance.*_func)(_value); }));
}

#pragma endregion