#pragma once

#include "DLL.h"
#include "ComponentSystem/Component.h"
#include "Cereal/types/polymorphic.hpp"
#include "Maths/Vec3.h"
#include "rttr/registration_friend.h"

namespace Galatea
{
	class Light : public Component
	{
	public:
		enum ELightType : unsigned int
		{
			POINT = 0,
			SPOT = 1 << 0,
			DIRECTIONAL = 1 << 1,
		};
	private:
		bool			hasBeenModified;

		float			power;
		float			shininess;
		float			cutOff;
		float			outerCutOff;

		Vec3			diffuse;
		Vec3			specular;
		Vec3			color;

		Vec3			attenuation;

		Vec3			direction;

		ELightType		type;
		Light()																			noexcept;

		void	SendAllProperties(const class Shader* _shader, unsigned int _position)	noexcept;
	public:
		GALATEA_API Light(ELightType _type)												noexcept;

		#if defined(GALATEADLL_EXPORTS) || defined(_DEBUGEXE)
		/* Function used by the cereal librarie to serialize and deserialize */
		template<class Archive>
		void serialize(Archive& _ar)
		{
			_ar(power, shininess, cutOff, outerCutOff, diffuse, specular, color, attenuation, direction, type);
		}
		#endif

		void	SendLight(const Shader* _shader, unsigned int _position)				noexcept;

		void	SetPower(float _newPower)												noexcept { hasBeenModified = true; power = _newPower; }
		void	SetShininess(float _newShininess)										noexcept { hasBeenModified = true; shininess = _newShininess; }
		/*Takes value on Degrees*/
		void	SetCutOff(float _newCutOff)												noexcept { hasBeenModified = true; cutOff = cosf(_newCutOff * G_DEG2RAD); }
		/*Takes value on Degrees*/
		void	SetOuterCutOff(float _newOuterCutOff)									noexcept { hasBeenModified = true; outerCutOff = cosf(_newOuterCutOff * G_DEG2RAD); }
		void	SetDiffuse(const Vec3& _newDif)											noexcept { hasBeenModified = true; diffuse = _newDif; }
		void	SetSpecular(const Vec3& _newSpe)										noexcept { hasBeenModified = true; specular = _newSpe; }
		void	SetDirection(const Vec3& _newDir)										noexcept { hasBeenModified = true; direction = _newDir; }
		void	SetColor(const Vec3& _newColor)											noexcept { hasBeenModified = true; color = _newColor; }
		void	SetAttenuation(const Vec3& _newAttenuation)								noexcept { hasBeenModified = true; attenuation = _newAttenuation; }

		float		GetPower()													const	noexcept { return power; }
		float		GetShininess()												const	noexcept { return shininess; }
		float		GetCutOff()													const	noexcept { return cutOff * G_RAD2DEG; }
		float		GetOuterCutOff()											const	noexcept { return outerCutOff * G_RAD2DEG; }
		const Vec3&	GetDiffuse()												const	noexcept { return diffuse; }
		const Vec3&	GetSpecular()												const	noexcept { return specular; }
		const Vec3& GetDirection()												const	noexcept { return direction; }
		const Vec3& GetColor()													const	noexcept { return color; }
		const Vec3&	GetAttenuation()											const	noexcept { return attenuation; }

		RTTR_ENABLE(Component)
		RTTR_REGISTRATION_FRIEND
		friend class cereal::access;
	};
}
CEREAL_REGISTER_TYPE(Galatea::Light);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Galatea::Component, Galatea::Light)