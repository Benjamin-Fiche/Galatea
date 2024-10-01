#pragma once

#pragma region Properties

const std::vector<InputPattern>& InputAction::GetPatterns() const noexcept
{
	return patterns;
}

#pragma endregion

#pragma region Methods

template<class Class>
int InputAction::AddCallback(void(Class::* _func)(), Class& _instance) noexcept
{
	return event.Suscribe(std::move([_func, &_instance]() { (_instance.*_func)(); }));
}

#pragma endregion