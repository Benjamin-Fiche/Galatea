#pragma once

#include "DLL.h"

#include "Debug/Log.h"
#include "Physic/Transform.h"

#include "Cereal/types/vector.hpp"
#include "Cereal/types/memory.hpp"
#include "Cereal/types/string.hpp"

namespace Galatea
{
	class Component;
	class GameObject final
	{
	private:
		#pragma region Variables

		std::vector<std::shared_ptr<Component>>				cList;
		std::vector<std::shared_ptr<GameObject>>			children;
		unsigned int										flag;

		#pragma endregion
		
		void	FindUnusedName(const std::string& _name, unsigned int _iteration)												noexcept;
	public:
		#pragma region Variables
		
		bool			isActive;
		std::string		name;
		Transform		transform;
		GameObject*		parent;

		#pragma endregion

		#pragma region Constructors/Destructor

		#if defined(GALATEADLL_EXPORTS) || defined(_DEBUGEXE)
		GameObject(unsigned int _flag = 0)																						noexcept;
		GameObject(std::string _name, unsigned int _flag = 0)																	noexcept;
		GameObject(const Transform& _transform, std::string _name = "GameObject", unsigned int _flag = 0)						noexcept;
		GameObject(GameObject* _parent, const Transform& _transform, std::string _name = "GameObject", unsigned int _flag = 0)	noexcept;
		GameObject(GameObject* _parent, std::string _name = "GameObject", unsigned int _flag = 0)								noexcept;
		~GameObject()																											noexcept;
		#endif
		
		#pragma endregion

		#pragma region Properties

		GALATEA_API const std::string&									GetName()					noexcept;

		/* Get all the componenent of this GameObject */
		GALATEA_API std::vector<std::shared_ptr<Component>>&			GetComponentList()			noexcept;

		/*Get*/
		GALATEA_API GameObject*											GetChild(const char* _name)	noexcept;
		GALATEA_API std::vector<std::shared_ptr<GameObject>>&			GetChildren()				noexcept;
		GALATEA_API Mat4												GetWorldTRS()		const	noexcept;
		GALATEA_API Vec3												GetWorldPosition()	const	noexcept;
		GALATEA_API Quat												GetWorldRotation()	const	noexcept;
		GALATEA_API Vec3												GetWorldScale()		const	noexcept;
		GALATEA_API unsigned int										GetFlag()			const	noexcept	{ return flag; };

		#pragma endregion

		#pragma region Methods

		/* Take an allocated Component as argument */
		GALATEA_API void	AddComponent(Component* _c)												noexcept;
		GALATEA_API void	RemoveComponent(Component* _c)											noexcept;

		GALATEA_API void	AddChild(GameObject* _gO)												noexcept;

		/* Get the first Component found that correspond the type */
		template<class T>
		T* GetComponent()																	const	noexcept
		{
			for (int i = 0; i < cList.size(); ++i)
				if (T* comp = dynamic_cast<T*>(cList[i].get()))
					return comp;

			return nullptr;
		}

		/* Get the list of Component that correspond the type */
		template<class T>
		std::vector<T*>		GetComponents()													const	noexcept
		{
			std::vector<T*> comps;

			for (int i = 0; i < cList.size(); ++i)
				if (T* comp = dynamic_cast<T*>(cList[i].get()))
					comps.push_back(comp);

			return comps;
		}

		GALATEA_API static GameObject* CreateGameObject2D(GameObject* _parent, const Transform& _transform, const std::string& _name, unsigned int _flag = 0u)	noexcept;
		GALATEA_API static GameObject* CreateGameObject2D(const Transform& _transform, const std::string& _name, unsigned int _flag = 0u)						noexcept;
		GALATEA_API static GameObject* CreateGameObject2D(GameObject* _parent, const std::string& _name, unsigned int _flag = 0u)								noexcept;
		GALATEA_API static GameObject* CreateGameObject2D(const std::string& _name, unsigned int _flag = 0u)													noexcept;

		GALATEA_API static GameObject* CreateGameObject(GameObject* _parent, const Transform& _transform, const std::string& _name, unsigned int _flag = 0u)	noexcept;
		GALATEA_API static GameObject* CreateGameObject(const Transform& _transform, const std::string& _name, unsigned int _flag = 0u)							noexcept;
		GALATEA_API static GameObject* CreateGameObject(GameObject* _parent, const std::string& _name, unsigned int _flag = 0u)									noexcept;
		GALATEA_API static GameObject* CreateGameObject(const std::string& _name, unsigned int _flag = 0u)														noexcept;
		
		#if defined(GALATEADLL_EXPORTS) || defined(_DEBUGEXE)

		template<class Archive>
		void save(Archive& _ar) const
		{
			_ar(isActive, name, transform, cList, children);
		}
		
		template<class Archive>
		void load(Archive& _ar)
		{
			_ar(isActive, name, transform, cList, children);

			for (int i = 0; i < cList.size(); ++i)
				cList[i].get()->owner = this;

			for (int i = 0; i < children.size(); ++i)
				children[i]->parent = this;
		}

		#endif
	};
}
