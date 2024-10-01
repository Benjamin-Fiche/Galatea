#pragma once

#include <vector>

#include "UpdatableComponent.h"

namespace Galatea
{
	class ComponentsManager
	{
	private:
		unsigned int						usedCameraIndex = 0;

		std::vector<class Camera*>			camList;
		std::vector<class Light*>			lightList;
		std::vector<class RigidBody*>		rbList;

		std::vector<UpdatableComponent*>	ucList;

		class Physics*						physics;

	public:
		ComponentsManager()							noexcept;
		~ComponentsManager()						noexcept = default;

		void					Update()																		noexcept;
		void					FixedUpdate()																	noexcept;
		void					LateUpdate()																	noexcept;

		void					AddComponent(Component* _c)														noexcept;
		void					RemoveComponent(Component* _c)													noexcept;
		void					SendLights(const class Shader* _shader, const struct Vec3& _cameraPos)	const	noexcept;
		std::vector<RigidBody*>	GetrbList() { return rbList; }
		

		friend GameObject;
		friend class Scene;
	};
}
