#pragma once

#include <vector>

#include "DLL.h"

#include "InputType.h"
#include "InputPattern.h"
#include "EAxisType.h"
#include "Event.h"

#pragma region Defines

#define G_DEFAULT_AXIS_TYPE EAxisType::BUTTONS
#define G_DEFAULT_DEADZONE 0.19f
//#define G_DEFAULT_SENSIVITY 1

#pragma endregion

namespace Galatea
{
	class GALATEA_API InputAxis : public InputType
	{
	private:
		#pragma region Variables

		Event<float>				event;
		std::vector<InputPattern>	positiveButtons;
		std::vector<InputPattern>	negativeButtons;

		float						value;

		#pragma endregion

	public:
		#pragma region Variables

		EAxisType		axisType;
		int				axis;
		unsigned int	gamepadID;
		bool			inverse;
		float			deadZone;
		//float			sensivity;

		#pragma endregion

		#pragma region Constructors/Destructors

		InputAxis()							noexcept;
		InputAxis(const InputAxis& _ia)		noexcept;
		InputAxis(InputAxis&& _ia)			noexcept;
		InputAxis(const std::string& _name)	noexcept;
		InputAxis(std::string&& _name)		noexcept;
		~InputAxis()						noexcept = default;

		#pragma endregion

		#pragma region Properties

		inline const std::vector<InputPattern>&	GetPositiveButtons()	const noexcept;
		inline const std::vector<InputPattern>&	GetNegativeButtons()	const noexcept;
		inline const float&						GetValue()				const noexcept;

		#pragma endregion

		#pragma region Methods

		InputAxis&	AddPositiveButton()																					noexcept;
		InputAxis&	AddPositiveButton(const InputPattern& _pattern)														noexcept;
		InputAxis&	AddPositiveButton(InputPattern&& _pattern)															noexcept;
		InputAxis&	AddPositiveButton(const Input& _input)																noexcept;
		InputAxis&	AddPositiveButton(Input&& _input)																	noexcept;
		InputAxis&	AddPositiveButton(EDeviceType _device, EInputState _state, int _code, unsigned int _gamepadID = 0)	noexcept;
		InputAxis&	AddNegativeButton()																					noexcept;
		InputAxis&	AddNegativeButton(const InputPattern& _pattern)														noexcept;
		InputAxis&	AddNegativeButton(InputPattern&& _pattern)															noexcept;
		InputAxis&	AddNegativeButton(const Input& _input)																noexcept;
		InputAxis&	AddNegativeButton(Input&& _input)																	noexcept;
		InputAxis&	AddNegativeButton(EDeviceType _device, EInputState _state, int _code, unsigned int _gamepadID = 0)	noexcept;
		int			AddCallback(const std::function<void(float)>& _callback)											noexcept;
		int			AddCallback(std::function<void(float)>&& _callback)													noexcept;
		int			AddCallback(void(*_func)(float))																	noexcept;
		template<class Class>
		int			AddCallback(void(Class::*_func)(float), Class& _instance)								noexcept;
		void		Update()																							noexcept override;

		#pragma endregion

		#pragma region Operators

		InputAxis&	operator=(const InputAxis& _axis)	noexcept;
		InputAxis&	operator=(InputAxis&& _axis)		noexcept;

		#pragma endregion
	};

	#include "InputAxis.inl"
}