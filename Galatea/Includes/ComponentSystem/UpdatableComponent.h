#pragma once

#include "DLL.h"

#include "Component.h"

namespace Galatea
{
	/* 
	UpdatableComponent let you override FixedUpdate, Update and LateUpdate function for them to be called when the game is running
	Component that can update itself throught FixedUpdate, Update and LateUpdate Functions.
	Plus if you want it to be serialize you need to add this two line at the end of your file :
	
	CEREAL_REGISTER_TYPE(YourClass);
	CEREAL_REGISTER_POLYMORPHIC_RELATION(Galatea::UpdatableComponent, YourClass) 
	*/
	GALATEA_API class UpdatableComponent : public Component
	{
		friend cereal::access;

	protected:
		UpdatableComponent() noexcept : Component{} {};

	public:
		UpdatableComponent(GameObject* _owner) : Component{ _owner } {};
		virtual ~UpdatableComponent() = default;

		virtual void Init()			noexcept {};

		virtual void FixedUpdate()	noexcept {};
		virtual void Update()		noexcept {};
		virtual void LateUpdate()	noexcept {};

		#if defined(GALATEADLL_EXPORTS) || defined(_DEBUGEXE)

		template<class Archive>
		void serialize(Archive& _ar)
		{
		}

		#endif
		RTTR_ENABLE(Component)
	};
}
CEREAL_REGISTER_TYPE(Galatea::UpdatableComponent);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Galatea::Component, Galatea::UpdatableComponent)