#include "Physic/Transform.h"
#include "rttr\registration.h"

using namespace Galatea;

#pragma region Constructors/Destructors

Transform::Transform() noexcept
	: position{ 0, 0, 0 }, rotation{ 1, 0, 0, 0 }, scale{ 1, 1, 1 }, globalMatrix{Mat4::Identity()}
{}

Transform::Transform(const Transform& _trs) noexcept
	: position{ _trs.position }, rotation{ _trs.rotation }, scale{ _trs.scale }
{}

Transform::Transform(Transform&& _trs) noexcept
	: position{ std::move(_trs.position) }, rotation{ std::move(_trs.rotation) }, scale{ std::move(_trs.scale) }
{}

Transform::Transform(const Vec3& _position, const Quat& _rotation, const Vec3& _scale) noexcept
	: position{ _position }, rotation{ _rotation }, scale{ _scale }
{}

Transform::Transform(Vec3&& _position, Quat&& _rotation, Vec3&& _scale) noexcept
	: position{ std::move(_position) }, rotation{ std::move(_rotation) }, scale{ std::move(_scale) }
{}

Transform::Transform(const Vec3& _position, const Vec3& _rotation, const Vec3& _scale) noexcept
	: position{ _position }, rotation{ Maths::EulerAnglesToQuaternion(_rotation) }, scale{ _scale }
{}

//Transform::Transform(Vec3&& _position, const Vec3& _rotation, Vec3&& _scale) noexcept
//	: position{ std::move(_position) }, rotation{ Maths::EulerAnglesToQuaternion(_rotation) }, scale{ std::move(_scale) }
//{}

#pragma endregion

#pragma region Methods

void Transform::Display() const noexcept
{
	std::cout << "pos : ";
	position.Display();
	std::cout << "rot : ";
	rotation.Display();
	std::cout << "scale : ";
	scale.Display();
}

void Transform::Reset() noexcept
{
	position = Vec3::zero;
	rotation = Quaternion{ 1, 0, 0, 0 };
	scale = { 1.f, 1.f, 1.f };
}

Transform& Transform::Translate(const Vec3& _translation) noexcept
{
	position += _translation;
	return *this;
}

Transform& Transform::Rotate(const Quat& _rotation) noexcept
{
	/* TODO: can we use the operator *= ? */
	rotation = _rotation * rotation;
	return *this;
}

Transform& Transform::Rotate(const Vec3& _rotation) noexcept
{
	/* TODO: can we use the operator *= ? */
	rotation = Maths::EulerAnglesToQuaternion(_rotation) * rotation;
	return *this;
}

Transform& Transform::Scale(const Vec3& _scale) noexcept
{
	scale.x *= _scale.x;
	scale.y *= _scale.y;
	scale.z *= _scale.z;

	return *this;
}

#pragma endregion

#pragma region Operators

Transform& Transform::operator=(const Transform& _trs) noexcept
{
	position	= _trs.position;
	rotation	= _trs.rotation;
	scale		= _trs.scale;
	return *this;
}

Transform& Transform::operator=(Transform&& _trs) noexcept
{
	position	= std::move(_trs.position);
	rotation	= std::move(_trs.rotation);
	scale		= std::move(_trs.scale);
	return *this;
}

#pragma endregion

#pragma region External Operators

std::ostream& Galatea::operator<<(std::ostream& _os, const Transform& _trs) noexcept
{
	_os << "pos: " << _trs.position << " |  rot: " << _trs.rotation << " | scale: " << _trs.scale;
	return _os;
}

#pragma endregion