#pragma once

//#include "Vec4.h"

#pragma region Constructors/Destructors

constexpr Vec3::Vec3(float _x, float _y, float _z) noexcept
	: x{ _x }, y{ _y }, z{ _z }
{}

constexpr Vec3::Vec3(const Vec3& _v) noexcept
	: x{ _v.x }, y{ _v.y }, z{ _v.z }
{}

constexpr Vec3::Vec3(Vec3&& _v) noexcept
	: x{ std::move(_v.x) }, y{ std::move(_v.y) }, z{ std::move(_v.z) }
{}

constexpr Vec3::Vec3(const Vec3& _a, const Vec3& _b) noexcept
	: x (_b.x - _a.x), y(_b.y - _a.y), z(_b.z - _a.z)
{}

constexpr Vec3::Vec3(const Vec2& _v, float _z) noexcept
	: x{ _v.x }, y{ _v.y }, z{ _z }
{}

constexpr Vec3::Vec3(float _x, const Vec2& _v) noexcept
	: x{ _x }, y{ _v.x }, z{ _v.y }
{}


/*Vec3::Vec3(const Vec4& _v) noexcept
	: x{ _v.x }, y{ _v.y }, z{ _v.z }
{}*/

#pragma endregion

#pragma region Methods

void Vec3::Display() const noexcept
{
	std::cout << "x: " << x << " y: " << y << " z: " << z << "\n";
}

constexpr float Vec3::SquareLength() const noexcept
{
	return x * x + y * y + z * z;
}

float Vec3::Length() const noexcept
{
	return sqrtf(x * x + y * y + z * z);
}

Vec3 Vec3::Normalized() const noexcept
{
	Vec3	v;
	float	l = Length();

	if (l != 0.f)
	{
		v.x = x / l;
		v.y = y / l;
		v.z = z / l;
	}

	return v;
}

void Vec3::Normalize() noexcept
{
	float	l = Length();

	if (l != 0.f)
	{
		x /= l;
		y /= l;
		z /= l;
	}
}

constexpr Vec3 Vec3::Negated() const noexcept
{
	return Vec3(-x, -y, -z);
}

constexpr void Vec3::Negate() noexcept
{
	x *= -1;
	y *= -1;
	z *= -1;
}

constexpr float Vec3::DotProduct(const Vec3& _v) const noexcept
{
	return x * _v.x + y * _v.y + z * _v.z;
}

float Vec3::Angle(const Vec3& _v) const noexcept
{
	if (SquareLength() == 0.f || _v.SquareLength() == 0.f)
		return 0.0f;
	else
		return acosf(std::fmin(std::fmaxf(DotProduct(_v) / (Length() * _v.Length()), -1.f), 1.f));
}

constexpr bool Vec3::IsCollinear(const Vec3& _v) const noexcept
{
	if (CrossProduct(_v) == 0.f)
		return true;
	return false;
}

constexpr Vec3 Vec3::CrossProduct(const Vec3& _v) const noexcept
{
	return Vec3(y * _v.z - z * _v.y,
				z * _v.x - x * _v.z,
				x * _v.y - y * _v.x);
}

constexpr Vec3 Vec3::Lerp(const Vec3& _v, float _t) const noexcept
{
	return *this * (1 - _t) + _v * _t;
}

float	Vec3::DistanceBetweenPoint(const Vec3& _v) const	noexcept
{
	return (*this - _v).Length();
}

constexpr float Vec3::SquareDistanceBetweenPoint(const Vec3& _v) const noexcept
{
	return (*this - _v).SquareLength();
}

#pragma endregion

#pragma region Operator 

constexpr Vec3 Vec3::operator+(const Vec3& _v) const noexcept
{
	return Vec3(x + _v.x, y + _v.y, z + _v.z);
}

constexpr Vec3 Vec3::operator-(const Vec3& _v) const noexcept
{
	return Vec3(x - _v.x, y - _v.y, z - _v.z);
}

constexpr Vec3 Vec3::operator*(float _scale) const noexcept
{
	return Vec3(x * _scale, y * _scale, z * _scale);
}

constexpr Vec3 Vec3::operator*(const Vec3& _v) const noexcept
{
	return Vec3(y * _v.z - z * _v.y,
				z * _v.x - x * _v.z,
				x * _v.y - y * _v.x);
}

constexpr Vec3 Vec3::operator/(float _scale) const noexcept
{
	return Vec3(x / _scale, y / _scale, z / _scale);
}

constexpr Vec3& Vec3::operator=(const Vec3& _v) noexcept
{
	x = _v.x;
	y = _v.y;
	z = _v.z;

	return (*this);
}

constexpr Vec3& Vec3::operator=(Vec3&& _v) noexcept
{
	x = std::move(_v.x);
	y = std::move(_v.y);
	z = std::move(_v.z);

	return (*this);
}

constexpr void Vec3::operator+=(const Vec3& _v) noexcept
{
	x += _v.x;
	y += _v.y;
	z += _v.z; 
}

constexpr void Vec3::operator-=(const Vec3& _v) noexcept
{
	x -= _v.x;
	y -= _v.y;
	z -= _v.z; 
}

constexpr void Vec3::operator*=(float _scale) noexcept
{
	x *= _scale;
	y *= _scale;
	z *= _scale; 
}

constexpr void Vec3::operator*=(const Vec3& _v) noexcept
{
	Vec3	tmp(*this);
	x = tmp.y * _v.z - tmp.z * _v.y;
	y = tmp.z * _v.x - tmp.x * _v.z;
	z = tmp.x * _v.y - tmp.y * _v.x;
}

constexpr void Vec3::operator/=(float _scale) noexcept
{
	x /= _scale;
	y /= _scale;
	z /= _scale;
}

constexpr bool Vec3::operator==(const Vec3& _v) const noexcept
{
	return (x >= _v.x - G_EPSILONE && x <= _v.x + G_EPSILONE &&
			y >= _v.y - G_EPSILONE && y <= _v.y + G_EPSILONE &&
			z >= _v.z - G_EPSILONE && z <= _v.z + G_EPSILONE);
}

constexpr bool Vec3::operator==(float _scale) const noexcept
{
	return (x >= _scale - FLT_EPSILON && x <= _scale + FLT_EPSILON &&
			y >= _scale - FLT_EPSILON && y <= _scale + FLT_EPSILON &&
			z >= _scale - FLT_EPSILON && z <= _scale + FLT_EPSILON);
}

constexpr bool Vec3::operator!=(const Vec3& _v) const noexcept
{
	return !(	x >= _v.x - FLT_EPSILON && x <= _v.x + FLT_EPSILON &&
				y >= _v.y - FLT_EPSILON && y <= _v.y + FLT_EPSILON &&
				z >= _v.z - FLT_EPSILON && z <= _v.z + FLT_EPSILON);
}

constexpr Vec3 Vec3::operator-() const noexcept//negate vector
{
	return { -x, -y, -z };
}

constexpr float& Vec3::operator[](unsigned _index) noexcept
{
	if (_index == 0 || _index == 1 || _index == 2)
		return xyz[_index];
}

#pragma endregion

#pragma region External Methods

static std::wstring ToString(const Vec3& v)
{
	std::string s = "( ";
	s += std::to_string(v.x);
	s += " , ";
	s += std::to_string(v.y);
	s += " , ";
	s += std::to_string(v.z);
	s += ")";

	std::wstringstream _s;
	_s << s.c_str();
	return _s.str();
}

#pragma endregion

#pragma region External Operator

constexpr Vec3 operator*(const float& _f, const Vec3 _v) noexcept
{
	return { _v.x * _f, _v.y * _f, _v.z * _f };
}

std::ostream& operator<<(std::ostream& _os, const Vec3& _v) noexcept
{
	_os << "x: " << _v.x << " y: " << _v.y << " z: " << _v.z;
	return _os;
}

#pragma endregion