#include <iostream>
#include <functional>

#include "Core/Scene.h"
#include "Core/SceneManager.h"

#include "Core/Render/WindowManager.h"
#include "Core/Render/RHI.h"
#include "Core/Camera/Camera.h"
#include "Core/Render/Mesh2D.h"

using namespace Galatea;

#pragma region Constructors/Destructor

Scene::Scene() noexcept
	: isInit{}, world {	nullptr }, world2D{ nullptr }
{}

Scene::Scene(const char* _name) noexcept :
	isInit{},
	name{_name},
	componentsManager{ nullptr },
	world{ new GameObject("World") },
	world2D{ new GameObject("World2D") }
{
}

Scene::~Scene() noexcept
{
	gameObjectList.clear();
	gameObject2DList.clear();
	world.~shared_ptr();
	world2D.~shared_ptr();

	delete componentsManager;
	delete finalFBO;
	delete sceneFBO;
}

#pragma endregion

void Scene::Init() noexcept
{
	if (SceneManager::instance.currentScene == nullptr)
		SceneManager::SetCurrentScene(this);

	componentsManager = new ComponentsManager;
	perspectifProjectionMatrix = Mat4::CreatePerspectiveMatrix(1024, 800, 0.001f, 1000, 60);
	orthogonalProjectionMatrix = Mat4::CreateOrthogonalMatrix(-1, 1, -1, 1, 0, 1000);
	isInit = true;
	if (world.get() == nullptr)
	{
		std::shared_ptr<GameObject> temp(new GameObject("World"));
		world = temp;
	}
	if (world2D.get() == nullptr)
	{
		std::shared_ptr<GameObject> temp(new GameObject("World2D"));
		world2D = temp;
	}

	finalFBO = new Framebuffer;
	sceneFBO = new Framebuffer;

	std::function<void(std::vector<GameObject*>&, std::shared_ptr<GameObject>)> func;

	func = [this, &func](std::vector<GameObject*>& list ,std::shared_ptr<GameObject> go)
	{
		list.push_back(go.get());
		auto children = go->GetChildren();
		for (int i = 0; i < children.size(); ++i)
			func(list, children[i]);
	};

	func(gameObjectList, world);
	func(gameObject2DList, world2D);

	for (int i = 0; i < gameObjectList.size(); ++i)
	{
		std::vector<std::shared_ptr<Component>> components = gameObjectList[i]->GetComponentList();

		for (int i = 0; i < components.size(); ++i)
			componentsManager->AddComponent(components[i].get());
	}

	for (int i = 0; i < gameObject2DList.size(); ++i)
	{
		std::vector<std::shared_ptr<Component>> components = gameObject2DList[i]->GetComponentList();

		for (int i = 0; i < components.size(); ++i)
			componentsManager->AddComponent(components[i].get());
	}
}

void Scene::Update() noexcept
{
	componentsManager->Update();
}

void Scene::FixedUpdate() noexcept
{
	componentsManager->FixedUpdate();
}

void Scene::LateUpdate() noexcept
{
	componentsManager->LateUpdate();
}

void Scene::Resize(int _width, int _height) noexcept
{
	perspectifProjectionMatrix = Mat4::CreatePerspectiveMatrix(_width, _height, 0.001f, 1000, 60);
	finalFBO->Resize(_width, _height);
	for (auto it : gameObject2DList)
		if (Mesh2D* mesh = it->GetComponent<Mesh2D>())
			mesh->Resize(_width, _height);
}

void Scene::ResizeCameraScene(int _width, int _height) noexcept
{
	cameraScene.projectionMatrix = Mat4::CreatePerspectiveMatrix(_width, _height, 0.001f, 1000, 60);
	sceneFBO->Resize(_width, _height);
}

void Scene::ResizeScenes(int _width, int _height) noexcept
{
	RHI::SetViewport(_width, _height);
	for (auto it = SceneManager::instance.scenesList.begin(); it != SceneManager::instance.scenesList.end(); ++it)
		it->second->Resize(_width, _height);
}

void Scene::ResizeCameraEditor(int _width, int _height) noexcept
{
	RHI::SetViewport(_width, _height);
	for (auto it = SceneManager::instance.scenesList.begin(); it != SceneManager::instance.scenesList.end(); ++it)
		it->second->ResizeCameraScene(_width, _height);
}

GameObject* Scene::GetGameObjectByName(std::string _s) noexcept
{
	for (int i = 0; i < gameObjectList.size(); ++i)
	{
		if (gameObjectList[i]->GetName() == _s)
			return gameObjectList[i];
	}
	return nullptr;
}

void Scene::AddCamera(Camera* _camera) noexcept
{
	componentsManager->camList.push_back(_camera);
}

bool Scene::SetUsedCamera(unsigned int _index) noexcept
{
	if (_index < componentsManager->camList.size())
	{
		componentsManager->camList[componentsManager->usedCameraIndex]->isActive = false;
		componentsManager->usedCameraIndex = _index;
		componentsManager->camList[componentsManager->usedCameraIndex]->isActive = true;
		return true;
	}
	return false;
}

Camera* Scene::GetCamera(unsigned int _index) noexcept
{
	return _index < componentsManager->camList.size() ? componentsManager->camList[_index] : nullptr;
}

unsigned int Scene::GetCameraCount() const noexcept
{
	return componentsManager->camList.size();
}

Camera* Scene::GetCurrentCamera() noexcept
{
	if (componentsManager->camList.size() != 0)
		return componentsManager->camList[componentsManager->usedCameraIndex];
	else
		return nullptr;
}

const Camera* Scene::GetCurrentCamera() const noexcept
{
	if (componentsManager->camList.size() != 0)
		return componentsManager->camList[componentsManager->usedCameraIndex];
	else
		return nullptr;
}

const Framebuffer* Scene::GetFinalFramebuffer() const noexcept
{
	return finalFBO;
}

const Framebuffer* Scene::GetSceneFramebuffer() const noexcept
{
	return sceneFBO;
}

bool  Scene::DeleteGameObject(GameObject* _gO) noexcept
{
	auto it = std::find(gameObjectList.begin(), gameObjectList.end(), _gO);

	if (it == gameObjectList.end())
		return false;
	else
		gameObjectList.erase(it);
	
	if (SearchAndDestruct(world.get(), _gO))
		return true;

	LogError("Could not delete the gameobject selected from the scene tree");
	return false;
}


bool Scene::SearchAndDestruct(GameObject* _actualGO, GameObject* _toFind) noexcept
{
	for (auto it = _actualGO->GetChildren().begin(); it != _actualGO->GetChildren().end(); ++it)
	{
		if ((*it).get() != _toFind && SearchAndDestruct((*it).get(), _toFind))
			return true;
		else if ((*it).get() == _toFind)
		{
			_actualGO->GetChildren().erase(it);
			return true;
		}
	}
	return false;
}

void Scene::UpdateCameraInEditor() noexcept
{
	Scene::GetCurrentScene()->GetCameraInEditor().Update();
}

Scene* Scene::GetCurrentScene() noexcept
{
	return SceneManager::instance.currentScene;
}

void Scene::AddScene(Scene* newScene) noexcept
{
	SceneManager::instance.scenesList.insert(std::make_pair(newScene->GetName(), newScene));
	SceneManager::instance.physics.CreateScene();

	if (SceneManager::instance.currentScene == nullptr)
	{
		SceneManager::instance.currentScene = SceneManager::instance.scenesList[newScene->GetName()].get();
		SceneManager::instance.physics.SetCurrentScene(0);
	}
}

void Scene::AddScene(std::shared_ptr<Scene> newScene) noexcept
{
	SceneManager::instance.scenesList.insert(std::make_pair(newScene->GetName(), newScene));
	SceneManager::instance.physics.CreateScene();

	if (SceneManager::instance.currentScene == nullptr)
	{
		SceneManager::instance.currentScene = SceneManager::instance.scenesList[newScene->GetName()].get();
		SceneManager::instance.physics.SetCurrentScene(0);
	}
}

void Scene::ChangeScene(unsigned int _index) noexcept
{
	if (_index >= SceneManager::instance.scenesList.size())
		return;
	SceneManager::instance.changeSceneID = _index;
	auto it = SceneManager::instance.scenesList.begin();
	for (unsigned int i = 0; i < _index; ++i)
		++it;
}

void Scene::ChangeScene(const char* _name) noexcept
{
	auto it = SceneManager::instance.scenesList.find(_name);
	if (it == SceneManager::instance.scenesList.end())
		return;
	SceneManager::instance.changeSceneID = static_cast<unsigned int>(std::distance(SceneManager::instance.scenesList.begin(), it));
}

Camera* Scene::GetCurrentSceneCamera() noexcept
{
	return SceneManager::instance.currentScene->GetCurrentCamera();
}

unsigned int Scene::GetCurrentSceneIndex() noexcept
{
	return SceneManager::instance.currentSceneID;
}

const std::string& Scene::GetCurrentSceneName() noexcept
{
	return SceneManager::instance.currentScene->name;
}

const std::string& Scene::GetSceneName(unsigned int _index) noexcept
{
	if (_index < SceneManager::instance.scenesList.size())
		return "";
	auto it = SceneManager::instance.scenesList.begin();
	for (unsigned int i = 0; i < _index; ++i)
		++it;
	return it->first;
}

unsigned int Scene::GetSceneIndex(const char* _name) noexcept
{
	auto it = SceneManager::instance.scenesList.find(_name);
	if (it == SceneManager::instance.scenesList.end())
		return -1;
	return static_cast<unsigned int>(std::distance(SceneManager::instance.scenesList.begin(), it));
}

unsigned int Scene::GetSceneNumbers() noexcept
{
	return static_cast<unsigned int>(SceneManager::instance.scenesList.size());
}
