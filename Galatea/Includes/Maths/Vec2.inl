#pragma once

#pragma region Constructor/Destructor

constexpr Vec2::Vec2(float _x, float _y) noexcept
	: x{ _x }, y{ _y }
{}

constexpr Vec2::Vec2(const Vec2& _v) noexcept
	: x{ _v.x }, y{ _v.y }
{}

constexpr Vec2::Vec2(Vec2&& _v) noexcept
	: x{ std::move(_v.x) }, y{ std::move(_v.y) }
{}

#pragma endregion 

#pragma region Methods

void Vec2::Display() const noexcept
{
	std::cout << "x: " << x << " y: " << y << std::endl;
}

constexpr float Vec2::SquareLength() const noexcept
{
	return x * x + y * y;
}

float Vec2::Length() const noexcept
{
	return sqrt(x * x + y * y);
}

Vec2 Vec2::Normalized() const noexcept
{	
	float l = Length();
	if (l != 0.f)
		return (*this) / l;
	else
		return (*this);
}

void Vec2::Normalize() noexcept
{
	float l = Length();
	if (l != 0.f)
		(*this) /= l;
}

constexpr Vec2 Vec2::Negated() const noexcept
{
	return Vec2(-x, -y);
}

constexpr void Vec2::Negate() noexcept
{
	x = -x;
	y = -y;
}

constexpr float Vec2::DotProduct(const Vec2& _v) const noexcept
{
	return x * _v.x + y * _v.y;
}

float Vec2::Angle(const Vec2& _v) const	noexcept
{
	if (SquareLength() == 0.f || _v.SquareLength() == 0.f)
		return 0.0f;
	else
		return acosf(std::fmin(std::fmaxf(DotProduct(_v) / (Length() * _v.Length()), -1.f), 1.f));
}

float Vec2::DistanceBetweenPoint(const Vec2& _v) const	noexcept
{
	return (*this - _v).Length();
}

float Vec2::SquareDistanceBetweenPoint(const Vec2& _v) const noexcept
{
	return (*this - _v).SquareLength();
}


#pragma endregion 

#pragma region Operator

constexpr Vec2 Vec2::operator+(const Vec2& _v) const noexcept
{
	return Vec2(x + _v.x, y + _v.y);
}

constexpr Vec2 Vec2::operator-(const Vec2& _v) const noexcept
{
	return Vec2(x - _v.x, y - _v.y);
}

constexpr Vec2 Vec2::operator*(float _scale) const noexcept
{
	return Vec2(x * _scale, y * _scale);
}

constexpr Vec2 Vec2::operator/(float _scale) const noexcept
{
	return Vec2(x / _scale, y / _scale);
}

constexpr Vec2& Vec2::operator=(const Vec2& _v) noexcept
{
	x = _v.x;
	y = _v.y;
	return (*this);
}

constexpr void Vec2::operator+=(const Vec2& _v) noexcept
{
	x += _v.x;
	y += _v.y;
}

constexpr void Vec2::operator-=(const Vec2& _v) noexcept
{
	x -= _v.x;
	y -= _v.y;
}

constexpr void Vec2::operator*=(float _scale) noexcept
{
	x *= _scale;
	y *= _scale;
}

constexpr void Vec2::operator/=(float _scale) noexcept
{
	x /= _scale;
	y /= _scale;
}

bool Vec2::operator==(const Vec2& _v) const noexcept
{
	return (x >= _v.x - FLT_EPSILON && x <= _v.x + FLT_EPSILON &&
			y >= _v.y - FLT_EPSILON && y <= _v.y + FLT_EPSILON);
}

constexpr float& Vec2::operator[](unsigned _index) noexcept
{
	if (_index == 0 || _index == 1)
		return xy[_index];
}

#pragma endregion 

#pragma region External Methods

static std::wstring ToString(const Vec2& v)
{
	std::string s = "( ";
	s += std::to_string(v.x);
	s += " , ";
	s += std::to_string(v.y);
	s += ")";

	std::wstringstream _s;
	_s << s.c_str();
	return _s.str();
}

#pragma endregion

#pragma region External Operator

std::ostream& operator<<(std::ostream& _os, const Vec2& _v) noexcept
{
	_os << "x: " <<  _v.x << " y: " << _v.y << "\n";
	return _os;
}
#pragma endregion