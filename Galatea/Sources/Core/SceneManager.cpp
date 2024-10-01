#include <iostream>
#include "Core/SceneManager.h"
#include "Core/Render/Mesh.h"
#include "Core/Render/RHI.h"					//TODO remove
#include "Core/Render/Light.h"					//TODO remove
#include "Core/Camera/Camera.h"					//TODO remove
#include "Core/ResourcesManager.h"				//TODO remove
#include "Core/Render/Text2D.h"					//TODO remove
#include "Core/Render/Quad2D.h"					//TODO remove
#include "Physic/RigidBody.h"					//TODO remove
#include "Sound/AudioListener.h"				//TODO remove
#include "Sound/Sound.h"						//TOOD remove
#include "Game/CameraFPSRotation.h"				//TODO remove
#include "Game/Player.h"						//TODO remove
#include "Game/Gun.h"							//TODO remove
#include "Game/InteractableObject.h"			//TODO remove
#include "Game/Door.h"							//TODO remove
#include "Game/GameManager.h"					//TODO remove
#include "Game/MenuManager.h"					//TODO remove
#include "Game/WinTrigger.h"
#include "Game/GameMap.h"

using namespace Galatea;

SceneManager SceneManager::instance;

SceneManager::SceneManager() noexcept
{

}

SceneManager::~SceneManager() noexcept
{

}

SceneManager& SceneManager::GetInstance() noexcept
{
	return instance;
}

Physics& SceneManager::GetPhysics() noexcept
{
	return physics;
}


void SceneManager::SetCurrentScene(Scene* _scene) noexcept
{
	if (_scene != nullptr)
		instance.currentScene = _scene;
}

void SceneManager::Init() noexcept
{
	LogMsg("Scene Manage Init");
	if (scenesList.size() == 0)
	{
		physics.Init();

		std::cout << "load nothing. Creating a new basic Scene\n";

		currentSceneID = 0;
		currentScene = new Scene("Game");
		Scene::AddScene(currentScene);

		// GameManager
		GameObject* gameManager{ GameObject::CreateGameObject(Transform(), "GameManager") };
		gameManager->AddComponent(new Sound("Resources/Sounds/BackgroundMusic.mp3", "Music", true, G_SOUND_2D | G_SOUND_CREATESTREAM | G_SOUND_LOOP_NORMAL));
		gameManager->AddComponent(new GravityGun::GameManager());

		// Player 
		GameObject* player{ GameObject::CreateGameObject(Transform(Vec3{0, 10, 0}, Vec3{0, 0, 0}, Vec3{1.f, 1.f, 1.f}), "Player") };
			// Player RigidBody 
			RigidBody* rbPlayer{ new RigidBody() };
			player->AddComponent(rbPlayer);
			rbPlayer->SetGeometry(EGeometryType::BOX);
			rbPlayer->SetIsStatic(false);
			rbPlayer->SetColliderScale(player->GetWorldScale());
			rbPlayer->SetGravity({0, -9.81, 0});
			// Camera 
			GameObject* camera{ GameObject::CreateGameObject(player, Transform(Vec3{0, 0.75f, 0.5f}), "Camera") };
			camera->AddComponent(new GravityGun::CameraFPSRotation());
			camera->AddComponent(new Camera(camera));
			// AudioListener 
			camera->AddComponent(new AudioListener());
			// PlayerScript 
			GravityGun::Player* playerScript{ new GravityGun::Player() };
			player->AddComponent(playerScript);
			// GravityChange sound
			player->AddComponent(new Sound("Resources/Sounds/GravityChange.wav", "FX", false));
			// Freeze sound
			player->AddComponent(new Sound("Resources/Sounds/Freeze.wav", "FX", false));
			player->AddComponent(new Sound("Resources/Sounds/Unfreeze.wav", "FX", false));
			// GunScript 
			GravityGun::Gun* gun = new GravityGun::Gun();
			player->AddComponent(gun);

			GameObject* gunGameobject{ GameObject::CreateGameObject(camera, Transform(Vec3{0.7, -0.5f, 1}, Vec3{0, 130, 0}, Vec3{0.7, 0.7f, 0.7f}), "PortalGun") };
			gunGameobject->AddComponent(ResourcesManager::GetResource<Mesh>(ResourcesManager::CreateMeshResource("Resources/Meshes/PortalGun/PortalGun.obj")));

		GameScene();

        GameObject* goCursor{ GameObject::CreateGameObject2D("Cursor") };
		goCursor->AddComponent(Quad2D::CreateQuad2D("Resources/Textures/cross.png"));
		goCursor->transform.Scale(Vec3{ 0.06f, 0.06f});

		currentScene->Init();

		Scene* menuScene = new Scene("Menu");
		Scene::AddScene(menuScene);
		Scene::ChangeScene("Menu");
		
		GameObject* menuManager{ GameObject::CreateGameObject(menuScene->GetWorld(), Transform(), "MenuManager") };
		// Camera 
		GameObject* menuCam{ GameObject::CreateGameObject(menuScene->GetWorld(), Transform(), "MenuCam") };
		menuCam->AddComponent(new GravityGun::MenuManager());

		GameObject* quadGo{ GameObject::CreateGameObject2D(menuScene->GetWorld2D(), Transform(), "quadGo") };
		quadGo->AddComponent(Quad2D::CreateQuad2D("Resources/Textures/LaboratoryGround.jpg"));
		quadGo->GetComponent<Quad2D>()->SetUseProportion(false);
		GameObject* logoGo{ GameObject::CreateGameObject2D(menuScene->GetWorld2D(), Transform({0.65, -0.65, 0}, {}, {0.35, 0.35, 1}), "logoGo") };
		logoGo->AddComponent(Quad2D::CreateQuad2D("Resources/Textures/Logo_Galatea.png"));
		logoGo->GetComponent<Quad2D>()->SetUseProportion(false);
		GameObject* textGo{ GameObject::CreateGameObject2D(menuScene->GetWorld2D(), Transform(Vec3(-0.28, 0, 0)), "textGo") };
		textGo->AddComponent(Text2D::CreateText("Press SPACE / A to start !", "Resources/Fonts/Arial.ttf", Vec3(0, 0, 0)));
		
		menuCam->AddComponent(new Camera(menuCam));

		menuScene->Init();
	}
	else
		currentSceneID = 0;

	instance.physics.SetCurrentScene(currentSceneID);
}

void SceneManager::ChangeScene() noexcept
{
	currentSceneID = (unsigned int)changeSceneID;
	changeSceneID = -1;
	auto it = SceneManager::instance.scenesList.begin();
	for (unsigned int i = 0; i < currentSceneID; ++i)
		++it;
	currentScene = it->second.get();

	physics.SetCurrentScene(currentSceneID);
}

void SceneManager::Update() noexcept
{
	if (changeSceneID != -1)
		ChangeScene();
	currentScene->Update();
}

void SceneManager::FixedUpdate() noexcept
{
	currentScene->FixedUpdate();
}

void SceneManager::LateUpdate() noexcept
{
	currentScene->LateUpdate();
}

void SceneManager::Destroy() noexcept
{
	physics.Destroy();
	for (auto [f, s] : scenesList)
	{
		SetCurrentScene(s.get());
		s.~shared_ptr();
	}
	scenesList.clear();
	currentScene = nullptr;
}


