#pragma once

#pragma region Constructor/Destructor

constexpr Vec4::Vec4(float _x, float _y, float _z, float _w) noexcept
	: x(_x), y(_y), z(_z), w{ _w }
{}

constexpr Vec4::Vec4(const Vec4& _v) noexcept
	: x(_v.x), y(_v.y), z(_v.z), w(_v.w)
{}

constexpr Vec4::Vec4(Vec4&& _v) noexcept
	: x(std::move(_v.x)), y(std::move(_v.y)), z(std::move(_v.z)), w(std::move(_v.w))
{}

constexpr Vec4::Vec4(const Vec3& _v, float _w) noexcept 
	: x(_v.x), y(_v.y), z(_v.z), w{ _w }
{}

#if USE_SIMD
Vec4::Vec4(const __m128& _v) noexcept
	:row{_v}
{}
#endif	

#pragma endregion 

#pragma region Methods

void Vec4::Display() const noexcept
{
	std::cout << "x: " << x << " y: " << y << " z: " << z << " w: " << w << std::endl;
}

constexpr Vec4 Vec4::Homogenized() const noexcept
{
	if (w != 0)
		return Vec4(x / w, y / w, z / w, w);

	return Vec4();
}

constexpr void Vec4::Homogenize() noexcept
{
	if (w != 0)
	{
		x /= w;
		y /= w;
		z /= w;
	}
}

constexpr float Vec4::SquareLength() const noexcept
{
	return x * x + y * y + z * z;
}

float Vec4::Length() const noexcept
{
	return sqrtf(x * x + y * y + z * z);

}

Vec4 Vec4::Normalized() const noexcept
{
	return	(*this) / Length();
}

void Vec4::Normalize() noexcept
{
	(*this) /= Length();
}

constexpr Vec4 Vec4::Negated() const noexcept
{
	return (*this) * -1;
}

constexpr void Vec4::Negate() noexcept
{
	(*this) *= -1;
}

constexpr float Vec4::DotProduct(const Vec4& _v) const noexcept
{
	return x * _v.x + y * _v.y + z * _v.z + w * _v.w;
}

constexpr Vec4 Vec4::Lerp(const Vec4& _v, float _t) const noexcept
{
	return (*this) * (1 - _t) + _v * _t;
}

#pragma endregion 

#pragma region Operator

constexpr Vec4 Vec4::operator=(const Vec4& v) noexcept
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;

	return *this;
}

constexpr Vec4 Vec4::operator+(const Vec4& _v) const noexcept
{
	return Vec4(x + _v.x, y + _v.y, z + _v.z, w + _v.w);
}

constexpr Vec4 Vec4::operator-(const Vec4& _v) const noexcept
{
	return Vec4(x - _v.x, y - _v.y, z -_v.z, w - _v.w);
}

constexpr Vec4 Vec4::operator*(float _scale) const noexcept
{
	return Vec4(x * _scale, y * _scale, z * _scale, w * _scale);
}

constexpr Vec4 Vec4::operator/(float _scale) const noexcept
{
	return Vec4(x / _scale, y / _scale, z / _scale, w / _scale);
}

constexpr void Vec4::operator+=(const Vec4& _v) noexcept
{
	x += _v.x; 
	y += _v.y; 
	z += _v.z;
	w += _v.w;
}

constexpr void Vec4::operator-=(const Vec4& _v) noexcept
{
	x -= _v.x;
	y -= _v.y;
	z -= _v.z;
	w -= _v.w;
}

constexpr void Vec4::operator*=(float _scale) noexcept
{
	x *= _scale;
	y *= _scale;
	z *= _scale;
	w *= _scale;
}

constexpr void Vec4::operator/=(float _scale) noexcept
{
	x /= _scale;
	y /= _scale;
	z /= _scale;
	w /= _scale;
}

constexpr bool Vec4::operator==(const Vec4& _v) const noexcept
{
	return (x >= _v.x - FLT_EPSILON && x <= _v.x + FLT_EPSILON &&
			y >= _v.y - FLT_EPSILON && y <= _v.y + FLT_EPSILON &&
			z >= _v.z - FLT_EPSILON && z <= _v.z + FLT_EPSILON &&
			w >= _v.w - FLT_EPSILON && w <= _v.w + FLT_EPSILON);
}

constexpr float& Vec4::operator[](unsigned _index) noexcept
{
	if (_index >= 0 && _index <= 3)
		return xyzw[_index];
}

Vec4::operator Vec3 () noexcept
{
	return Vec3(x, y, z);
}

#pragma endregion 

#pragma region External Methods

static std::wstring ToString(const Vec4& v)
{
	std::string s = "( ";
	s += std::to_string(v.x);
	s += " , ";
	s += std::to_string(v.y);
	s += " , ";
	s += std::to_string(v.z);
	s += " , ";
	s += std::to_string(v.w);
	s += ")";

	std::wstringstream _s;
	_s << s.c_str();
	return _s.str();
}

#pragma endregion 

#pragma region ExternalOperator

Vec4 operator-(const Vec4 _v) noexcept //negate vector
{
	return { -_v.x, -_v.y, -_v.z, _v.w };
}

std::ostream& operator<<(std::ostream& _os, const Vec4& _v) noexcept
{
	_os << "x: " << _v.x << " y: " << _v.y << " z: " << _v.z << " w: " << _v.w << "\n";
	return _os;
}

#pragma endregion 
