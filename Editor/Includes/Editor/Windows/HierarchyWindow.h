#pragma once

#include <ComponentSystem/GameObject.h>

#include "Editor/EditorWindow.h"

namespace Galatea
{
	class HierarchyWindow : public EditorWindow
	{
	private:
		#pragma region Value
		bool				isFirstClick;
		GameObject*			selected;

		#pragma endregion

		#pragma region Methods

		void	GameObjectMenu(GameObject* _gameObject = nullptr)	noexcept;
		void	RenderCreateButton()								noexcept;
		void	RenderDeletePopUp()									noexcept;
		void	RenderSceneGraph(GameObject* _gameObject)			noexcept;

		#pragma endregion

	public:
		#pragma region Constructors/Destructor

		HierarchyWindow()							noexcept = default;
		HierarchyWindow(const HierarchyWindow& _w)	noexcept = default;
		HierarchyWindow(HierarchyWindow&& _w)		noexcept = default;
		HierarchyWindow(const char* _name)			noexcept;
		HierarchyWindow(const std::string& _name)	noexcept;
		HierarchyWindow(std::string&& _name)		noexcept;
		~HierarchyWindow()							noexcept = default;


		#pragma endregion

		#pragma region Methods

		void Update()	noexcept override;


		#pragma endregion
	};
}