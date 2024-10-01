#include <Core/SceneManager.h>
#include <Core/Scene.h>
#include <Debug/Log.h>
#include <Core/Render/Mesh.h>
#include <Core/Render/Light.h>

#include "Editor/Windows/HierarchyWindow.h"
#include "Editor/Windows/InspectorWindow.h"
#include "ImGui/imgui.h"

using namespace Galatea;

#pragma region Constructors/Destructor

HierarchyWindow::HierarchyWindow(const char* _name) noexcept
	: EditorWindow{ _name }, selected{ nullptr }, isFirstClick{false}
{}

HierarchyWindow::HierarchyWindow(const std::string& _name) noexcept
	: EditorWindow{ _name }, selected{ nullptr }, isFirstClick{ false }
{}

HierarchyWindow::HierarchyWindow(std::string&& _name) noexcept
	: EditorWindow{ _name }, selected{ nullptr }, isFirstClick{ false }
{}

#pragma endregion

#pragma region Methods
 
void HierarchyWindow::GameObjectMenu(GameObject* _gameObject) noexcept
{
	if (ImGui::BeginMenu("3D Object"))
	{
		if (ImGui::MenuItem("Cube"))
		{
			GameObject* cube = GameObject::CreateGameObject(_gameObject, "Cube");
			cube->AddComponent(Mesh::CreateCube());
		}
		if (ImGui::MenuItem("Sphere"))
		{
			GameObject* cube = GameObject::CreateGameObject(_gameObject, "Sphere");
			cube->AddComponent(Mesh::CreateSphere());
		}
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Light"))
	{
		if (ImGui::MenuItem("Point light"))
		{
			GameObject* light = GameObject::CreateGameObject(_gameObject, "Point light");
			light->AddComponent(new Light(Light::ELightType::POINT));
		}
		if (ImGui::MenuItem("Directionnal light"))
		{
			GameObject* light = GameObject::CreateGameObject(_gameObject, "Directionnal light");
			light->AddComponent(new Light(Light::ELightType::DIRECTIONAL));
		}
		if (ImGui::MenuItem("Spot light"))
		{
			GameObject* light = GameObject::CreateGameObject(_gameObject, "Spot light");
			light->AddComponent(new Light(Light::ELightType::SPOT));
		}
		ImGui::EndMenu();
	}
}

void HierarchyWindow::RenderCreateButton() noexcept
{
	if (ImGui::Button("Create"))
		ImGui::OpenPopup("CreatePopup");

	if (ImGui::BeginPopup("CreatePopup"))
	{
		if (ImGui::MenuItem("Create empty")) 
		{
			GameObject::CreateGameObject("GameObject");
		}
		if (ImGui::MenuItem("Create empty child")) 
		{
			if (InspectorWindow::gameObject != nullptr)
				GameObject::CreateGameObject(InspectorWindow::gameObject, "GameObject");
			else
				LogMsg("Please select a GameObject in the scene decriptor");
		}
		GameObjectMenu();
		ImGui::EndPopup();
	}
}

void HierarchyWindow::RenderDeletePopUp() noexcept
{
	if (selected != nullptr && !ImGui::IsPopupOpen("DeletePopUp") && isFirstClick)
		ImGui::OpenPopup("DeletePopUp");

	if (ImGui::BeginPopup("DeletePopUp"))
	{
		if (ImGui::BeginMenu("Add Child"))
		{
			if (ImGui::MenuItem("Empty GameObject"))
				GameObject::CreateGameObject(selected, "GameObject");

			GameObjectMenu(selected);
			ImGui::EndMenu();
		}
		if (ImGui::MenuItem("Delete GameObject"))
		{
			InspectorWindow::gameObject = nullptr;
			if (Scene::GetCurrentScene()->DeleteGameObject(selected))
				LogMsg("GameObject deleted Successfully");

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

void HierarchyWindow::RenderSceneGraph(GameObject* _gameObject) noexcept
{
	ImGuiTreeNodeFlags	flags{ ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick };

	if (_gameObject->GetChildren().size() == 0)
		flags |= ImGuiTreeNodeFlags_Leaf;
	
	if (_gameObject == InspectorWindow::gameObject)
		flags |= ImGuiTreeNodeFlags_Selected;

	if (ImGui::TreeNodeEx(_gameObject->name.c_str(), flags))
	{
		if (ImGui::IsItemClicked())
		{
			InspectorWindow::gameObject = _gameObject;
			selected = nullptr;
		}
		if (ImGui::IsItemClicked(1))
		{
			isFirstClick = true;
			selected = _gameObject;
		}

		std::vector<std::shared_ptr<GameObject>>			children{ _gameObject->GetChildren() };
		std::vector<std::shared_ptr<GameObject>>::iterator	it;
		for (it = children.begin(); it != children.end(); ++it)
			RenderSceneGraph((*it).get());

		ImGui::TreePop();
	}
}

void HierarchyWindow::Update() noexcept
{
	if (isOpen)
	{
		ImGui::Begin("Hierarchy", &isOpen, ImGuiWindowFlags_NoCollapse);

		RenderCreateButton();

		if (ImGui::TreeNodeEx(/*SceneManager::GetCurrentSceneName().c_str()*/"Scene", ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_DefaultOpen))
		{
			std::vector<std::shared_ptr<GameObject>> gameObjects{ Scene::GetCurrentScene()->GetWorld()->GetChildren() };
			std::vector<std::shared_ptr<GameObject>>::iterator	it;
			//std::cout << "world child size = " << gameObjects.size()<< "\n";
			for (it = gameObjects.begin(); it != gameObjects.end(); ++it)
			{
				RenderSceneGraph((*it).get());
			}

			RenderSceneGraph(Scene::GetCurrentScene()->GetWorld2D());

			ImGui::TreePop();
		}
		RenderDeletePopUp();

		ImGui::End();
	}
}

#pragma endregion