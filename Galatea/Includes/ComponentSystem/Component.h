#pragma once

#include "DLL.h"

#include "Cereal/types/polymorphic.hpp"
#include "ComponentSystem/GameObject.h"
#include "rttr/variant_sequential_view.h"
#include "rttr/type_list.h"
#include "rttr/type.h"
#include "rttr/registration_friend.h"
#include "rttr/registration.h"

namespace Galatea
{
	/* 
	Inherite from this class to be able to store your class in a GameObject 
	Plus if you want it to be serialize you need to add this two line at the end of your file :
	
	CEREAL_REGISTER_TYPE(YourClass);
	CEREAL_REGISTER_POLYMORPHIC_RELATION(Galatea::Component, YourClass)
	*/
	class  Component
	{
		friend cereal::access;
		friend GameObject;

	protected:
		Component() noexcept;

	public :
		GameObject*		owner;
		bool			isActive;

		GALATEA_API	Component(GameObject* _owner)			noexcept;
		GALATEA_API virtual ~Component()					noexcept {};

		GALATEA_API GameObject* GetOwner() const noexcept { return owner; }
		GALATEA_API GameObject* GetOwner() noexcept { return owner; }

		GALATEA_API virtual void	OnAwake()	noexcept {};
		GALATEA_API virtual void	Init()		noexcept {};

		#if defined(GALATEADLL_EXPORTS) || defined(_DEBUGEXE)

		template<class Archive>
		void serialize(Archive& _ar) {};

		#endif

		Component& operator=(const Component& _c)	noexcept;
		Component& operator=(Component& _c)			noexcept;

		RTTR_ENABLE()
	};
}
