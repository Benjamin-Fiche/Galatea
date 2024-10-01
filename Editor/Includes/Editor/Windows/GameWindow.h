#pragma once

#include "Editor/EditorWindow.h"

namespace Galatea
{
	class GameWindow : public EditorWindow
	{
	private:
		#pragma region Variables

		ImVec2	size;

		#pragma endregion

	public:
		#pragma region Constructors/Destructor

		GameWindow()							noexcept = default;
		GameWindow(const GameWindow& _w)		noexcept = default;
		GameWindow(GameWindow&& _w)				noexcept = default;
		GameWindow(const char* _name)			noexcept;
		GameWindow(const std::string& _name)	noexcept;
		GameWindow(std::string&& _name)			noexcept;
		~GameWindow()							noexcept = default;

		#pragma endregion

		#pragma region Properties

		Vec2	GetWindowSize() const noexcept;

		#pragma endregion

		#pragma region Methods

		void Update()	noexcept override;

		#pragma endregion
	};
}