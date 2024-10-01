#pragma once

#include "Editor/EditorWindow.h"

namespace Galatea
{
	class SceneWindow : public EditorWindow
	{
	private:
		#pragma region Variables

		ImVec2	size;

		#pragma endregion
	public:
		#pragma region Constructors/Destructor

		SceneWindow()							noexcept = default;
		SceneWindow(const SceneWindow& _w)		noexcept = default;
		SceneWindow(SceneWindow&& _w)			noexcept = default;
		SceneWindow(const char* _name)			noexcept;
		SceneWindow(const std::string& _name)	noexcept;
		SceneWindow(std::string&& _name)		noexcept;
		~SceneWindow()							noexcept = default;

		#pragma endregion

		#pragma region Methods

		void Update()	noexcept override;

		#pragma endregion
	};
}