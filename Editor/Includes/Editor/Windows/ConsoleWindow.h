#pragma once

#include "Editor/EditorWindow.h"

namespace Galatea
{
	class ConsoleWindow : public EditorWindow
	{
	public:
		#pragma region Constructors/Destructor

		ConsoleWindow()							noexcept = default;
		ConsoleWindow(const ConsoleWindow& _w)	noexcept = default;
		ConsoleWindow(ConsoleWindow&& _w)		noexcept = default;
		ConsoleWindow(const char* _name)		noexcept;
		ConsoleWindow(const std::string& _name)	noexcept;
		ConsoleWindow(std::string&& _name)		noexcept;
		~ConsoleWindow()						noexcept = default;

		#pragma endregion

		#pragma region Methods

		void Update()	noexcept override;

		#pragma endregion
	};
}
