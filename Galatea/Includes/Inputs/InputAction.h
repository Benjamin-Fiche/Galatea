#pragma once

#include <vector>

#include "DLL.h"

#include "InputPattern.h"
#include "InputType.h"
#include "Event.h"

namespace Galatea
{
	class GALATEA_API InputAction : public InputType
	{
	private:
		#pragma region Variables

		Event<>						event;
		std::vector<InputPattern>	patterns;

		#pragma endregion

	public:
		#pragma region Constructors/Destructors

		InputAction()							noexcept = default;
		InputAction(const InputAction& _ia)		noexcept;
		InputAction(InputAction&& _ia)			noexcept;
		InputAction(const std::string& _name)	noexcept;
		InputAction(std::string&& _name)		noexcept;
		~InputAction()							noexcept = default;

		#pragma endregion

		#pragma region Properties

		inline const std::vector<InputPattern>&	GetPatterns()	const noexcept;
		
		#pragma endregion

		#pragma region Methods

		InputAction&	AddPattern()																				noexcept;
		InputAction&	AddPattern(const InputPattern& _pattern)													noexcept;
		InputAction&	AddPattern(InputPattern&& _pattern)															noexcept;
		InputAction&	AddPattern(const Input& _input)																noexcept;
		InputAction&	AddPattern(Input&& _input)																	noexcept;
		InputAction&	AddPattern(EDeviceType _device, EInputState _state, int _code, unsigned int _gamepadID = 0)	noexcept;
		int				AddCallback(const std::function<void()>& _callback)											noexcept;
		int				AddCallback(std::function<void()>&& _callback)												noexcept;
		int				AddCallback(void(*_func)())																	noexcept;
		template<class Class>
		int				AddCallback(void(Class::* _func)(), Class& _instance)										noexcept;
		void			Update()																					noexcept override;

		#pragma endregion

		#pragma region Operators

		InputAction&	operator=(const InputAction& _action)	noexcept;
		InputAction&	operator=(InputAction&& _action)		noexcept;
		/* TODO: besoin de mettre les operators += et -= ? */

		#pragma endregion
	};

	#include "InputAction.inl"
}