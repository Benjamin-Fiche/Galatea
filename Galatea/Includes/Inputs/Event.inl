#pragma once

#pragma region Constructors/Destructors

template<class ... Args>
Event<Args...>::Event(void(*_func)(Args ... _args)) noexcept
	: listeners{ std::move(std::move([_func](Args ... _args) { _func(_args ...); })) }
{}

template<class ... Args>
template<class Class>
Event<Args...>::Event(void(Class::*_func)(Args ... _args), Class& _instance) noexcept
	: listeners{ std::move(std::move([_func, &_instance](Args ... _args) { (_instance.*_func)(_args ...); })) }
{}

template<class ... Args>
Event<Args...>::Event(const Event& _event) noexcept
	: listeners{ _event.listeners }
{}

template<class ... Args>
Event<Args...>::Event(Event&& _event) noexcept
	: listeners{ std::move(_event.listeners) }
{}

template<class ... Args>
Event<Args...>::Event(const std::function<void(Args...)>& _func) noexcept
	: listeners{ _func }
{}

template<class ... Args>
Event<Args...>::Event(std::function<void(Args...)>&& _func) noexcept
	: listeners{ std::move(_func) }
{}

#pragma endregion

#pragma region Properties

template<class ... Args>
const std::vector<std::function<void(Args...)>>& Event<Args...>::GetListeners() const noexcept
{
	return listeners;
}

template<class ... Args>
size_t Event<Args...>::GetListenersCount() const noexcept
{
	return listeners.size();
}

#pragma endregion

#pragma region Methods

template<class ... Args>
int Event<Args...>::GetFreeEmplacementID() const noexcept
{
	for (int i = 0; i < listeners.size(); i++)
		if (listeners[i] == nullptr)
			return i;
	return -1;
}

template<class ... Args>
int Event<Args...>::Suscribe(const std::function<void(Args...)>& _func) noexcept
{
	int	id{ GetFreeEmplacementID() };
	if (id >= 0)
		listeners[id] = _func;
	else
	{
		id = listeners.size();
		listeners.push_back(_func);
	}
	return id;
}

template<class ... Args>
int Event<Args...>::Suscribe(std::function<void(Args...)>&& _func) noexcept
{
	int	id{ GetFreeEmplacementID() };
	if (id >= 0)
		listeners[id] = std::move(_func);
	else
	{
		id = listeners.size();
		listeners.push_back(std::move(_func));
	}
	return id;
}

template<class ... Args>
int Event<Args...>::Suscribe(void(*_func)(Args ... _args)) noexcept
{
	int	id{ GetFreeEmplacementID() };
	if (id >= 0)
		listeners[id] = std::move(std::move([_func](Args ... _args) { _func(_args ...); }));
	else
	{
		id = listeners.size();
		listeners.push_back(std::move([_func](Args ... _args) { _func(_args ...); }));
	}
	return id;
}

template<class ... Args>
template<class Class>
int Event<Args...>::Suscribe(void(Class::*_func)(Args ... _args), Class& _instance) noexcept
{
	int	id{ GetFreeEmplacementID() };
	if (id >= 0)
		listeners[id] = std::move(std::move([_func, &_instance](Args ... _args) { (_instance.*_func)(_args ...); }));
	else
	{
		id = listeners.size();
		listeners.push_back(std::move([_func, &_instance](Args ... _args) { (_instance.*_func)(_args ...); }));
	}
	return id;
}

template<class ... Args>
bool Event<Args...>::Unsuscribe(unsigned int _id) noexcept
{
	if (_id >= listeners.size())
		return false;

	listeners[_id] = nullptr;
	return true;
}

template<class ... Args>
void Event<Args...>::UnsuscribeAll() noexcept
{
	for (auto it = listeners.begin(); it != listeners.end(); ++it)
		*it = nullptr;
}

template<class ... Args>
void Event<Args...>::Raise(Args ... args) const noexcept
{
	for (auto it = listeners.begin(); it != listeners.end(); ++it)
		if (*it)
			(*it)(args ...);
}

#pragma endregion

#pragma region Operators

template<class ... Args>
Event<Args...>& Event<Args...>::operator=(const Event<Args...>& _event) noexcept
{
	listeners = _event.listeners;
	return *this;
}

template<class ... Args>
Event<Args...>& Event<Args...>::operator=(Event<Args...>&& _event) noexcept
{
	listeners = std::move(_event.listeners);
	return *this;
}

template<class ... Args>
int Event<Args...>::operator+=(const std::function<void(Args...)>& _func) noexcept
{
	int	id{ GetFreeEmplacementID() };
	if (id >= 0)
		listeners[id] = _func;
	else
	{
		id = listeners.size();
		listeners.push_back(_func);
	}
	return id;
}

template<class ... Args>
int Event<Args...>::operator+=(std::function<void(Args...)>&& _func) noexcept
{
	int	id{ GetFreeEmplacementID() };
	if (id >= 0)
		listeners[id] = std::move(_func);
	else
	{
		id = listeners.size();
		listeners.push_back(std::move(_func));
	}
	return id;
}

template<class ... Args>
int Event<Args...>::operator+=(void(*_func)(Args ... _args)) noexcept
{
	int	id{ GetFreeEmplacementID() };
	if (id >= 0)
		listeners[id] = std::move(std::move([_func](Args ... _args) { _func(_args ...); }));
	else
	{
		id = listeners.size();
		listeners.push_back(std::move([_func](Args ... _args) { _func(_args ...); }));
	}
	return id;
}

template<class ... Args>
bool Event<Args...>::operator-=(int _id) noexcept
{
	if (_id >= listeners.size())
		return false;

	listeners[_id] = nullptr;
	return true;
}

template<class ... Args>
void Event<Args...>::operator()(Args ... args) noexcept
{
	for (auto it = listeners.begin(); it != listeners.end(); ++it)
		if (*it)
			(*it)(args ...);
}

#pragma endregion