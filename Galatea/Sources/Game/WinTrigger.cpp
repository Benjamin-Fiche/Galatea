#include "Game/WinTrigger.h"

#include "Physic/Physics.h"
#include "Physic/RigidBody.h"
#include "Game/Player.h"
#include "Core/Time.h"
#include "Core/SceneManager.h"
#include "Core/Scene.h"
#include "Cereal/types/polymorphic.hpp"

using namespace GravityGun;

WinTrigger::WinTrigger(std::string _menuSceneName)	noexcept :
	menuSceneName { _menuSceneName }
{}


void WinTrigger::Init() noexcept
{
	rigidBody = owner->GetComponent<RigidBody>();
	rigidBody->SetIsTrigger(true);

	if  (rigidBody != nullptr)
		rigidBody->onBeginOverlapEvent.Suscribe(&WinTrigger::OnBegin, *this);
}

void WinTrigger::OnBegin(RigidBody* _other) noexcept
{
	if (_other->owner->GetName() == "Player")
	{
		_other->owner->transform.position = { 0, 10, 0 };
		Scene::ChangeScene(menuSceneName.c_str());
	}
}
