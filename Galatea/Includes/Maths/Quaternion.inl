#pragma region Constructor/Destructor

constexpr Quaternion::Quaternion() noexcept 
	: w{ 1.f }, x{ 0.f }, y{ 0.f }, z{ 0.f }
{}

constexpr Quaternion::Quaternion(const Quaternion& _q) noexcept 
	: w{ _q.w }, x{ _q.x }, y{ _q.y }, z{ _q.z }
{}

constexpr Quaternion::Quaternion(float _w, const Vec3& _v) noexcept 
	: w{ _w }, xyz{ _v }
{}

constexpr Quaternion::Quaternion(float _w, float _x, float _y, float _z) noexcept 
	: w{ _w }, x{ _x }, y{ _y }, z{ _z }
{}

Quaternion::Quaternion(const Vec3& _v, float _teta) noexcept 
		: w{ cosf(_teta * G_DEG2RAD / 2.f) }, xyz{ sinf(_teta * G_DEG2RAD / 2.f) * _v }
{}

Quaternion::Quaternion(const Mat4& _m) noexcept 
	: w{ 0.f }, xyz{ 0.f, 0.f, 0.f }
{
	float trace = _m.data2d[0][0] + _m.data2d[1][1] + _m.data2d[2][2];

	if (trace > 0) 
	{
		float S = sqrt(trace + 1.0f) * 2.f; // S=4*qw 
		w = 0.25f * S;
		x = (_m.data2d[2][1] - _m.data2d[1][2]) / S;
		y = (_m.data2d[0][2] - _m.data2d[2][0]) / S;
		z = (_m.data2d[1][0] - _m.data2d[0][1]) / S;
	}
	else if ((_m.data2d[0][0] > _m.data2d[1][1]) & (_m.data2d[0][0] > _m.data2d[2][2]))
	{
		float S = sqrt(1.0f + _m.data2d[0][0] - _m.data2d[1][1] - _m.data2d[2][2]) * 2.f; // S=4*qx 
		w = (_m.data2d[2][1] - _m.data2d[1][2]) / S;
		x = 0.25f * S;
		y = (_m.data2d[0][1] + _m.data2d[1][0]) / S;
		z = (_m.data2d[0][2] + _m.data2d[2][0]) / S;
	}
	else if (_m.data2d[1][1] > _m.data2d[2][2])
	{
		float S = sqrt(1.0f + _m.data2d[1][1] - _m.data2d[0][0] - _m.data2d[2][2]) * 2.f; // S=4*qy
		w = (_m.data2d[0][2] - _m.data2d[2][0]) / S;
		x = (_m.data2d[0][1] + _m.data2d[1][0]) / S;
		y = 0.25f * S;
		z = (_m.data2d[1][2] + _m.data2d[2][1]) / S;
	}
	else 
	{
		float S = sqrt(1.0f + _m.data2d[2][2] - _m.data2d[0][0] - _m.data2d[1][1]) * 2.f; // S=4*qz
		w = (_m.data2d[1][0] - _m.data2d[0][1]) / S;
		x = (_m.data2d[0][2] + _m.data2d[2][0]) / S;
		y = (_m.data2d[1][2] + _m.data2d[2][1]) / S;
		z = 0.25f * S;
	}

	std::cout << "Norme = " << Length() << std::endl;
	Normalize();
}

#pragma endregion

#pragma region Methods

void Quaternion::Display() const noexcept
{
	std::cout << "w = " << w << " | x = " << x << " | y = " << y << " | z = " << z << "\n";
}

/*Quaternion Quaternion::Zero() noexcept
{
	return Quaternion{ 0.f, 0.f, 0.f, 0.f };
}*/

constexpr void Quaternion::Reset() noexcept
{
	w = x = y = z = 0;
}

float Quaternion::Length() const noexcept
{
	return sqrt(w * w + x * x + y * y + z * z);
}

constexpr float Quaternion::SquareLength() const noexcept
{
	return (w * w + x * x + y * y + z * z);
}

Quaternion Quaternion::Normalized() const noexcept
{
	float l{ sqrt(w * w + x * x + y * y + z * z) };
	return Quaternion{ w / l, x / l, y / l, z / l };
}

void Quaternion::Normalize() noexcept
{
	float l{ sqrt(w * w + x * x + y * y + z * z) };

	w /= l;
	x /= l;
	y /= l;
	z /= l;
}

constexpr Quaternion Quaternion::Conjugated() const noexcept
{
	return Quaternion{ w, -x, -y, -z };
}

constexpr void Quaternion::Conjugate() noexcept
{
	x = -x;
	y = -y;
	z = -z;
}

constexpr Quaternion Quaternion::Inversed() const noexcept
{
	float u{ 1 / (w * w + x * x + y * y + z * z) };

	return Quaternion{ u * w, u * (-x), u * (-y), u * (-z) };
}

constexpr void Quaternion::Inverse() noexcept
{
	float u{ 1 / (w * w + x * x + y * y + z * z) };

	w /= u;
	x = u * (-x);
	y = u * (-y);
	z = u * (-z);
}

constexpr Quaternion Quaternion::Negated() const noexcept
{
	return Quaternion{ -w, -x, -y, -z };
}

constexpr void Quaternion::Negate() noexcept
{
	w = -w;
	x = -x;
	y = -y;
	z = -z;
}

constexpr Quaternion Quaternion::Difference(const Quaternion& _q) const noexcept
{
	return Inversed() * _q;
}

Mat4 Quaternion::ToMatrix() const noexcept
{
	Quaternion	q{ Normalized() };

	float x2 = q.x * q.x;
	float y2 = q.y * q.y;
	float z2 = q.z * q.z;

	float xy = q.x * q.y;
	float xz = q.x * q.z;
	float yz = q.y * q.z;
	float wx = q.w * q.x;
	float wy = q.w * q.y;
	float wz = q.w * q.z;

	Mat4 m = Mat4{	Vector4{ 1 - 2 * (y2 + z2),	2 * (xy - wz),		2 * (xz + wy),		0 },
					Vector4{ 2 * (xy + wz),		1 - 2 * (x2 + z2),	2 * (yz - wx),		0 },
					Vector4{ 2 * (xz - wy),		2 * (yz + wx),		1 - 2 * (x2 + y2),	0 },
					Vector4{ 0,					0,					0,					1 }
	};

	return m;
}

constexpr Quaternion Quaternion::Lerp(const Quaternion& _q, float _t) const noexcept
{
	float bias{ (*this ^ _q) >= 0 ? 1.f : -1.f };
	return Quaternion{	w * (1 - _t) * bias + _q.w * _t,
						x * (1 - _t) * bias + _q.x * _t,
						y * (1 - _t) * bias + _q.y * _t,
						z * (1 - _t) * bias + _q.z * _t };
}

Quaternion Quaternion::Slerp(const Quaternion& _q, float _t) const noexcept
{
	float theta{ acos(w * _q.w + x * _q.x + y * _q.y + z * _q.z) };
	if (theta < 0) theta = -theta;
	float sin_tDelta{ sin((1 - _t) * theta) };
	float sintDelta{ sin(_t * theta) };
	float sinDelta{ sin(theta) };

	return Quaternion{	(w * sin_tDelta + _q.w * sintDelta) / sinDelta,
						(x * sin_tDelta + _q.x * sintDelta) / sinDelta,
						(y * sin_tDelta + _q.y * sintDelta) / sinDelta,
						(z * sin_tDelta + _q.z * sintDelta) / sinDelta };
}

Quaternion Quaternion::NLerp(const Quaternion& _q, float _t) const noexcept
{
	return Lerp(_q, _t).Normalized();
}

Quaternion Quaternion::NSlerp(const Quaternion& _q, float _t) const noexcept
{
	return Normalized().Slerp(_q.Normalized(), _t);
}

Quaternion Quaternion::RotationBetweenVector(const Vec3& _start, const Vec3& _end) noexcept
{
	if (_start.IsCollinear(_end))
		return Quaternion{ sqrtf(_start.SquareLength() * _end.SquareLength()) + _start.DotProduct(_end), Vec3(-_start.y, _start.x, _start.z) }.Normalized();
	else
		return Quaternion{ sqrtf(_start.SquareLength() * _end.SquareLength()) + _start.DotProduct(_end), _start.CrossProduct(_end) }.Normalized();

}

Quaternion Quaternion::FromEulerAngle(const Vec3& _angles) noexcept
{
	/* Abbreviations for the various angular functions */
	float	cy{ cos(_angles.yaw * G_DEG2RAD * 0.5f) };
	float	sy{ sin(_angles.yaw * G_DEG2RAD * 0.5f) };
	float	cp{ cos(_angles.pitch * G_DEG2RAD * 0.5f) };
	float	sp{ sin(_angles.pitch * G_DEG2RAD * 0.5f) };
	float	cr{ cos(_angles.roll * G_DEG2RAD * 0.5f) };
	float	sr{ sin(_angles.roll * G_DEG2RAD * 0.5f) };

	return Quaternion{	cy * cp * cr + sy * sp * sr,
						sy * cp * sr + cy * sp * cr,
						sy * cp * cr - cy * sp * sr,
						cy * cp * sr - sy * sp * cr };
}

Vec3 Quaternion::ToEulerAngles() const noexcept
{
	Quaternion	q{ Normalized() };

	float sinThetaY = 2 * (q.x * q.z + q.w * q.y);
	float cosThetaY = sqrtf(1 - sinThetaY * sinThetaY);
	float sinThetaX;
	float cosThetaX;
	float sinThetaZ;
	float cosThetaZ;

	if (cosThetaY == 0)
	{
		sinThetaZ = 0;
		cosThetaZ = 1;
		sinThetaX = 2 * (q.y * q.z + q.w * q.x);
		cosThetaX = 1 - 2 * (q.x * q.x + q.z * q.z);
	}
	else
	{
		sinThetaX = -2 * (q.y * q.z - q.w * q.x) / cosThetaY;
		cosThetaX = (1 - 2 * (q.x * q.x + q.y * q.y)) / cosThetaY;
		sinThetaZ = -2 * (q.x * q.y - q.w * q.z) / cosThetaY;
		cosThetaZ = (1 - 2 * (q.y * q.y + q.z * q.z)) / cosThetaY;
	}

	return {atan2(sinThetaX, cosThetaX) * G_RAD2DEG,
			atan2(sinThetaY, cosThetaY) * G_RAD2DEG,
			atan2(sinThetaZ, cosThetaZ) * G_RAD2DEG };
}

#pragma endregion

#pragma region Operator

constexpr Quaternion Quaternion::operator+(const Quaternion& _q) const noexcept
{
	return Quaternion{ w + _q.w, x + _q.x, y + _q.y, z + _q.z };
}

constexpr void Quaternion::operator+=(const Quaternion& _q) noexcept
{
	w += _q.w;
	x += _q.x;
	y += _q.y;
	z += _q.z;
}


constexpr Quaternion Quaternion::operator-(const Quaternion& _q) const noexcept
{
	return Quaternion{ w - _q.w, x - _q.x, y - _q.y, z - _q.z };
}

constexpr void Quaternion::operator-=(const Quaternion& _q) noexcept
{
	w -= _q.w;
	x -= _q.x;
	y -= _q.y;
	z -= _q.z;
}

constexpr Quaternion Quaternion::operator*(const Quaternion& _q) const noexcept
{
	return Quaternion{	w * _q.w - x * _q.x - y * _q.y - z * _q.z,
						w * _q.x + x * _q.w + y * _q.z - z * _q.y,
						w * _q.y + y * _q.w + z * _q.x - x * _q.z,
						w * _q.z + z * _q.w + x * _q.y - y * _q.x };
}

constexpr void Quaternion::operator*=(const Quaternion& _q) noexcept
{
	w = w * _q.w - x * _q.x - y * _q.y - z * _q.z;
	x = w * _q.x + x * _q.w + y * _q.z - z * _q.y;
	y = w * _q.y + y * _q.w + z * _q.x - x * _q.z;
	z = w * _q.z + z * _q.w + x * _q.y - y * _q.x;
}

constexpr Quaternion Quaternion::operator*(float _s) const noexcept
{
	return Quaternion{ w * _s, x * _s, y * _s, z * _s };
}

constexpr void Quaternion::operator*=(float _s) noexcept
{
	w *= _s;
	x *= _s;
	y *= _s;
	z *= _s;
}

constexpr float Quaternion::operator^(const Quaternion& _q) const noexcept
{
	return w * _q.w + x * _q.x + y * _q.y + z * _q.z;
}

constexpr Quaternion Quaternion::operator/(float _s) const noexcept
{
	if (_s != 0)
		return Quaternion{ w / _s, x / _s, y / _s, z / _s };
}

constexpr void Quaternion::operator/=(float _s) noexcept
{
	if (_s == 0)
		return;

	w /= _s;
	x /= _s;
	y /= _s;
	z /= _s;
}

constexpr Quaternion Quaternion::operator=(const Quaternion& _q) noexcept
{
	w = _q.w;
	x = _q.x;
	y = _q.y;
	z = _q.z;

	return *this;
}

constexpr Quaternion Quaternion::operator=(const Vec3& _v) noexcept
{
	w = 1;
	xyz = _v;

	return *this;
}

Quaternion Quaternion::operator=(const Mat4& _m) noexcept
{
	float trace = _m.data2d[0][0] + _m.data2d[1][1] + _m.data2d[2][2];

	if (trace > 0)
	{
		//std::cout << "Premier if\n";
		float S = sqrt(trace + 1.0f) * 2.f; // S=4*qw 
		w = 0.25f * S;
		x = (_m.data2d[2][1] - _m.data2d[1][2]) / S;
		y = (_m.data2d[0][2] - _m.data2d[2][0]) / S;
		z = (_m.data2d[1][0] - _m.data2d[0][1]) / S;
	}
	else if ((_m.data2d[0][0] > _m.data2d[1][1]) && (_m.data2d[0][0] > _m.data2d[2][2]))
	{
		//std::cout << "Deuxieme if\n";
		float S = sqrt(1.0f + _m.data2d[0][0] - _m.data2d[1][1] - _m.data2d[2][2]) * 2.f; // S=4*qx 
		w = (_m.data2d[2][1] - _m.data2d[1][2]) / S;
		x = 0.25f * S;
		y = (_m.data2d[0][1] + _m.data2d[1][0]) / S;
		z = (_m.data2d[0][2] + _m.data2d[2][0]) / S;
	}
	else if (_m.data2d[1][1] > _m.data2d[2][2])
	{
		//std::cout << "Troisieme if\n";
		float S = sqrt(1.0f + _m.data2d[1][1] - _m.data2d[0][0] - _m.data2d[2][2]) * 2.f; // S=4*qy
		w = (_m.data2d[0][2] - _m.data2d[2][0]) / S;
		x = (_m.data2d[0][1] + _m.data2d[1][0]) / S;
		y = 0.25f * S;
		z = (_m.data2d[1][2] + _m.data2d[2][1]) / S;
	}
	else
	{
		//std::cout << "Quatrieme if\n";
		float S = sqrt(1.0f + _m.data2d[2][2] - _m.data2d[0][0] - _m.data2d[1][1]) * 2.f; // S=4*qz
		w = (_m.data2d[1][0] - _m.data2d[0][1]) / S;
		x = (_m.data2d[0][2] + _m.data2d[2][0]) / S;
		y = (_m.data2d[1][2] + _m.data2d[2][1]) / S;
		z = 0.25f * S;
	}
	Normalize();

	return *this;
}

constexpr Vector3 Quaternion::operator*(const Vec3& point) const noexcept
{
	Vector3 vector;
	float x2 = x * 2.f;
	float y2 = y * 2.f;
	float z2 = z * 2.f;
	float x²2 = x * x2;
	float y²2 = y * y2;
	float z²2 = z * z2;
	float xy2 = x * y2;
	float xz2 = x * z2;
	float yz2 = y * z2;
	float wx2 = w * x2;
	float wy2 = w * y2;
	float wz2 = w * z2;
	vector.x = (((1.f - (y²2 + z²2)) * point.x) + ((xy2 - wz2) * point.y)) + ((xz2 + wy2) * point.z);
	vector.y = (((xy2 + wz2) * point.x) + ((1.f - (x²2 + z²2)) * point.y)) + ((yz2 - wx2) * point.z);
	vector.z = (((xz2 - wy2) * point.x) + ((yz2 + wx2) * point.y)) + ((1.f - (x²2 + y²2)) * point.z);
	return vector;
}

constexpr bool		Quaternion::operator==(const Quaternion& _q)	const	noexcept
{
	float G_FLT_EPSILON = 0.001f;
	return    w >= _q.w - G_FLT_EPSILON && w <= _q.w + G_FLT_EPSILON &&
		x >= _q.x - G_FLT_EPSILON && x <= _q.x + G_FLT_EPSILON &&
		y >= _q.y - G_FLT_EPSILON && y <= _q.y + G_FLT_EPSILON &&
		z >= _q.z - G_FLT_EPSILON && z <= _q.z + G_FLT_EPSILON;
}


#pragma endregion

#pragma region External Methods

namespace Maths
{
	/* TODO: test the methods in a 3D world */
	Vec3 QuaternionToEulerAngles(const Quaternion& _quat) noexcept
	{
		Quaternion	q{ _quat.Normalized() };

		float sinThetaY = 2 * (q.x * q.z + q.w * q.y);
		float cosThetaY = sqrtf(1 - sinThetaY * sinThetaY);
		float sinThetaX;
		float cosThetaX;
		float sinThetaZ;
		float cosThetaZ;

		if (cosThetaY == 0)
		{
			sinThetaZ = 0;
			cosThetaZ = 1;
			sinThetaX = 2 * (q.y * q.z + q.w * q.x);
			cosThetaX = 1 - 2 * (q.x * q.x + q.z * q.z);
		}
		else
		{
			sinThetaX = -2 * (q.y * q.z - q.w * q.x) / cosThetaY;
			cosThetaX = (1 - 2 * (q.x * q.x + q.y * q.y)) / cosThetaY;
			sinThetaZ = -2 * (q.x * q.y - q.w * q.z) / cosThetaY;
			cosThetaZ = (1 - 2 * (q.y * q.y + q.z * q.z)) / cosThetaY;
		}

		return {atan2(sinThetaX, cosThetaX) * G_RAD2DEG,
				atan2(sinThetaY, cosThetaY) * G_RAD2DEG,
				atan2(sinThetaZ, cosThetaZ) * G_RAD2DEG };

		//return _quat.ToMatrix().ToEulerAngles();
	}

	Quaternion EulerAnglesToQuaternion(const Vec3& _angles) noexcept
	{
		/* Abbreviations for the various angular functions */
		float	cy{ cos(_angles.yaw * G_DEG2RAD * 0.5f) };
		float	sy{ sin(_angles.yaw * G_DEG2RAD * 0.5f) };
		float	cp{ cos(_angles.pitch * G_DEG2RAD * 0.5f) };
		float	sp{ sin(_angles.pitch * G_DEG2RAD * 0.5f) };
		float	cr{ cos(_angles.roll * G_DEG2RAD * 0.5f) };
		float	sr{ sin(_angles.roll * G_DEG2RAD * 0.5f) };

		return Quaternion{	cy * cp * cr + sy * sp * sr,
							sy * cp * sr + cy * sp * cr,
							sy * cp * cr - cy * sp * sr,
							cy * cp * sr - sy * sp * cr	};
	}

	Mat4 QuaternionToMatrix(const Quat& _q) noexcept
	{
		Quat	q{ _q.Normalized() };

		float x2 = q.x * q.x;
		float y2 = q.y * q.y;
		float z2 = q.z * q.z;

		float xy = q.x * q.y;
		float xz = q.x * q.z;
		float yz = q.y * q.z;
		float wx = q.w * q.x;
		float wy = q.w * q.y;
		float wz = q.w * q.z;
		
		Mat4 m = Mat4{	Vector4{ 1 - 2 * (y2 + z2),	2 * (xy - wz),		2 * (xz + wy),		0 },
						Vector4{ 2 * (xy + wz),		1 - 2 * (x2 + z2),	2 * (yz - wx),		0 },
						Vector4{ 2 * (xz - wy),		2 * (yz + wx),		1 - 2 * (x2 + y2),	0 },
						Vector4{ 0,					0,					0,					1 }
		};

		return m;
	}
}

#pragma endregion

#pragma region ExternalOperator

std::ostream& operator<<(std::ostream& _os, const Quaternion& _q) noexcept
{
	_os << "w = " << (_q.w < 0.001 && _q.w > -0.001 ? 0.0 : _q.w) << " | ";
	_os << "x = " << (_q.x < 0.001 && _q.x > -0.001 ? 0.0 : _q.x) << " | ";
	_os << "y = " << (_q.y < 0.001 && _q.y > -0.001 ? 0.0 : _q.y) << " | ";
	_os << "z = " << (_q.z < 0.001 && _q.z > -0.001 ? 0.0 : _q.z);

	return _os;
}

#pragma endregion
