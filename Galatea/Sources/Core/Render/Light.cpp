#include "Core/Render/Light.h"
#include "Core/Render/Shader.h"

using namespace Galatea;

Light::Light() noexcept :
	hasBeenModified{ true },
	power{ 1.0f },
	cutOff{ cosf(12.5f * G_DEG2RAD) },
	outerCutOff{ cosf(17.5f * G_DEG2RAD) },
	diffuse{ 0.7f, 0.7f, 0.7f },
	specular{ 0.1f, 0.1f, 0.1f },
	color{ 1.0f, 1.0f, 1.0f },
	direction{ 1.0f, 1.0f, 1.0f },
	attenuation{ 1.0f, 0.09f, 0.032f },
	type{ ELightType::POINT }
{

}

Light::Light(ELightType _type) noexcept :
	hasBeenModified{ true },
	power{ 1.0f },
	cutOff{ cosf(12.5f * G_DEG2RAD) },
	outerCutOff{ cosf(17.5f * G_DEG2RAD) },
	diffuse{ 0.7f, 0.7f, 0.7f },
	specular{ 0.1f, 0.1f, 0.1f },
	color{ 1.0f, 1.0f, 1.0f },
	direction{ 1.0f, 1.0f, 1.0f },
	attenuation{ 1.0f, 0.09f, 0.032f },
	type{ _type }
{

}

void Light::SendAllProperties(const Shader* _shader, unsigned int _position)	noexcept
{
	std::string pos = std::to_string(_position);
	
	_shader->SendInt	(("lights[" + pos + "].type"		).c_str(), type);
	_shader->SendFloat	(("lights[" + pos + "].power"		).c_str(), power);
	_shader->SendFloat	(("lights[" + pos + "].shininess"	).c_str(), shininess);
	_shader->SendFloat	(("lights[" + pos + "].cutOff"		).c_str(), cutOff);
	_shader->SendFloat	(("lights[" + pos + "].outerCutOff"	).c_str(), outerCutOff);
	_shader->SendVec3	(("lights[" + pos + "].diffuse"		).c_str(), diffuse);
	_shader->SendVec3	(("lights[" + pos + "].specular"	).c_str(), specular);
	_shader->SendVec3	(("lights[" + pos + "].attenuation"	).c_str(), attenuation);
	_shader->SendVec3	(("lights[" + pos + "].color"		).c_str(), color);

	hasBeenModified = false;
}

void Light::SendLight(const Shader* _shader, unsigned int _position) noexcept
{
	std::string pos = std::to_string(_position);
	if (isActive)
	{
		if (hasBeenModified)
			SendAllProperties(_shader, _position);
		_shader->SendVec3(("lights[" + pos + "].position").c_str(), owner->transform.globalMatrix * Vec3{ 0.0f, 0.0f, 0.0f });
		_shader->SendVec3(("lights[" + pos + "].direction").c_str(), owner->transform.rotation * direction);
	}
	_shader->SendBool(("lights[" + pos + "].isActive").c_str(), isActive);		//TODO : Add on Enable/Disable function for component/gameobject ?
}