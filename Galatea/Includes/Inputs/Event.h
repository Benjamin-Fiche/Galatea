#pragma once

#include <vector>
#include <functional>

#include "DLL.h"

namespace Galatea
{
	template<class ... Args>
	class Event
	{
	private:
		#pragma region Variables

		std::vector<std::function<void(Args...)>>	listeners;

		#pragma endregion

		#pragma region Methods

		int	GetFreeEmplacementID()	const noexcept;

		#pragma endregion

	public:
		#pragma region Constructors/Destructors

		Event()															noexcept = default;
		Event(const Event& _event)										noexcept;
		Event(Event&& _event)											noexcept;
		
		/*
		Create an event with a function to add to the listeners
			- _func : the function to add to the listeners (its ID is 0)
		*/
		Event(void(*_func)(Args ... _args))								noexcept;
		
		/*
		Create an event with a function to add to the listeners
			- _func : the function to add to the listeners (its ID is 0)
		*/
		Event(std::function<void(Args...)>&& _func)						noexcept;
		
		/*
		Create an event with a function to add to the listeners
			- _func : the function to add to the listeners (its ID is 0)
			- _instance : the instance of the object that call the function
		*/
		template<class Class>
		Event(void(Class::*_func)(Args ... _args), Class& _instance)	noexcept;

		/*
		Create an event with a function to add to the listeners
			- _func : the function to add to the listeners (its ID is 0)
		*/
		Event(const std::function<void(Args...)>& _func)				noexcept;

		~Event()														noexcept = default;

		#pragma endregion

		#pragma region Properties

		inline const std::vector<std::function<void(Args...)>>&	GetListeners()		const noexcept;
		inline size_t											GetListenersCount()	const noexcept;

		#pragma endregion
		
		#pragma region Methods

		/*
		Add a listener to this event
			- _func : the function to suscribe to the event
			- return the ID of the function if user wants to unsuscribe it later
		*/
		int		Suscribe(const std::function<void(Args...)>& _func)				noexcept;

		/*
		Add a listener to this event
			- _func : the function to suscribe to the event
			- return the ID of the function if user wants to unsuscribe it later
		*/
		int		Suscribe(std::function<void(Args...)>&& _func)					noexcept;

		/*
		Add a listener to this event
			- _func : the function to suscribe to the event
			- return the ID of the function if user wants to unsuscribe it later
		*/
		int		Suscribe(void(*_func)(Args ... _args))							noexcept;

		/*
		Add a listener to this event
			- _func : the function to suscribe to the event
			- _instance : the instance of the object that call the function
			- return the ID of the function if user wants to unsuscribe it later
		*/
		template<class Class>
		int		Suscribe(void(Class::*_func)(Args ... _args), Class& _instance)	noexcept;

		/*
		Remove a listener from this event
			- _id : the ID of the function to unsuscribe
			- return the true if the function has been deleted or false if the function has not been found
		*/
		bool	Unsuscribe(unsigned int _id)									noexcept;
		
		/* Remove all listeners of this event */
		void	UnsuscribeAll()													noexcept;
		
		/* Call all the listeners' callbacks */
		void	Raise(Args ... args)									const	noexcept;

		#pragma endregion
		
		#pragma region Operators

		Event&	operator=(const Event& _event)										noexcept;
		Event&	operator=(Event&& _event)											noexcept;
		
		/*
		Add a listener to this event
			- _func : the function to suscribe to the event
			- return the ID of the function if user wants to unsuscribe it later
		*/
		int		operator+=(const std::function<void(Args...)>& _func)				noexcept;
		
		/*
		Add a listener to this event
			- _func : the function to suscribe to the event
			- return the ID of the function if user wants to unsuscribe it later
		*/
		int		operator+=(std::function<void(Args...)>&& _func)					noexcept;
		
		/*
		Add a listener to this event
			- _func : the function to suscribe to the event
			- return the ID of the function if user wants to unsuscribe it later
		*/
		int		operator+=(void(*_func)(Args ... _args))							noexcept;

		/*
		Remove a listener from this event
			- _id : the ID of the function to unsuscribe
			- return true if the function has been deleted or false if the function has not been found
		*/
		bool	operator-=(int _id)													noexcept;

		void	operator()(Args ... args)											noexcept;

		#pragma endregion
	};

	#include "Event.inl"
}