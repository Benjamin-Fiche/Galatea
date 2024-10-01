#include "ComponentSystem/GameObject.h"
#include "Core/Scene.h"
#include "Debug/Log.h"

using namespace Galatea;

GameObject::GameObject(unsigned int _flag) noexcept :
	name{ "GameObject" },
	flag{ _flag },
	isActive{ true }
{
}

GameObject::GameObject(std::string _name, unsigned int _flag) noexcept:
	name{ _name },
	flag{ _flag },
	isActive{ true }
{
}

GameObject::GameObject(const Transform& _transform, std::string _name, unsigned int _flag) noexcept :
	name{ _name },
	flag{ _flag },
	isActive{ true },
	transform{ _transform }
{
}

GameObject::GameObject(GameObject* _parent, const Transform& _transform, std::string _name, unsigned int _flag) noexcept :
	name{ _name },
	parent { _parent },
	flag { _flag },
	isActive{ true },
	transform{ _transform }
{
}

GameObject::GameObject(GameObject* _parent, std::string _name, unsigned int _flag) noexcept :
	name{ _name },
	parent{ _parent },
	flag{ _flag },
	isActive{ true }
{
}

GameObject::~GameObject() noexcept
{
	parent = nullptr;
	for (auto it : cList)
		Scene::GetCurrentScene()->GetComponentsManager()->RemoveComponent(it.get());
	cList.clear();
	children.clear();
}

void GameObject::AddComponent(Component* _c) noexcept
{
	_c->owner = this;
	std::shared_ptr<Component> newC(_c);
	cList.push_back(std::move(newC));
	if (Scene::GetCurrentScene()->IsSceneInit())
		Scene::GetCurrentScene()->GetComponentsManager()->AddComponent(_c);
}

void GameObject::RemoveComponent(Component* _c) noexcept
{
	Scene::GetCurrentScene()->GetComponentsManager()->RemoveComponent(_c);

	for (auto it{ cList.begin() }; it != cList.end(); ++it)
	{
		if ((*it).get() == _c)
		{
			cList.erase(it);
			break;
		}
	}
}

void GameObject::AddChild(GameObject* _gO) noexcept
{
	std::shared_ptr<GameObject> newgO(_gO);
	for (auto it = children.begin(); it != children.end(); ++it)
		if (*it == newgO)
			return;

	if (_gO->parent != nullptr)
	{
		for (auto it = _gO->parent->children.begin(); it != _gO->parent->children.end(); ++it)
		{
			if (*it == newgO)
			{
				_gO->parent->children.erase(it);
				break;
			}
		}
	}
	children.push_back(std::move(newgO));
	_gO->parent = this;
}

const std::string& GameObject::GetName() noexcept
{
	return name;
}

GameObject* GameObject::GetChild(const char* _name) noexcept
{
	for (int i = 0; i < children.size(); ++i)
		if (children[i].get()->GetName() == _name)
			return children[i].get();

	return nullptr;
}

std::vector<std::shared_ptr<Component>>& GameObject::GetComponentList() noexcept
{
	return cList;
}

std::vector<std::shared_ptr<GameObject>>& GameObject::GetChildren() noexcept
{
	return children;
}

Mat4 GameObject::GetWorldTRS() const noexcept
{
	if (parent != nullptr)
		return parent->GetWorldTRS() * transform.GetMatrix();
	return transform.GetMatrix();
}

Vec3 GameObject::GetWorldPosition() const noexcept
{
	if (parent != nullptr)
		return parent->GetWorldTRS() * transform.position;
	return transform.position;
}

Quat GameObject::GetWorldRotation() const noexcept
{
	if (parent != nullptr)
		return parent->GetWorldRotation() * transform.rotation;
	return transform.rotation;
}

Vec3 GameObject::GetWorldScale() const noexcept
{
	if (parent != nullptr)
	{
		Vec3 parentScale = parent->GetWorldScale();
		return Vec3(parentScale.x * transform.scale.x,
					parentScale.y * transform.scale.y,
					parentScale.z * transform.scale.z);
	}

	return transform.scale;
}

void GameObject::FindUnusedName(const std::string& _name, unsigned int _iteration) noexcept
{
	for (auto it : parent->children)
	{
		if (_name == it->name && it.get() != this)
		{
			FindUnusedName(name + std::to_string(_iteration), ++_iteration);
			return;
		}
	}
	if (_iteration != 1)
		name += std::to_string(_iteration);
}

GameObject* GameObject::CreateGameObject2D(const Transform& _transform, const std::string& _name, unsigned int _flag) noexcept
{
	return GameObject::CreateGameObject2D(nullptr, _transform, _name, _flag);
}

GameObject* GameObject::CreateGameObject2D(GameObject* _parent, const std::string& _name, unsigned int _flag) noexcept
{
	return GameObject::CreateGameObject2D(_parent, Transform(), _name, _flag);
}

GameObject* GameObject::CreateGameObject2D(const std::string& _name, unsigned int _flag) noexcept
{
	return GameObject::CreateGameObject2D(nullptr, Transform(), _name, _flag);
}

GameObject* GameObject::CreateGameObject2D(GameObject* _parent, const Transform& _transform, const std::string& _name, unsigned int _flag) noexcept
{
	GameObject* go = new GameObject(_parent, _transform, _name, _flag);

	if (_parent == nullptr)
		Scene::GetCurrentScene()->GetWorld2D()->AddChild(go);
	else
		_parent->AddChild(go);

	if (Scene::GetCurrentScene()->IsSceneInit())
		Scene::GetCurrentScene()->gameObject2DList.push_back(go);

	go->FindUnusedName(_name, 1);

	return go;
}

GameObject* GameObject::CreateGameObject(const Transform& _transform, const std::string& _name, unsigned int _flag) noexcept
{
	return GameObject::CreateGameObject(nullptr, _transform, _name, _flag);
}

GameObject* GameObject::CreateGameObject(GameObject* _parent, const std::string& _name, unsigned int _flag) noexcept
{
	return GameObject::CreateGameObject(_parent, Transform(), _name, _flag);
}

GameObject* GameObject::CreateGameObject(const std::string& _name, unsigned int _flag) noexcept
{
	return GameObject::CreateGameObject(nullptr, Transform(), _name, _flag);
}

GameObject* GameObject::CreateGameObject(GameObject* _parent, const Transform& _transform, const std::string& _name, unsigned int _flag) noexcept
{
	GameObject* go = new GameObject(_parent, _transform, _name, _flag);

	if (_parent == nullptr)
		Scene::GetCurrentScene()->GetWorld()->AddChild(go);
	else
		_parent->AddChild(go);
	
	if (Scene::GetCurrentScene()->IsSceneInit())
		Scene::GetCurrentScene()->gameObjectList.push_back(go);

	go->FindUnusedName(_name, 1);

	return go;
}
