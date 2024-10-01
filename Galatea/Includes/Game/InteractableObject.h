#pragma once

#include <ComponentSystem/Component.h>
#include <Physic/RigidBody.h>
#include <Core/Render/Material.h>
#include <Maths/Vec3.h>

namespace GravityGun
{
	class InteractableObject : public Galatea::Component
	{
	private:
		#pragma region Variables

		Galatea::RigidBody* rigidBody;
		Galatea::Material*	material;

		Galatea::Vector3	positiveGravityColors[3];
		Galatea::Vector3	negativeGravityColors[3];
		Galatea::Vector3	colorSelector;

		#pragma endregion

		#pragma region Methods

		void	SetColor(const Galatea::Vector3& _gravity)	noexcept;

		#pragma endregion

	public:
		#pragma region Constructors/Destructor

		InteractableObject()	noexcept;
		~InteractableObject()	noexcept;

		#pragma endregion

		#pragma region Methods

		void	Init()	noexcept override;
		void	SetGravity(const Galatea::Vector3& _gravity)	noexcept;

		template<class Archive>
		void serialize(Archive& _ar)
		{}

		#pragma endregion

		#pragma region Operators
		#pragma endregion
	};
}
CEREAL_REGISTER_TYPE(GravityGun::InteractableObject);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Galatea::Component, GravityGun::InteractableObject)