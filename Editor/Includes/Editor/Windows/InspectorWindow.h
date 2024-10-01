#pragma once

#include "Editor/EditorWindow.h"
#include <ComponentSystem/Component.h>

namespace Galatea
{
	class GameObject;
	class Transform;

	class InspectorWindow : public EditorWindow
	{
	private:
		#pragma region Variables

		bool isFirstClick;

		#pragma endregion

		#pragma region Methods

		void	RenderTransform(Transform& _trs)	noexcept;

		#pragma endregion

	public:
		#pragma region Variables

		static GameObject*	gameObject;
		static Component*	selected;

		#pragma endregion

		#pragma region Constructors/Destructor

		InspectorWindow()							noexcept = default;
		InspectorWindow(const InspectorWindow& _w)	noexcept = default;
		InspectorWindow(InspectorWindow&& _w)		noexcept = default;
		InspectorWindow(const char* _name)			noexcept;
		InspectorWindow(const std::string& _name)	noexcept;
		InspectorWindow(std::string&& _name)		noexcept;
		~InspectorWindow()							noexcept = default;

		#pragma endregion

		#pragma region Methods
		void RenderAddComponentButton()					noexcept;
		void RenderDeletePopUp()						noexcept;

		void Update()	noexcept override;

		#pragma endregion
	};
}