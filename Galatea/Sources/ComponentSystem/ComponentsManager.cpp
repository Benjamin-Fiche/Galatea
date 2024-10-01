#include "ComponentSystem/ComponentsManager.h"
#include "ComponentSystem/GameObject.h"
#include "Core/Camera/Camera.h"
#include "Core/Render/Light.h"
#include "Core/SceneManager.h"
#include "Core/Camera/Camera.h"
#include "Core/Render/Shader.h"
#include "Physic/Physics.h"
#include "Physic/RigidBody.h"

using namespace Galatea;

ComponentsManager::ComponentsManager()		noexcept :
	physics{ &SceneManager::GetInstance().GetPhysics() }
{}

void ComponentsManager::Update() noexcept
{
	for (int i = 0; i < ucList.size(); ++i)
	{
		if (ucList[i]->owner->isActive && ucList[i]->isActive)
			ucList[i]->Update();
	}
}

void ComponentsManager::FixedUpdate() noexcept
{
	for (int i = 0; i < ucList.size(); ++i)
	{
		if (ucList[i]->owner->isActive && ucList[i]->isActive)
			ucList[i]->FixedUpdate();
	}

	physics->FixedUpdate();
}

void ComponentsManager::LateUpdate() noexcept
{
	for (int i = 0; i < ucList.size(); ++i)
	{
		if (ucList[i]->owner->isActive && ucList[i]->isActive)
			ucList[i]->LateUpdate();
	}
}

void ComponentsManager::AddComponent(Component* _c) noexcept
{
	_c->Init();
	if (UpdatableComponent* _uc = dynamic_cast<UpdatableComponent*>(_c))
	{
		if (Camera* cam = dynamic_cast<Camera*>(_uc))
		{
			if (camList.size() != usedCameraIndex)
				cam->isActive = false;
			camList.push_back(cam);
		}
		else if (RigidBody* rigidBody = dynamic_cast<RigidBody*>(_uc))
		{
			rigidBody->Init(*physics);
			rbList.push_back(rigidBody);
		}
		
		ucList.push_back(_uc);
	}
	else if (Light* light = dynamic_cast<Light*>(_c))
	{
		lightList.push_back(light);
	}
}

void ComponentsManager::RemoveComponent(Component* _c) noexcept
{
	if (UpdatableComponent* _uc = dynamic_cast<UpdatableComponent*>(_c))
	{
		if (Camera* cam = dynamic_cast<Camera*>(_uc))
		{
			for (auto it{ camList.begin() }; it != camList.end(); ++it)
				if ((*it) == cam)
				{
					camList.erase(it);
					break;
				}
		}
		else if (RigidBody* rigidBody = dynamic_cast<RigidBody*>(_uc))
		{
			for (auto it{ rbList.begin() }; it != rbList.end(); ++it)
				if ((*it) == rigidBody)
				{
					rbList.erase(it);
					break;
				}
		}

		for (auto it{ ucList.begin() }; it != ucList.end(); ++it)
			if ((*it) == _uc)
			{
				ucList.erase(it);
				break;
			}
	}
	else if (Light* light = dynamic_cast<Light*>(_c))
	{
		for (auto it{ lightList.begin() }; it != lightList.end(); ++it)
			if ((*it) == light)
			{
				lightList.erase(it);
				break;
			}
	}
}

void ComponentsManager::SendLights(const Shader* _shader, const Vec3& _cameraPos) const noexcept
{
	_shader->SendInt("lightNumber", lightList.size());
	_shader->SendVec3("viewPos", _cameraPos);

	for (unsigned int index = 0; index < lightList.size(); ++index)
		lightList[index]->SendLight(_shader, index);

}
