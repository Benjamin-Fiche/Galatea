#include <ComponentSystem/GameObject.h>
#include <Core/Camera/Camera.h>

#include "ImGui/imgui.h"
#include "Editor/Windows/InspectorWindow.h"
#include "Editor/OnInspectorUI.h"
#include "Editor/Reflection/Reflector.h"

using namespace Galatea;

#pragma region Variables

GameObject* InspectorWindow::gameObject	{ nullptr };
Component*	InspectorWindow::selected	{ nullptr };

#pragma endregion

#pragma region Constructors/Destructor

InspectorWindow::InspectorWindow(const char* _name) noexcept
	: EditorWindow{ _name }
{}

InspectorWindow::InspectorWindow(const std::string& _name) noexcept
	: EditorWindow{ _name }
{}

InspectorWindow::InspectorWindow(std::string&& _name) noexcept
	: EditorWindow{ _name }
{}

#pragma endregion

#pragma region Methods

void InspectorWindow::RenderAddComponentButton() noexcept
{
	if (ImGui::Button("Add Component"))
		ImGui::OpenPopup("CreatePopup");

	if (ImGui::BeginPopup("CreatePopup"))
	{
		if (ImGui::MenuItem("Add Camera"))
		{
			gameObject->AddComponent(new Camera);
		}
		if (ImGui::BeginMenu("Add Light"))
		{
			if (ImGui::MenuItem("Point Light"))
			{
				gameObject->AddComponent(new Light(Light::ELightType::POINT));
			}
			if (ImGui::MenuItem("Directional Light"))
			{
				gameObject->AddComponent(new Light(Light::ELightType::DIRECTIONAL));
			}
			if (ImGui::MenuItem("Spot Light"))
			{
				gameObject->AddComponent(new Light(Light::ELightType::SPOT));
			}
			ImGui::EndMenu();
		}
		ImGui::EndPopup();
	}
}

void InspectorWindow::RenderDeletePopUp() noexcept
{
	if (selected != nullptr && !ImGui::IsPopupOpen("DeletePopUp") && isFirstClick)
		ImGui::OpenPopup("DeletePopUp");

	if (ImGui::BeginPopup("DeletePopUp"))
	{
		if (ImGui::MenuItem("Delete Component"))
		{
			//if (SceneManager::GetCurrentScene()->DeleteGameObject(selected))
			//	LogMsg("GameObject deleted Successfully");

			selected = nullptr;
		}
		ImGui::EndPopup();
	}

	if (ImGui::IsMouseReleased(0) || ImGui::IsMouseReleased(1))
		if (isFirstClick)
			isFirstClick = false;
		else
			selected = nullptr;
}


void InspectorWindow::RenderTransform(Transform& _trs) noexcept	/* TODO: move into Transform class -> OnInspectorUI */
{
	if (ImGui::TreeNodeEx("Transform", ImGuiTreeNodeFlags_Framed))
	{
		OnInspectorUI::DragValue("position", &_trs.position);
		OnInspectorUI::DragValue("rotation", &_trs.rotation);
		OnInspectorUI::DragValue("scale", &_trs.scale);

		ImGui::TreePop();
	}
}

void InspectorWindow::Update() noexcept
{
	if (isOpen)
	{
		ImGui::Begin("Inspector", &isOpen, ImGuiWindowFlags_NoCollapse);

		if (gameObject != nullptr)
		{
			RenderAddComponentButton();

			ImGui::Text(gameObject->name.c_str());
			std::vector<std::shared_ptr<Component>> compList = gameObject->GetComponentList();

			Reflector::Reflect(&gameObject->transform);

			for (int i = 0; i < compList.size(); ++i) // go through the component list to reflect them to the screen
				Reflector::Reflect(compList[i].get()); 
		}

		ImGui::End();
	}
}

#pragma endregion
