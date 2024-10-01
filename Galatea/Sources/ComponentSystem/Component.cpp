#include "ComponentSystem/Component.h"
#include "ComponentSystem/GameObject.h"

using namespace Galatea;

Component::Component() noexcept
	: owner{ nullptr }, isActive{ true }
{}

Component::Component(GameObject* _owner) noexcept
	: owner{ _owner }, isActive{ true }
{}

Component& Component::operator=(const Component& _c)	noexcept
{
	owner		= _c.owner;
	isActive	= _c.isActive;
	return *this;
}

Component& Component::operator=(Component& _c)			noexcept
{
	owner		= std::move(_c.owner);
	isActive	= std::move(_c.isActive);
	return *this;
}