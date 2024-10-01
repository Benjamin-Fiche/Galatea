#pragma once

#include "rttr/registration.h"
#include "Physic/Transform.h" //also include Quaternion, Mat4, Vec4 ,Vec3, Vec2
#include "Core/Render/Mesh.h"
#include "Core/Camera/Camera.h"
#include "Core/Render/Texture.h"
#include "Core/Render/Material.h"
#include "Core/Render/Light.h"
#include "Physic/RigidBody.h"
#include "Core/Camera/CameraFreeFlyMovement.h"
#include "Core/Render/Text2D.h"
#include "Core/Render/Quad2D.h"
#include "Sound/Sound.h"

using namespace rttr;
RTTR_REGISTRATION
{
	/* Math class registration */
	registration::class_<Galatea::Vec2>("Vec2")
		.property("x",	&Galatea::Vec2::x)
		.property("y",	&Galatea::Vec2::y);

	registration::class_<Galatea::Vec3>("Vec3")
		.property("x",	&Galatea::Vec3::x)
		.property("y",	&Galatea::Vec3::y)
		.property("z",	&Galatea::Vec3::z);

	registration::class_<Galatea::Vec4>("Vec4")
		.property("x",	&Galatea::Vec4::x)
		.property("y",	&Galatea::Vec4::y)
		.property("z",	&Galatea::Vec4::z)
		.property("w",	&Galatea::Vec4::w);

	registration::class_<Galatea::Quaternion>("Quaternion")
		.property("w",	&Galatea::Quaternion::w)
		.property("x",	&Galatea::Quaternion::x)
		.property("y",	&Galatea::Quaternion::y)
		.property("z",	&Galatea::Quaternion::z);

	registration::class_<Galatea::Mat4>("Mat4") 
		.property("data",	&Galatea::Mat4::data);

	/* Component class Registration */

	registration::class_<Galatea::Transform>("Transform")
		.property("position",	&Galatea::Transform::position)
		.property("rotation",	&Galatea::Transform::rotation)
		.property("scale",		&Galatea::Transform::scale);
			
	registration::class_<Galatea::Mesh>("Mesh")
		.property("isActive",	&Galatea::Mesh::isActive)
		.property("name",		&Galatea::Mesh::name)
		.property("materials",	&Galatea::Mesh::materials);

	registration::class_<Galatea::Material>("Material")
		.property("shininess",				&Galatea::Material::shininess)
		.property("opacity",				&Galatea::Material::opacity)
		.property("transparencyFactor",		&Galatea::Material::transparencyFactor)
		.property("reflectivity",			&Galatea::Material::reflectivity)
		.property("bumpScaling",			&Galatea::Material::bumpScaling)
		.property("ambientColor",			&Galatea::Material::ambientColor)
		.property("specularColor",			&Galatea::Material::specularColor)
		.property("diffuseColor",			&Galatea::Material::diffuseColor)
		.property("emissiveColor",			&Galatea::Material::emissiveColor)
		.property("reflectiveColor",		&Galatea::Material::reflectiveColor)
		.property("transparentColor",		&Galatea::Material::transparentColor)
		.property("diffuseTexture",			&Galatea::Material::diffuseTexture)
		.property("ambientTexture",			&Galatea::Material::ambientTexture)
		.property("specularTexture",		&Galatea::Material::specularTexture)
		.property("emissiveTexture",		&Galatea::Material::emissiveTexture)
		.property("bumpTexture",			&Galatea::Material::bumpTexture)
		.property("materialName",			&Galatea::Material::materialName)
		.property("directory",				&Galatea::Material::directory)
		.property("flag",					&Galatea::Material::flag);

	registration::class_<Galatea::Camera>("Camera")
		.property("isActive",	&Galatea::Camera::isActive)
		.property("front",		&Galatea::Camera::front)
		.property("right",		&Galatea::Camera::right)
		.property("up",			&Galatea::Camera::up);


	registration::class_<Galatea::CameraFreeFlyMovement>("CameraFreeFlyMovement")
		.property("isActive",	&Galatea::CameraFreeFlyMovement::isActive)
		.property("speed",		&Galatea::CameraFreeFlyMovement::speed)
		.property("sensivity",	&Galatea::CameraFreeFlyMovement::sensivity);

	registration::class_<Galatea::Texture>("Texture")
		.property("textureID",	&Galatea::Texture::textureID)
		.property("name",		&Galatea::Texture::name);

	registration::class_<Galatea::Light>("Light")
		.property("isActive",		&Galatea::Light::isActive)
		.property("power",			&Galatea::Light::GetPower, &				Galatea::Light::SetPower)
		.property("shininess",		&Galatea::Light::GetShininess,				&Galatea::Light::SetShininess)
		.property("cutOff",			&Galatea::Light::GetCutOff,					&Galatea::Light::SetCutOff)
		.property("outerCutOff",	&Galatea::Light::GetOuterCutOff,			&Galatea::Light::SetOuterCutOff)
		.property("diffuse",		&Galatea::Light::GetDiffuse,				&Galatea::Light::SetDiffuse)
		.property("specular",		&Galatea::Light::GetSpecular,				&Galatea::Light::SetSpecular)
		.property("color",			&Galatea::Light::GetColor,					&Galatea::Light::SetColor)
		.property("attenuation",	&Galatea::Light::GetAttenuation,			&Galatea::Light::SetAttenuation)
		.property("direction",		&Galatea::Light::GetDirection,				&Galatea::Light::SetDirection);

	registration::class_<Galatea::RigidBody>("RigidBody")
		.property("colliderScale",		&Galatea::RigidBody::GetColliderScale,		&Galatea::RigidBody::SetColliderScale)
		.property("gravity",			&Galatea::RigidBody::GetGravity,			&Galatea::RigidBody::SetGravity)
		.property("isStatic",			&Galatea::RigidBody::GetIsStatic,			&Galatea::RigidBody::SetIsStatic)
		.property("isTrigger",			&Galatea::RigidBody::GetIsTrigger,			&Galatea::RigidBody::SetIsTrigger)
		.property("geometry",			&Galatea::RigidBody::GetGeometry,			&Galatea::RigidBody::SetGeometry)
		.property("freezePosition",		&Galatea::RigidBody::GetFreezePosition,		&Galatea::RigidBody::SetFreezePosition)
		.property("freezeRotation",		&Galatea::RigidBody::GetFreezeRotation,		&Galatea::RigidBody::SetFreezeRotation)
		.property("staticFriction",		&Galatea::RigidBody::GetStaticFriction,		&Galatea::RigidBody::SetStaticFriction)
		.property("dynamicFriction",	&Galatea::RigidBody::GetDynamicFriction,	&Galatea::RigidBody::SetDynamicFriction)
		.property("restitution",		&Galatea::RigidBody::GetRestitution,		&Galatea::RigidBody::SetRestitution)
		.property("mass",				&Galatea::RigidBody::GetMass,				&Galatea::RigidBody::SetMass);

	registration::class_<Galatea::Text2D>("Text2D")
		.property("color", &Galatea::Text2D::color)
		.property("text", &Galatea::Text2D::text)
		.property("fontName", &Galatea::Text2D::fontName);

		registration::class_<Galatea::Quad2D>("Quad2D")
		.property("textureName", &Galatea::Quad2D::textureName);

	registration::class_<Galatea::Sound>("Sound")
		.property("source", &Galatea::Sound::source)
		.property("channelGroup", &Galatea::Sound::channelGroup)
		.property("playOnAwake", &Galatea::Sound::playOnAwake);
}