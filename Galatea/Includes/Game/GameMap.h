#pragma once
#include <iostream>
#include "Core/SceneManager.h"
#include "Core/Render/Mesh.h"
#include "Core/Render/RHI.h"					
#include "Core/Render/Light.h"					
#include "Core/Camera/Camera.h"
#include "Game/CameraFPSRotation.h"		
#include "Game/Player.h"				
#include "Game/Gun.h"					
#include "Game/InteractableObject.h"	
#include "Game/Door.h"					
#include "Game/GameManager.h"			
#include "Game/MenuManager.h"			
#include "Game/WinTrigger.h"
using namespace Galatea;

void GameScene() noexcept
{
	GameObject* Map{ GameObject::CreateGameObject(Transform({0, 0, 0}, {0, 0, 0}, {5, 5, 5}), "Map") };

	//ROOM 1
	GameObject* room1{ GameObject::CreateGameObject(Map, Transform({0, 0, 0}, {0, 0, 0}, {1, 1, 1}), "Room1") };
	{
		GameObject* light{ GameObject::CreateGameObject(room1, Transform({0, 2.5f, 0}, {0, 0, 0}, {1, 1, 1}), "room1 Light") };
		Light* lightComp = new Light(Light::ELightType::POINT);
		light->AddComponent(lightComp);
		lightComp->SetAttenuation({ 1, 0.14, 0.07 });
		lightComp->SetPower(3.f);

		GameObject* ground{ GameObject::CreateGameObject(room1, Transform({0, 0, 0}, {0, 0, 0}, {5, 0.2f, 5}), "room1 ground") };
		ground->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallDown.png"));
		// Wall Rigidbody 
		RigidBody* rbGround{ new RigidBody() };
		ground->AddComponent(rbGround);
		rbGround->SetIsStatic(true);
		rbGround->SetColliderScale(ground->GetWorldScale());
		rbGround->SetGravity(Vec3(0, -9.81f, 0));

		GameObject* roof{ GameObject::CreateGameObject(room1, Transform({0, 5, 0}, {0, 0, 0}, {5, 0.2f, 5}), "room1 roof") };
		roof->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallUp.png"));
		// Wall Rigidbody
		RigidBody* rbRoof{ new RigidBody() };
		roof->AddComponent(rbRoof);
		rbRoof->SetIsStatic(true);
		rbRoof->SetColliderScale(roof->GetWorldScale());
		rbRoof->SetGravity(Vec3(0, 9.81f, 0));

		GameObject* rightWall{ GameObject::CreateGameObject(room1, Transform({2.5f, 2.5f, 0}, {0, 0, 0}, {0.2f, 5, 5}), "room1 right") };
		rightWall->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallRight.png"));
		// Wall Rigidbody
		RigidBody* rbRightWall{ new RigidBody() };
		rightWall->AddComponent(rbRightWall);
		rbRightWall->SetIsStatic(true);
		rbRightWall->SetColliderScale(rightWall->GetWorldScale());
		rbRightWall->SetGravity(Vec3(9.81f, 0, 0));

		GameObject* leftWall{ GameObject::CreateGameObject(room1, Transform({-2.5f, 2.5f, 0}, {0, 0, 0}, {0.2f, 5, 5}), "room1 left") };
		leftWall->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallLeft.png"));
		// Wall Rigidbody
		RigidBody* rbLeftWall{ new RigidBody() };
		leftWall->AddComponent(rbLeftWall);
		rbLeftWall->SetIsStatic(true);
		rbLeftWall->SetColliderScale(leftWall->GetWorldScale());
		rbLeftWall->SetGravity(Vec3(-9.81f, 0, 0));

		GameObject* backWall{ GameObject::CreateGameObject(room1, Transform({0, 2.5f, -2.5f}, {0, 0, 0}, {5, 5, 0.2f}), "room1 back") };
		backWall->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallBack.png"));
		// Wall Rigidbody
		RigidBody* rbBackWall{ new RigidBody() };
		backWall->AddComponent(rbBackWall);
		rbBackWall->SetIsStatic(true);
		rbBackWall->SetColliderScale(backWall->GetWorldScale());
		rbBackWall->SetGravity(Vec3(0, 0, -9.81f));


		//front walls
		GameObject* frontWall1{ GameObject::CreateGameObject(room1, Transform({0, 1, 2.5f}, {0, 0, 0}, {5, 2, 0.2f}), "room1 front 1") };
		frontWall1->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallFront.png"));
		// Wall Rigidbody
		RigidBody* rbFrontWall1{ new RigidBody() };
		frontWall1->AddComponent(rbFrontWall1);
		rbFrontWall1->SetIsStatic(true);
		rbFrontWall1->SetColliderScale(frontWall1->GetWorldScale());
		rbFrontWall1->SetGravity(Vec3(0, 0, 9.81f));

		GameObject* frontWall2{ GameObject::CreateGameObject(room1, Transform({0, 4, 2.5f}, {0, 0, 0}, {5, 2, 0.2f}), "room1front 2") };
		frontWall2->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallFront.png"));
		// Wall Rigidbody
		RigidBody* rbFrontWall2{ new RigidBody() };
		frontWall2->AddComponent(rbFrontWall2);
		rbFrontWall2->SetIsStatic(true);
		rbFrontWall2->SetColliderScale(frontWall2->GetWorldScale());
		rbFrontWall2->SetGravity(Vec3(0, 0, 9.81f));

		GameObject* frontWall3{ GameObject::CreateGameObject(room1, Transform({-1.5, 2.5f, 2.5f}, {0, 0, 0}, {2, 1, 0.2f}), "room1 front 3") };
		frontWall3->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallFront.png"));
		// Wall Rigidbody
		RigidBody* rbFrontWall3{ new RigidBody() };
		frontWall3->AddComponent(rbFrontWall3);
		rbFrontWall3->SetIsStatic(true);
		rbFrontWall3->SetColliderScale(frontWall3->GetWorldScale());
		rbFrontWall3->SetGravity(Vec3(0, 0, 9.81f));

		GameObject* frontWall4{ GameObject::CreateGameObject(room1, Transform({1.5f, 2.5f, 2.5f}, {0, 0, 0}, {2, 1, 0.2f}), "room1 front 4") };
		frontWall4->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallFront.png"));
		// Wall Rigidbody
		RigidBody* rbFrontWall4{ new RigidBody() };
		frontWall4->AddComponent(rbFrontWall4);
		rbFrontWall4->SetIsStatic(true);
		rbFrontWall4->SetColliderScale(frontWall4->GetWorldScale());
		rbFrontWall4->SetGravity(Vec3(0, 0, 9.81f));

		// Door
		GameObject* door{ GameObject::CreateGameObject(room1, Transform(Vec3(0, 2.5f, 2.5f), Quaternion(1, 0, 0, 0), Vec3(1, 1, 0.2f)), "room 1 Door") };
		// DoorLeaf
		GameObject* doorLeaf{ GameObject::CreateGameObject(door, Transform(Vec3(0, 0, 0), Quaternion(1, 0, 0, 0), Vec3(1, 1, 1)), "DoorLeaf") };
		doorLeaf->AddComponent(Mesh::CreateCube("Resources/Textures/white.png"));
		RigidBody* doorLeafRB{ new RigidBody() };
		doorLeaf->AddComponent(doorLeafRB);
		doorLeafRB->SetColliderScale(doorLeaf->GetWorldScale());
		doorLeafRB->SetGravity({ 0, 0, 9.81f });
		doorLeafRB->SetIsStatic(true);
		doorLeafRB->SetFreezePosition({ 1, 1, 1 });
		doorLeafRB->SetFreezeRotation({ 1, 1, 1 });
		// Sound 
		door->AddComponent(new Sound("Resources/Sounds/DoorOpen.mp3", "FX", false, G_SOUND_3D | G_SOUND_CREATESAMPLE | G_SOUND_3D_LINEARROLLOFF));
		door->AddComponent(new Sound("Resources/Sounds/DoorClose.mp3", "FX", false, G_SOUND_3D | G_SOUND_CREATESAMPLE | G_SOUND_3D_LINEARROLLOFF));
		// Door script 
		door->AddComponent(new GravityGun::Door());
	}

	//ROOM 2
	GameObject* room2{ GameObject::CreateGameObject(Map, Transform({0, 0, 5}, {0, 0, 0}, {1, 1, 1}), "Room2") };
	{
		GameObject* light{ GameObject::CreateGameObject(room2, Transform({0, 2.5f, 0}, {0, 0, 0}, {1, 1, 1}), "room2 Light") };
		Light* lightComp = new Light(Light::ELightType::POINT);
		light->AddComponent(lightComp);
		lightComp->SetAttenuation({ 1, 0.14, 0.07 });
		lightComp->SetPower(3.f);

		GameObject* ground{ GameObject::CreateGameObject(room2, Transform({0, 0, 0}, {0, 0, 0}, {5, 0.2f, 5}), "room2 ground") };
		ground->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallDown.png"));
		// Wall Rigidbody 
		RigidBody* rbGround{ new RigidBody() };
		ground->AddComponent(rbGround);
		rbGround->SetIsStatic(true);
		rbGround->SetColliderScale(ground->GetWorldScale());
		rbGround->SetGravity(Vec3(0, -9.81f, 0));

		GameObject* roof{ GameObject::CreateGameObject(room2, Transform({0, 5, 0}, {0, 0, 0}, {5, 0.2f, 5}), "room2 roof") };
		roof->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallUp.png"));
		// Wall Rigidbody
		RigidBody* rbRoof{ new RigidBody() };
		roof->AddComponent(rbRoof);
		rbRoof->SetIsStatic(true);
		rbRoof->SetColliderScale(roof->GetWorldScale());
		rbRoof->SetGravity(Vec3(0, 9.81f, 0));

		GameObject* rightWall{ GameObject::CreateGameObject(room2, Transform({2.5f, 2.5f, 0}, {0, 0, 0}, {0.2f, 5, 5}), "room2 right") };
		rightWall->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallRight.png"));
		// Wall Rigidbody
		RigidBody* rbRightWall{ new RigidBody() };
		rightWall->AddComponent(rbRightWall);
		rbRightWall->SetIsStatic(true);
		rbRightWall->SetColliderScale(rightWall->GetWorldScale());
		rbRightWall->SetGravity(Vec3(9.81f, 0, 0));

		GameObject* leftWall{ GameObject::CreateGameObject(room2, Transform({-2.5f, 2.5f, 0}, {0, 0, 0}, {0.2f, 5, 5}), "room2 left") };
		leftWall->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallLeft.png"));
		// Wall Rigidbody
		RigidBody* rbLeftWall{ new RigidBody() };
		leftWall->AddComponent(rbLeftWall);
		rbLeftWall->SetIsStatic(true);
		rbLeftWall->SetColliderScale(leftWall->GetWorldScale());
		rbLeftWall->SetGravity(Vec3(-9.81f, 0, 0));


		//front walls
		GameObject* frontWall1{ GameObject::CreateGameObject(room2, Transform({0, 1, 2.5f}, {0, 0, 0}, {5, 2, 0.2f}), "room2 front 1") };
		frontWall1->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallBack.png"));
		// Wall Rigidbody
		RigidBody* rbFrontWall1{ new RigidBody() };
		frontWall1->AddComponent(rbFrontWall1);
		rbFrontWall1->SetIsStatic(true);
		rbFrontWall1->SetColliderScale(frontWall1->GetWorldScale());
		rbFrontWall1->SetGravity(Vec3(0, 0, -9.81f));

		GameObject* frontWall2{ GameObject::CreateGameObject(room2, Transform({0, 4, 2.5f}, {0, 0, 0}, {5, 2, 0.2f}), "room2 front 2") };
		frontWall2->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallBack.png"));
		// Wall Rigidbody
		RigidBody* rbFrontWall2{ new RigidBody() };
		frontWall2->AddComponent(rbFrontWall2);
		rbFrontWall2->SetIsStatic(true);
		rbFrontWall2->SetColliderScale(frontWall2->GetWorldScale());
		rbFrontWall2->SetGravity(Vec3(0, 0, -9.81f));

		GameObject* frontWall3{ GameObject::CreateGameObject(room2, Transform({-1.5, 2.5f, 2.5f}, {0, 0, 0}, {2, 1, 0.2f}), "room2 front 3") };
		frontWall3->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallBack.png"));
		// Wall Rigidbody
		RigidBody* rbFrontWall3{ new RigidBody() };
		frontWall3->AddComponent(rbFrontWall3);
		rbFrontWall3->SetIsStatic(true);
		rbFrontWall3->SetColliderScale(frontWall3->GetWorldScale());
		rbFrontWall3->SetGravity(Vec3(0, 0, -9.81f));

		GameObject* frontWall4{ GameObject::CreateGameObject(room2, Transform({1.5, 2.5f, 2.5f}, {0, 0, 0}, {2, 1, 0.2f}), "room2 front 4") };
		frontWall4->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallBack.png"));
		// Wall Rigidbody
		RigidBody* rbFrontWall4{ new RigidBody() };
		frontWall4->AddComponent(rbFrontWall4);
		rbFrontWall4->SetIsStatic(true);
		rbFrontWall4->SetColliderScale(frontWall4->GetWorldScale());
		rbFrontWall4->SetGravity(Vec3(0, 0, -9.81f));

		GameObject* Platform1{ GameObject::CreateGameObject(room2, Transform({0, 1.95f, -2.f}, {0, 0, 0}, {1, 0.2f, 1}), "room2 Platform 1") };
		Platform1->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallDown.png"));
		// Wall Rigidbody
		RigidBody* rbPlatform1{ new RigidBody() };
		Platform1->AddComponent(rbPlatform1);
		rbPlatform1->SetIsStatic(true);
		rbPlatform1->SetColliderScale(Platform1->GetWorldScale());
		rbPlatform1->SetGravity(Vec3(0, -9.81f, 0));

		GameObject* Platform2{ GameObject::CreateGameObject(room2, Transform({0, 3, 2}, {0, 0, 0}, {1, 0.2f, 1}), "room2 Platform 2") };
		Platform2->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallDown.png"));
		// Wall Rigidbody
		RigidBody* rbPlatform2{ new RigidBody() };
		Platform2->AddComponent(rbPlatform2);
		rbPlatform2->SetIsStatic(true);
		rbPlatform2->SetColliderScale(Platform2->GetWorldScale());
		rbPlatform2->SetGravity(Vec3(0, -9.81f, 0));

		GameObject* miniWall{ GameObject::CreateGameObject(room2, Transform({0, 2.5f, -1.5f}, {0, 0, 0}, {1, 1, 0.2f}), "room2 Mini Wall") };
		miniWall->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallFront.png"));
		// Wall Rigidbody
		RigidBody* rbminiWall{ new RigidBody() };
		miniWall->AddComponent(rbminiWall);
		rbminiWall->SetIsStatic(true);
		rbminiWall->SetColliderScale(miniWall->GetWorldScale());
		rbminiWall->SetGravity(Vec3(0, 0, 9.81f));

		// Door
		GameObject* door{ GameObject::CreateGameObject(room2, Transform(Vec3(0, 2.5f, 2.5f), Quaternion(1, 0, 0, 0), Vec3(1, 1, 0.2f)), "room 2 Door") };
		// DoorLeaf
		GameObject* doorLeaf{ GameObject::CreateGameObject(door, Transform(Vec3(0, 0, 0), Quaternion(1, 0, 0, 0), Vec3(1, 1, 1)), "DoorLeaf") };
		doorLeaf->AddComponent(Mesh::CreateCube("Resources/Textures/white.png"));
		RigidBody* doorLeafRB{ new RigidBody() };
		doorLeaf->AddComponent(doorLeafRB);
		doorLeafRB->SetColliderScale(doorLeaf->GetWorldScale());
		doorLeafRB->SetGravity({ 0, 9.81f,  0 });
		doorLeafRB->SetIsStatic(true);
		doorLeafRB->SetFreezePosition({ 1, 1, 1 });
		doorLeafRB->SetFreezeRotation({ 1, 1, 1 });
		// Sound 
		door->AddComponent(new Sound("Resources/Sounds/DoorOpen.mp3", "FX", false, G_SOUND_3D | G_SOUND_CREATESAMPLE | G_SOUND_3D_LINEARROLLOFF));
		door->AddComponent(new Sound("Resources/Sounds/DoorClose.mp3", "FX", false, G_SOUND_3D | G_SOUND_CREATESAMPLE | G_SOUND_3D_LINEARROLLOFF));
		// Door script 
		door->AddComponent(new GravityGun::Door());
	}

	//ROOM 3
	GameObject* room3{ GameObject::CreateGameObject(Map, Transform({0, 0, 12.5f}, {0, 0, 0}, {1, 1, 1}), "Room3") };
	{
		GameObject* light{ GameObject::CreateGameObject(room3, Transform({0, 2.5f, 0}, {0, 0, 0}, {1, 1, 1}), "room3 Light") };
		Light* lightComp = new Light(Light::ELightType::POINT);
		light->AddComponent(lightComp);
		lightComp->SetAttenuation({ 1, 0.09f, 0.032f });
		lightComp->SetPower(3.f);

		GameObject* roof{ GameObject::CreateGameObject(room3, Transform({0, 5, 0}, {0, 0, 0}, {5, 0.2f, 10}), "room3 roof") };
		roof->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallDown.png"));
		// Wall Rigidbody
		RigidBody* rbRoof{ new RigidBody() };
		roof->AddComponent(rbRoof);
		rbRoof->SetIsStatic(true);
		rbRoof->SetColliderScale(roof->GetWorldScale());
		rbRoof->SetGravity(Vec3(0, -9.81f, 0));

		GameObject* rightWall{ GameObject::CreateGameObject(room3, Transform({2.5f, 2.5f, 0}, {0, 0, 0}, {0.2f, 5, 10}), "room3 right") };
		rightWall->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallDown.png"));
		// Wall Rigidbody
		RigidBody* rbRightWall{ new RigidBody() };
		rightWall->AddComponent(rbRightWall);
		rbRightWall->SetIsStatic(true);
		rbRightWall->SetColliderScale(rightWall->GetWorldScale());
		rbRightWall->SetGravity(Vec3(0, -9.81f, 0));

		GameObject* leftWall{ GameObject::CreateGameObject(room3, Transform({-2.5f, 2.5f, 0}, {0, 0, 0}, {0.2f, 5, 10}), "room3 left") };
		leftWall->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallDown.png"));
		// Wall Rigidbody
		RigidBody* rbLeftWall{ new RigidBody() };
		leftWall->AddComponent(rbLeftWall);
		rbLeftWall->SetIsStatic(true);
		rbLeftWall->SetColliderScale(leftWall->GetWorldScale());
		rbLeftWall->SetGravity(Vec3(0, -9.81f, 0));

		GameObject* ground{ GameObject::CreateGameObject(room3, Transform({0, 0, -1.58f}, {0, 0, 0}, {5, 0.2f, 6.888f}), "room3 ground") };
		ground->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallDown.png"));
		// Wall Rigidbody
		RigidBody* rbGround{ new RigidBody() };
		ground->AddComponent(rbGround);
		rbGround->SetIsStatic(true);
		rbGround->SetColliderScale(ground->GetWorldScale());
		rbGround->SetGravity(Vec3(0, -9.81f, 0));

		GameObject* slope{ GameObject::CreateGameObject(room3, Transform({0, -0.424, 3.384f}, {15, 0, 0}, {5, 0.2f, 3.2899f}), "room3 slope") };
		slope->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallDown.png"));
		// Wall Rigidbody
		RigidBody* rbSlope{ new RigidBody() };
		slope->AddComponent(rbSlope);
		rbSlope->SetIsStatic(true);
		rbSlope->SetColliderScale(slope->GetWorldScale());
		rbSlope->SetGravity(Vec3(0, -9.81f, 0));

		GameObject* slopeWallLeft{ GameObject::CreateGameObject(room3, Transform({-2.5f, -1, 3.5f}, {0, 0, 0}, {0.2f, 2, 3}), "room3 slope Wall Left") };
		slopeWallLeft->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallDown.png"));
		// Wall Rigidbody
		RigidBody* rbSlopeWallLeft{ new RigidBody() };
		slopeWallLeft->AddComponent(rbSlopeWallLeft);
		rbSlopeWallLeft->SetIsStatic(true);
		rbSlopeWallLeft->SetColliderScale(slopeWallLeft->GetWorldScale());
		rbSlopeWallLeft->SetGravity(Vec3(0, -9.81f, 0));

		GameObject* slopeWallRight{ GameObject::CreateGameObject(room3, Transform({2.5f, -1, 3.5f}, {0, 0, 0}, {0.2f, 2, 3}), "room3 slope Wall Right") };
		slopeWallRight->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallDown.png"));
		// Wall Rigidbody
		RigidBody* rbSlopeWallRight{ new RigidBody() };
		slopeWallLeft->AddComponent(rbSlopeWallRight);
		rbSlopeWallRight->SetIsStatic(true);
		rbSlopeWallRight->SetColliderScale(slopeWallRight->GetWorldScale());
		rbSlopeWallRight->SetGravity(Vec3(0, -9.81f, 0));


		//front walls
		GameObject* frontWall1{ GameObject::CreateGameObject(room3, Transform({0, 3, 5}, {0, 0, 0}, {5, 4, 0.2f}), "room3 front 1") };
		frontWall1->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallDown.png"));
		// Wall Rigidbody
		RigidBody* rbFrontWall1{ new RigidBody() };
		frontWall1->AddComponent(rbFrontWall1);
		rbFrontWall1->SetIsStatic(true);
		rbFrontWall1->SetColliderScale(frontWall1->GetWorldScale());
		rbFrontWall1->SetGravity(Vec3(0, -9.81f, 0));

		GameObject* frontWall2{ GameObject::CreateGameObject(room3, Transform({0, -0.5f, 5}, {0, 0, 0}, {5, 1, 0.2f}), "room3 front 2") };
		frontWall2->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallDown.png"));
		// Wall Rigidbody
		RigidBody* rbFrontWall2{ new RigidBody() };
		frontWall2->AddComponent(rbFrontWall2);
		rbFrontWall2->SetIsStatic(true);
		rbFrontWall2->SetColliderScale(frontWall2->GetWorldScale());
		rbFrontWall2->SetGravity(Vec3(0, -9.81f, 0));

		GameObject* frontWall3{ GameObject::CreateGameObject(room3, Transform({-1.5, 0.5f, 5}, {0, 0, 0}, {2, 1, 0.2f}), "room3 front 3") };
		frontWall3->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallDown.png"));
		// Wall Rigidbody
		RigidBody* rbFrontWall3{ new RigidBody() };
		frontWall3->AddComponent(rbFrontWall3);
		rbFrontWall3->SetIsStatic(true);
		rbFrontWall3->SetColliderScale(frontWall3->GetWorldScale());
		rbFrontWall3->SetGravity(Vec3(0, -9.81f, 0));

		GameObject* frontWall4{ GameObject::CreateGameObject(room3, Transform({1.5, 0.5f, 5}, {0, 0, 0}, {2, 1, 0.2f}), "room3 front 4") };
		frontWall4->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallDown.png"));
		// Wall Rigidbody
		RigidBody* rbFrontWall4{ new RigidBody() };
		frontWall4->AddComponent(rbFrontWall4);
		rbFrontWall4->SetIsStatic(true);
		rbFrontWall4->SetColliderScale(frontWall4->GetWorldScale());
		rbFrontWall4->SetGravity(Vec3(0, -9.81f, 0));

		GameObject* Platform1{ GameObject::CreateGameObject(room3, Transform({0, 0, 4.7f}, {0, 0, 0}, {1.5f, 0.2f, 0.5f}), "room3 Platform") };
		Platform1->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallDown.png"));
		// Wall Rigidbody
		RigidBody* rbPlatform1{ new RigidBody() };
		Platform1->AddComponent(rbPlatform1);
		rbPlatform1->SetIsStatic(true);
		rbPlatform1->SetColliderScale(Platform1->GetWorldScale());
		rbPlatform1->SetGravity(Vec3(0, -9.81f, 0));

		GameObject* interactablePlatform{ GameObject::CreateGameObject(Transform({0, 24.5f, 76.125f}, {0, 0, 0}, {10, 1, 20}), "room3 interactablePlatform") };
		interactablePlatform->AddComponent(Mesh::CreateCube("Resources/Textures/white.png"));
		// Ground Rigidbody 
		RigidBody* rbInteractablePlatform{ new RigidBody() };
		interactablePlatform->AddComponent(rbInteractablePlatform);
		rbInteractablePlatform->SetIsStatic(false);
		rbInteractablePlatform->SetColliderScale(interactablePlatform->GetWorldScale());
		rbInteractablePlatform->SetGravity(Vec3(0, 9.81, 0));
		// Interactable Obect 
		interactablePlatform->AddComponent(new GravityGun::InteractableObject());

		// Door
		GameObject* door{ GameObject::CreateGameObject(room3, Transform(Vec3(0, 0.5f, 5), Quaternion(1, 0, 0, 0), Vec3(1, 1, 0.2f)), "room 3 Door") };
		// DoorLeaf
		GameObject* doorLeaf{ GameObject::CreateGameObject(door, Transform(Vec3(0, 0, 0), Quaternion(1, 0, 0, 0), Vec3(1, 1, 1)), "DoorLeaf") };
		doorLeaf->AddComponent(Mesh::CreateCube("Resources/Textures/white.png"));
		RigidBody* doorLeafRB{ new RigidBody() };
		doorLeaf->AddComponent(doorLeafRB);
		doorLeafRB->SetColliderScale(doorLeaf->GetWorldScale());
		doorLeafRB->SetGravity({ 0, -9.81f,  0 });
		doorLeafRB->SetIsStatic(true);
		doorLeafRB->SetFreezePosition({ 1, 1, 1 });
		doorLeafRB->SetFreezeRotation({ 1, 1, 1 });
		// Sound 
		door->AddComponent(new Sound("Resources/Sounds/DoorOpen.mp3", "FX", false, G_SOUND_3D | G_SOUND_CREATESAMPLE | G_SOUND_3D_LINEARROLLOFF));
		door->AddComponent(new Sound("Resources/Sounds/DoorClose.mp3", "FX", false, G_SOUND_3D | G_SOUND_CREATESAMPLE | G_SOUND_3D_LINEARROLLOFF));
		// Door script 
		door->AddComponent(new GravityGun::Door());
	}

	//ROOM 4
	GameObject* room4{ GameObject::CreateGameObject(Map, Transform({0, 0, 20}, {0, 0, 0}, {1, 1, 1}), "Room4") };
	{
		GameObject* light{ GameObject::CreateGameObject(room4, Transform({0, 2.5f, 0}, {0, 0, 0}, {1, 1, 1}), "room4 Light") };
		Light* lightComp = new Light(Light::ELightType::POINT);
		light->AddComponent(lightComp);
		lightComp->SetAttenuation({ 1, 0.14, 0.07 });
		lightComp->SetPower(3.f);

		GameObject* ground{ GameObject::CreateGameObject(room4, Transform({0, 0, 0}, {0, 0, 0}, {5, 0.2f, 5}), "room4 ground") };
		ground->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallDown.png"));
		// Wall Rigidbody 
		RigidBody* rbGround{ new RigidBody() };
		ground->AddComponent(rbGround);
		rbGround->SetIsStatic(true);
		rbGround->SetColliderScale(ground->GetWorldScale());
		rbGround->SetGravity(Vec3(0, -9.81f, 0));

		GameObject* roof{ GameObject::CreateGameObject(room4, Transform({0, 5, 0}, {0, 0, 0}, {5, 0.2f, 5}), "room4 roof") };
		roof->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallUp.png"));
		// Wall Rigidbody
		RigidBody* rbRoof{ new RigidBody() };
		roof->AddComponent(rbRoof);
		rbRoof->SetIsStatic(true);
		rbRoof->SetColliderScale(roof->GetWorldScale());
		rbRoof->SetGravity(Vec3(0, 9.81f, 0));

		GameObject* rightWall{ GameObject::CreateGameObject(room4, Transform({2.5f, 2.5f, 0}, {0, 0, 0}, {0.2f, 5, 5}), "room4 right") };
		rightWall->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallRight.png"));
		// Wall Rigidbody
		RigidBody* rbRightWall{ new RigidBody() };
		rightWall->AddComponent(rbRightWall);
		rbRightWall->SetIsStatic(true);
		rbRightWall->SetColliderScale(rightWall->GetWorldScale());
		rbRightWall->SetGravity(Vec3(9.81f, 0, 0));

		GameObject* leftWall{ GameObject::CreateGameObject(room4, Transform({-2.5f, 2.5f, 0}, {0, 0, 0}, {0.2f, 5, 5}), "room4 left") };
		leftWall->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallLeft.png"));
		// Wall Rigidbody
		RigidBody* rbLeftWall{ new RigidBody() };
		leftWall->AddComponent(rbLeftWall);
		rbLeftWall->SetIsStatic(true);
		rbLeftWall->SetColliderScale(leftWall->GetWorldScale());
		rbLeftWall->SetGravity(Vec3(-9.81f, 0, 0));

		//front walls
		GameObject* frontWall1{ GameObject::CreateGameObject(room4, Transform({0, 1, 2.5f}, {0, 0, 0}, {5, 2, 0.2f}), "room4 front 1") };
		frontWall1->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallFront.png"));
		// Wall Rigidbody
		RigidBody* rbFrontWall1{ new RigidBody() };
		frontWall1->AddComponent(rbFrontWall1);
		rbFrontWall1->SetIsStatic(true);
		rbFrontWall1->SetColliderScale(frontWall1->GetWorldScale());
		rbFrontWall1->SetGravity(Vec3(0, 0, 9.81f));

		GameObject* frontWall2{ GameObject::CreateGameObject(room4, Transform({0, 4, 2.5f}, {0, 0, 0}, {5, 2, 0.2f}), "room4 front 2") };
		frontWall2->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallFront.png"));
		// Wall Rigidbody
		RigidBody* rbFrontWall2{ new RigidBody() };
		frontWall2->AddComponent(rbFrontWall2);
		rbFrontWall2->SetIsStatic(true);
		rbFrontWall2->SetColliderScale(frontWall2->GetWorldScale());
		rbFrontWall2->SetGravity(Vec3(0, 0, 9.81f));

		GameObject* frontWall3{ GameObject::CreateGameObject(room4, Transform({-1.5f, 2.5f, 2.5f}, {0, 0, 0}, {2, 1, 0.2f}), "room4 front 3") };
		frontWall3->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallFront.png"));
		// Wall Rigidbody
		RigidBody* rbFrontWall3{ new RigidBody() };
		frontWall3->AddComponent(rbFrontWall3);
		rbFrontWall3->SetIsStatic(true);
		rbFrontWall3->SetColliderScale(frontWall3->GetWorldScale());
		rbFrontWall3->SetGravity(Vec3(0, 0, 9.81f));

		GameObject* frontWall4{ GameObject::CreateGameObject(room4, Transform({1.5f, 2.5f, 2.5f}, {0, 0, 0}, {2, 1, 0.2f}), "room4 front 4") };
		frontWall4->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallFront.png"));
		// Wall Rigidbody
		RigidBody* rbFrontWall4{ new RigidBody() };
		frontWall4->AddComponent(rbFrontWall4);
		rbFrontWall4->SetIsStatic(true);
		rbFrontWall4->SetColliderScale(frontWall4->GetWorldScale());
		rbFrontWall4->SetGravity(Vec3(0, 0, 9.81f));


		GameObject* interactableCube{ GameObject::CreateGameObject(Transform({0, 1.5f, 111}, {0, 0, 0}, {4.f, 2.5f, 4.f}), "room4 interactableCube") };
		interactableCube->AddComponent(Mesh::CreateCube("Resources/Textures/white.png"));
		// Ground Rigidbody 
		RigidBody* rbInteractableCube{ new RigidBody() };
		interactableCube->AddComponent(rbInteractableCube);
		rbInteractableCube->SetIsStatic(false);
		rbInteractableCube->SetColliderScale(interactableCube->transform.scale);
		rbInteractableCube->SetGravity(Vec3(0, -9.81, 0));
		// Interactable Obect 
		interactableCube->AddComponent(new GravityGun::InteractableObject());

		// Door
		GameObject* door{ GameObject::CreateGameObject(room4, Transform(Vec3(0, 2.5f, 2.5f), Quaternion(1, 0, 0, 0), Vec3(1, 1, 0.2f)), "room 4 Door") };
		// DoorLeaf
		GameObject* doorLeaf{ GameObject::CreateGameObject(door, Transform(Vec3(0, 0, 0), Quaternion(1, 0, 0, 0), Vec3(1, 1, 1)), "DoorLeaf") };
		doorLeaf->AddComponent(Mesh::CreateCube("Resources/Textures/white.png"));
		RigidBody* doorLeafRB{ new RigidBody() };
		doorLeaf->AddComponent(doorLeafRB);
		doorLeafRB->SetColliderScale(doorLeaf->GetWorldScale());
		doorLeafRB->SetGravity({ 0, -9.81f, 0 });
		doorLeafRB->SetIsStatic(true);
		doorLeafRB->SetFreezePosition({ 1, 1, 1 });
		doorLeafRB->SetFreezeRotation({ 1, 1, 1 });
		// Sound 
		door->AddComponent(new Sound("Resources/Sounds/DoorOpen.mp3", "FX", false, G_SOUND_3D | G_SOUND_CREATESAMPLE | G_SOUND_3D_LINEARROLLOFF));
		door->AddComponent(new Sound("Resources/Sounds/DoorClose.mp3", "FX", false, G_SOUND_3D | G_SOUND_CREATESAMPLE | G_SOUND_3D_LINEARROLLOFF));
		// Door script 
		door->AddComponent(new GravityGun::Door());
	}

	//ROOM 5
	GameObject* room5{ GameObject::CreateGameObject(Map, Transform({2.5f, 2.5f, 27.5}, {0, 0, 0}, {1, 1, 1}), "Room5") };
	{
		GameObject* light1{ GameObject::CreateGameObject(room5, Transform({-2, 0.5f, 0}, {0, 0, 0}, {1, 1, 1}), "room5 Light 1") };
		Light* lightComp1 = new Light(Light::ELightType::POINT);
		light1->AddComponent(lightComp1);
		lightComp1->SetAttenuation({ 1, 0.09f, 0.032f });
		lightComp1->SetPower(3.f);

		GameObject* light2{ GameObject::CreateGameObject(room5, Transform({0, 3, 7.5f}, {0, 0, 0}, {1, 1, 1}), "room5 Light 2") };
		Light* lightComp2 = new Light(Light::ELightType::POINT);
		light2->AddComponent(lightComp2);
		lightComp2->SetAttenuation({ 1, 0.09f, 0.032f });
		lightComp2->SetPower(3.f);

		GameObject* ground{ GameObject::CreateGameObject(room5, Transform({0, -2.5f, 2.5f}, {0, 0, 0}, {10, 0.2f, 15}), "room5 ground") };
		ground->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallDown.png"));
		// Wall Rigidbody 
		RigidBody* rbGround{ new RigidBody() };
		ground->AddComponent(rbGround);
		rbGround->SetIsStatic(true);
		rbGround->SetColliderScale(ground->GetWorldScale());
		rbGround->SetGravity(Vec3(0, -9.81f, 0));

		GameObject* roof{ GameObject::CreateGameObject(room5, Transform({0, 7.5f, 2.5f}, {0, 0, 0}, {10, 0.2f, 15}), "room5 roof") };
		roof->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallUp.png"));
		// Wall Rigidbody
		RigidBody* rbRoof{ new RigidBody() };
		roof->AddComponent(rbRoof);
		rbRoof->SetIsStatic(true);
		rbRoof->SetColliderScale(roof->GetWorldScale());
		rbRoof->SetGravity(Vec3(0, 9.81f, 0));

		GameObject* rightWall{ GameObject::CreateGameObject(room5, Transform({5, 2.5f, 2.5f}, {0, 0, 0}, {0.2f, 10, 15}), "room5 right") };
		rightWall->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallRight.png"));
		// Wall Rigidbody
		RigidBody* rbRightWall{ new RigidBody() };
		rightWall->AddComponent(rbRightWall);
		rbRightWall->SetIsStatic(true);
		rbRightWall->SetColliderScale(rightWall->GetWorldScale());
		rbRightWall->SetGravity(Vec3(9.81f, 0, 0));

		GameObject* leftWall{ GameObject::CreateGameObject(room5, Transform({-5, 2.5f, 0}, {0, 0, 0}, {0.2f, 10, 10}), "room5 left") };
		leftWall->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallLeft.png"));
		// Wall Rigidbody
		RigidBody* rbLeftWall{ new RigidBody() };
		leftWall->AddComponent(rbLeftWall);
		rbLeftWall->SetIsStatic(true);
		rbLeftWall->SetColliderScale(leftWall->GetWorldScale());
		rbLeftWall->SetGravity(Vec3(-9.81f, 0, 0));

		GameObject* leftDoorWall1{ GameObject::CreateGameObject(room5, Transform({-5, -0.5f, 7.5f}, {0, 0, 0}, {0.2f, 4, 5}), "room5 leftDoorWall 1") };
		leftDoorWall1->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallLeft.png"));
		// Wall Rigidbody
		RigidBody* rbLeftDoorWall1{ new RigidBody() };
		leftDoorWall1->AddComponent(rbLeftDoorWall1);
		rbLeftDoorWall1->SetIsStatic(true);
		rbLeftDoorWall1->SetColliderScale(leftDoorWall1->GetWorldScale());
		rbLeftDoorWall1->SetGravity(Vec3(-9.81f, 0, 0));

		GameObject* leftDoorWall2{ GameObject::CreateGameObject(room5, Transform({-5, 5.5f, 7.5f}, {0, 0, 0}, {0.2f, 4, 5}), "room5 leftDoorWall 2") };
		leftDoorWall2->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallLeft.png"));
		// Wall Rigidbody
		RigidBody* rbLeftDoorWall2{ new RigidBody() };
		leftDoorWall2->AddComponent(rbLeftDoorWall2);
		rbLeftDoorWall2->SetIsStatic(true);
		rbLeftDoorWall2->SetColliderScale(leftDoorWall2->GetWorldScale());
		rbLeftDoorWall2->SetGravity(Vec3(-9.81f, 0, 0));

		GameObject* leftDoorWall3{ GameObject::CreateGameObject(room5, Transform({-5, 2.5f, 9.25f}, {0, 0, 0}, {0.2f, 2, 1.5f}), "room5 leftDoorWall 3") };
		leftDoorWall3->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallLeft.png"));
		// Wall Rigidbody
		RigidBody* rbLeftDoorWall3{ new RigidBody() };
		leftDoorWall3->AddComponent(rbLeftDoorWall3);
		rbLeftDoorWall3->SetIsStatic(true);
		rbLeftDoorWall3->SetColliderScale(leftDoorWall3->GetWorldScale());
		rbLeftDoorWall3->SetGravity(Vec3(-9.81f, 0, 0));

		GameObject* leftDoorWall4{ GameObject::CreateGameObject(room5, Transform({-5, 2.5f, 5.75f}, {0, 0, 0}, {0.2f, 2, 1.5f}), "room5 leftDoorWall 4") };
		leftDoorWall4->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallLeft.png"));
		// Wall Rigidbody
		RigidBody* rbLeftDoorWall4{ new RigidBody() };
		leftDoorWall4->AddComponent(rbLeftDoorWall4);
		rbLeftDoorWall4->SetIsStatic(true);
		rbLeftDoorWall4->SetColliderScale(leftDoorWall4->GetWorldScale());
		rbLeftDoorWall4->SetGravity(Vec3(-9.81f, 0, 0));

		GameObject* frontWall{ GameObject::CreateGameObject(room5, Transform({0, 2.5f, 10}, {0, 0, 0}, {10, 10, 0.2f}), "room5 front") };
		frontWall->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallFront.png"));
		// Wall Rigidbody
		RigidBody* rbFrontWall{ new RigidBody() };
		frontWall->AddComponent(rbFrontWall);
		rbFrontWall->SetIsStatic(true);
		rbFrontWall->SetColliderScale(frontWall->GetWorldScale());
		rbFrontWall->SetGravity(Vec3(0, 0, 9.81f));

		GameObject* backWall{ GameObject::CreateGameObject(room5, Transform({0, 5, -4.9f}, {0, 0, 0}, {10, 5, 0.2f}), "room5 back") };
		backWall->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallBack.png"));
		// Wall Rigidbody
		RigidBody* rbBackWall{ new RigidBody() };
		backWall->AddComponent(rbBackWall);
		rbBackWall->SetIsStatic(true);
		rbBackWall->SetColliderScale(backWall->GetWorldScale());
		rbBackWall->SetGravity(Vec3(0, 0, -9.81f));

		GameObject* backWallDoor1{ GameObject::CreateGameObject(room5, Transform({-2.5f, 1.5f, -4.9f}, {0, 0, 0}, {5, 2, 0.2f}), "room5 back door 1") };
		backWallDoor1->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallBack.png"));
		// Wall Rigidbody
		RigidBody* rbBackWallDoor1{ new RigidBody() };
		backWallDoor1->AddComponent(rbBackWallDoor1);
		rbBackWallDoor1->SetIsStatic(true);
		rbBackWallDoor1->SetColliderScale(backWallDoor1->GetWorldScale());
		rbBackWallDoor1->SetGravity(Vec3(0, 0, -9.81f));

		GameObject* backWallDoor2{ GameObject::CreateGameObject(room5, Transform({-2.5f, -1.5f, -4.9f}, {0, 0, 0}, {5, 2, 0.2f}), "room5 back door 2") };
		backWallDoor2->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallBack.png"));
		// Wall Rigidbody
		RigidBody* rbBackWallDoor2{ new RigidBody() };
		backWallDoor2->AddComponent(rbBackWallDoor2);
		rbBackWallDoor2->SetIsStatic(true);
		rbBackWallDoor2->SetColliderScale(backWallDoor2->GetWorldScale());
		rbBackWallDoor2->SetGravity(Vec3(0, 0, -9.81f));

		GameObject* backWallDoor3{ GameObject::CreateGameObject(room5, Transform({-1, 0, -4.9f}, {0, 0, 0}, {2, 1, 0.2f}), "room5 back door 3") };
		backWallDoor3->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallBack.png"));
		// Wall Rigidbody
		RigidBody* rbBackWallDoor3{ new RigidBody() };
		backWallDoor3->AddComponent(rbBackWallDoor3);
		rbBackWallDoor3->SetIsStatic(true);
		rbBackWallDoor3->SetColliderScale(backWallDoor3->GetWorldScale());
		rbBackWallDoor3->SetGravity(Vec3(0, 0, -9.81f));

		GameObject* backWallDoor4{ GameObject::CreateGameObject(room5, Transform({-4, 0, -4.9f}, {0, 0, 0}, {2, 1, 0.2f}), "room5 back door 4") };
		backWallDoor4->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallBack.png"));
		// Wall Rigidbody
		RigidBody* rbBackWallDoor4{ new RigidBody() };
		backWallDoor4->AddComponent(rbBackWallDoor4);
		rbBackWallDoor4->SetIsStatic(true);
		rbBackWallDoor4->SetColliderScale(backWallDoor4->GetWorldScale());
		rbBackWallDoor4->SetGravity(Vec3(0, 0, -9.81f));

		GameObject* insideWall1{ GameObject::CreateGameObject(room5, Transform({-1.5f, 2.5f, 5}, {0, 0, 0}, {7, 10, 0.2f}), "room5 inside 1") };
		insideWall1->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallFront.png"));
		// Wall Rigidbody
		RigidBody* rbInsideWall1{ new RigidBody() };
		insideWall1->AddComponent(rbInsideWall1);
		rbInsideWall1->SetIsStatic(true);
		rbInsideWall1->SetColliderScale(insideWall1->GetWorldScale());
		rbInsideWall1->SetGravity(Vec3(0, 0, 9.81f));

		GameObject* insideWall2{ GameObject::CreateGameObject(room5, Transform({3.5f, 0.5f, 5}, {0, 0, 0}, {3, 6, 0.2f}), "room5 inside 2") };
		insideWall2->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallFront.png"));
		// Wall Rigidbody
		RigidBody* rbInsideWall2{ new RigidBody() };
		insideWall2->AddComponent(rbInsideWall2);
		rbInsideWall2->SetIsStatic(true);
		rbInsideWall2->SetColliderScale(insideWall2->GetWorldScale());
		rbInsideWall2->SetGravity(Vec3(0, 0, 9.81f));

		GameObject* insideWall12{ GameObject::CreateGameObject(room5, Transform({-1.5f, 2.5f, 5.1f}, {0, 0, 0}, {7, 10, 0.2f}), "room5 inside 1 2") };
		insideWall12->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallBack.png"));
		// Wall Rigidbody
		RigidBody* rbInsideWall12{ new RigidBody() };
		insideWall12->AddComponent(rbInsideWall12);
		rbInsideWall12->SetIsStatic(true);
		rbInsideWall12->SetColliderScale(insideWall12->GetWorldScale());
		rbInsideWall12->SetGravity(Vec3(0, 0, -9.81f));

		GameObject* insideWall22{ GameObject::CreateGameObject(room5, Transform({3.5f, 0.5f, 5.1f}, {0, 0, 0}, {3, 6, 0.2f}), "room5 inside 2 2") };
		insideWall22->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallBack.png"));
		// Wall Rigidbody
		RigidBody* rbInsideWall22{ new RigidBody() };
		insideWall22->AddComponent(rbInsideWall22);
		rbInsideWall22->SetIsStatic(true);
		rbInsideWall22->SetColliderScale(insideWall22->GetWorldScale());
		rbInsideWall22->SetGravity(Vec3(0, 0, -9.81f));


		GameObject* insideWall3{ GameObject::CreateGameObject(room5, Transform({2.5f, 2.5f, 0}, {0, 0, 0}, {5, 10, 0.2f}), "room5 inside 3") };
		insideWall3->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallBack.png"));
		// Wall Rigidbody
		RigidBody* rbInsideWall3{ new RigidBody() };
		insideWall3->AddComponent(rbInsideWall3);
		rbInsideWall3->SetIsStatic(true);
		rbInsideWall3->SetColliderScale(insideWall3->GetWorldScale());
		rbInsideWall3->SetGravity(Vec3(0, 0, -9.81f));

		GameObject* insideWall4{ GameObject::CreateGameObject(room5, Transform({0, 0, -2.5f}, {0, 0, 0}, {0.2f, 5, 5}), "room5 inside 4") };
		insideWall4->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallRight.png"));
		// Wall Rigidbody
		RigidBody* rbInsideWall4{ new RigidBody() };
		insideWall4->AddComponent(rbInsideWall4);
		rbInsideWall4->SetIsStatic(true);
		rbInsideWall4->SetColliderScale(insideWall4->GetWorldScale());
		rbInsideWall4->SetGravity(Vec3(9.81f, 0, 0));

		GameObject* insideWall5{ GameObject::CreateGameObject(room5, Transform({2.5f, 2.5f, -2.5f}, {0, 0, 0}, {5, 0.2f, 5}), "room5 inside 5") };
		insideWall5->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallDown.png"));
		// Wall Rigidbody
		RigidBody* rbInsideWall5{ new RigidBody() };
		insideWall5->AddComponent(rbInsideWall5);
		rbInsideWall5->SetIsStatic(true);
		rbInsideWall5->SetColliderScale(insideWall5->GetWorldScale());
		rbInsideWall5->SetGravity(Vec3(0, -9.81f, 0));

		GameObject* insideWall6{ GameObject::CreateGameObject(room5, Transform({0, 4.5f, 2.5f}, {0, 0, 0}, {0.2f, 6, 5.1}), "room5 inside 6") };
		insideWall6->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallRight.png"));
		// Wall Rigidbody
		RigidBody* rbInsideWall6{ new RigidBody() };
		insideWall6->AddComponent(rbInsideWall6);
		rbInsideWall6->SetIsStatic(true);
		rbInsideWall6->SetColliderScale(insideWall6->GetWorldScale());
		rbInsideWall6->SetGravity(Vec3(9.81f, 0, 0));

		GameObject* insideWall7{ GameObject::CreateGameObject(room5, Transform({2.5f, 5, -0.1f}, {0, 0, 0}, {5, 5, 0.2f}), "room5 inside 7") };
		insideWall7->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallFront.png"));
		// Wall Rigidbody
		RigidBody* rbInsideWall7{ new RigidBody() };
		insideWall7->AddComponent(rbInsideWall7);
		rbInsideWall7->SetIsStatic(true);
		rbInsideWall7->SetColliderScale(insideWall7->GetWorldScale());
		rbInsideWall7->SetGravity(Vec3(0, 0, 9.81f));

		GameObject* insideWall8{ GameObject::CreateGameObject(room5, Transform({0.1f, 4.5f, 2.5f}, {0, 0, 0}, {0.2f, 6, 5.1}), "room5 inside 8") };
		insideWall8->AddComponent(Mesh::CreateCube("Resources/Textures/LaboratoryWallLeft.png"));
		// Wall Rigidbody
		RigidBody* rbInsideWall8{ new RigidBody() };
		insideWall8->AddComponent(rbInsideWall8);
		rbInsideWall8->SetIsStatic(true);
		rbInsideWall8->SetColliderScale(insideWall8->GetWorldScale());
		rbInsideWall8->SetGravity(Vec3(-9.81f, 0, 0));

		GameObject* interactableCube1{ GameObject::CreateGameObject(Transform({25, 27.5f, 125}, {0, 0, 0}, {10, 2.5f, 10}), "room5 interactableCube 1") };
		interactableCube1->AddComponent(Mesh::CreateCube("Resources/Textures/white.png"));
		// Ground Rigidbody 
		RigidBody* rbInteractableCube1{ new RigidBody() };
		interactableCube1->AddComponent(rbInteractableCube1);
		rbInteractableCube1->SetIsStatic(true);
		rbInteractableCube1->SetColliderScale(interactableCube1->GetWorldScale());
		rbInteractableCube1->SetGravity(Vec3(0, -9.81, 0));
		// Interactable Obect 
		interactableCube1->AddComponent(new GravityGun::InteractableObject());

		GameObject* interactableCube2{ GameObject::CreateGameObject(Transform({27.5f, 25, 151}, {0, 0, 0}, {17.5f, 6, 20}), "room5 interactableCube 2") };
		interactableCube2->AddComponent(Mesh::CreateCube("Resources/Textures/white.png"));
		// Ground Rigidbody 
		RigidBody* rbInteractableCube2{ new RigidBody() };
		interactableCube2->AddComponent(rbInteractableCube2);
		rbInteractableCube2->SetIsStatic(true);
		rbInteractableCube2->SetColliderScale(interactableCube2->GetWorldScale());
		rbInteractableCube2->SetGravity(Vec3(0, -9.81, 0));
		// Interactable Obect 
		interactableCube2->AddComponent(new GravityGun::InteractableObject());

		GameObject* interactableCube3{ GameObject::CreateGameObject(Transform({25, 40, 160}, {0, 0, 0}, {20, 17.5f, 3.5f}), "room5 interactableCube 3") };
		interactableCube3->AddComponent(Mesh::CreateCube("Resources/Textures/white.png"));
		// Ground Rigidbody 
		RigidBody* rbInteractableCube3{ new RigidBody() };
		interactableCube3->AddComponent(rbInteractableCube3);
		rbInteractableCube3->SetIsStatic(true);
		rbInteractableCube3->SetColliderScale(interactableCube3->GetWorldScale());
		rbInteractableCube3->SetGravity(Vec3(0, -9.81, 0));
		// Interactable Obect 
		interactableCube3->AddComponent(new GravityGun::InteractableObject());


		// Door
		GameObject* door{ GameObject::CreateGameObject(room5, Transform(Vec3(-5, 2.5f, 7.5f), Quaternion(1, 0, 0, 0), Vec3(0.2, 2, 2)), "room 5 Door") };
		// DoorLeaf
		GameObject* doorLeaf{ GameObject::CreateGameObject(door, Transform(Vec3(0, 0, 0), Quaternion(1, 0, 0, 0), Vec3(1, 1, 1)), "DoorLeaf") };
		doorLeaf->AddComponent(Mesh::CreateCube("Resources/Textures/white.png"));
		RigidBody* doorLeafRB{ new RigidBody() };
		doorLeaf->AddComponent(doorLeafRB);
		doorLeafRB->SetColliderScale(doorLeaf->GetWorldScale());
		doorLeafRB->SetGravity({ 0, -9.81f, 0 });
		doorLeafRB->SetIsStatic(true);
		doorLeafRB->SetFreezePosition({ 1, 1, 1 });
		doorLeafRB->SetFreezeRotation({ 1, 1, 1 });
		// Sound 
		door->AddComponent(new Sound("Resources/Sounds/DoorOpen.mp3", "FX", false, G_SOUND_3D | G_SOUND_CREATESAMPLE | G_SOUND_3D_LINEARROLLOFF));
		door->AddComponent(new Sound("Resources/Sounds/DoorClose.mp3", "FX", false, G_SOUND_3D | G_SOUND_CREATESAMPLE | G_SOUND_3D_LINEARROLLOFF));
		// Door script 
		door->AddComponent(new GravityGun::Door());


		GameObject* winTrigger{ GameObject::CreateGameObject(room5, Transform(Vec3(-6, 2.5f, 7.5f), Quaternion(1, 0, 0, 0), Vec3(1, 2, 2)), "room 5 wintrigger") };
		RigidBody* rbWinTrigger{ new RigidBody() };
		winTrigger->AddComponent(rbWinTrigger);
		rbWinTrigger->SetIsStatic(true);
		winTrigger->AddComponent(new GravityGun::WinTrigger("Menu"));
	}
}