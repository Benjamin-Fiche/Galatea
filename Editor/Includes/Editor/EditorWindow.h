#pragma once

#include <iostream>
namespace Galatea
{
	class EditorWindow
	{
	public:
		#pragma region Variables

		std::string	name;
		bool		isOpen;

		#pragma endregion

		#pragma region Consturctors/Desturctor

		EditorWindow()							noexcept;
		EditorWindow(const char* _name)			noexcept;
		EditorWindow(const std::string& _name)	noexcept;
		EditorWindow(std::string&& _name)		noexcept;
		~EditorWindow()							noexcept = default;

		#pragma endregion

		#pragma region Properties

		bool			IsOpen() const noexcept { return isOpen; };

		EditorWindow&	SetIsOpen(bool _isOpen) noexcept { isOpen = _isOpen; };

		#pragma endregion

		#pragma region Methods

		virtual void	Update()	noexcept = 0;

		#pragma endregion
	};
}