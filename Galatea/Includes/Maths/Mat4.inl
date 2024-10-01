
#pragma region Constructor

constexpr Mat4::Mat4() noexcept
	: data{}
{
	for (int i{ 0 }; i < 16; ++i)
		data[i] = 0;
}

constexpr Mat4::Mat4(const Mat4& _m) noexcept
	: data{}
{
	for (int i{ 0 }; i < 16; ++i)
		data[i] = _m.data[i];
}

Mat4::Mat4(const Vec4& _v1, const Vec4& _v2, const Vec4& _v3, const Vec4& _v4) noexcept
{
	data[0] = _v1.x;
	data[1] = _v1.y;
	data[2] = _v1.z;
	data[3] = _v1.w;
	data[4] = _v2.x;
	data[5] = _v2.y;
	data[6] = _v2.z;
	data[7] = _v2.w;
	data[8] = _v3.x;
	data[9] = _v3.y;
	data[10] = _v3.z;
	data[11] = _v3.w;
	data[12] = _v4.x;
	data[13] = _v4.y;
	data[14] = _v4.z;
	data[15] = _v4.w;
}

#pragma endregion

#pragma region Methods

constexpr Mat4 Mat4::Zero() noexcept
{
	Mat4 m;
	for (unsigned int i{ 0 }; i < 16; i++)
		m.data[i] = 0;
	return m;
}

void Mat4::Display() const noexcept
{
	std::cout << "| ";
	for (unsigned int i = 0; i < 16; i++)
	{
		if (i != 0 && i % 4 == 0)
			std::cout << "\n| ";
		std::cout << data[i] << " | ";
	}
	std::cout << "\n";
}

constexpr Mat4 Mat4::Transposed() const noexcept
{
	Mat4 Result;

	Result.data2d[0][0] = data2d[0][0];
	Result.data2d[0][1] = data2d[1][0];
	Result.data2d[0][2] = data2d[2][0];
	Result.data2d[0][3] = data2d[3][0];

	Result.data2d[1][0] = data2d[0][1];
	Result.data2d[1][1] = data2d[1][1];
	Result.data2d[1][2] = data2d[2][1];
	Result.data2d[1][3] = data2d[3][1];

	Result.data2d[2][0] = data2d[0][2];
	Result.data2d[2][1] = data2d[1][2];
	Result.data2d[2][2] = data2d[2][2];
	Result.data2d[2][3] = data2d[3][2];

	Result.data2d[3][0] = data2d[0][3];
	Result.data2d[3][1] = data2d[1][3];
	Result.data2d[3][2] = data2d[2][3];
	Result.data2d[3][3] = data2d[3][3];

	return Result;
}

void Mat4::Transpose() noexcept
{
	Mat4 Result;

	Result.data2d[0][0] = data2d[0][0];
	Result.data2d[0][1] = data2d[1][0];
	Result.data2d[0][2] = data2d[2][0];
	Result.data2d[0][3] = data2d[3][0];

	Result.data2d[1][0] = data2d[0][1];
	Result.data2d[1][1] = data2d[1][1];
	Result.data2d[1][2] = data2d[2][1];
	Result.data2d[1][3] = data2d[3][1];

	Result.data2d[2][0] = data2d[0][2];
	Result.data2d[2][1] = data2d[1][2];
	Result.data2d[2][2] = data2d[2][2];
	Result.data2d[2][3] = data2d[3][2];

	Result.data2d[3][0] = data2d[0][3];
	Result.data2d[3][1] = data2d[1][3];
	Result.data2d[3][2] = data2d[2][3];
	Result.data2d[3][3] = data2d[3][3];

	*this = Result;
}

Mat4 Mat4::Inverse() const noexcept
{
	Mat4		m;

	const float s0{ data[0] }, s1{ data[1] }, s2{ data[2] }, s3{ data[3] };
	const float s4{ data[4] }, s5{ data[5] }, s6{ data[6] }, s7{ data[7] };
	const float s8{ data[8] }, s9{ data[9] }, s10{ data[10] }, s11{ data[11] };
	const float s12{ data[12] }, s13{ data[13] }, s14{ data[14] }, s15{ data[15] };

	const float s10_15{ s10 * s15 }, s11_14{ s11 * s14 }, s6_15{ s6 * s15 }, s7_14{ s7 * s14 };
	const float s6_11{ s6 * s11 }, s7_10{ s7 * s10 }, s2_15{ s2 * s15 }, s3_14{ s3 * s14 };
	const float s2_11{ s2 * s11 }, s3_10{ s3 * s10 }, s2_7{ s2 * s7 }, s3_6{ s3 * s6 };

	float inv[16];
	inv[0] = s5 * s10_15 - s5 * s11_14 - s9 * s6_15 + s9 * s7_14 + s13 * s6_11 - s13 * s7_10;
	inv[1] = -s1 * s10_15 + s1 * s11_14 + s9 * s2_15 - s9 * s3_14 - s13 * s2_11 + s13 * s3_10;
	inv[2] = s1 * s6_15 - s1 * s7_14 - s5 * s2_15 + s5 * s3_14 + s13 * s2_7 - s13 * s3_6;
	inv[3] = -s1 * s6_11 + s1 * s7_10 + s5 * s2_11 - s5 * s3_10 - s9 * s2_7 + s9 * s3_6;
	inv[4] = -s4 * s10_15 + s4 * s11_14 + s8 * s6_15 - s8 * s7_14 - s12 * s6_11 + s12 * s7_10;
	inv[5] = s0 * s10_15 - s0 * s11_14 - s8 * s2_15 + s8 * s3_14 + s12 * s2_11 - s12 * s3_10;
	inv[6] = -s0 * s6_15 + s0 * s7_14 + s4 * s2_15 - s4 * s3_14 - s12 * s2_7 + s12 * s3_6;
	inv[7] = s0 * s6_11 - s0 * s7_10 - s4 * s2_11 + s4 * s3_10 + s8 * s2_7 - s8 * s3_6;

	inv[8] = s4 * s9 * s15 - s4 * s11 * s13 - s8 * s5 * s15 + s8 * s7 * s13 + s12 * s5 * s11 - s12 * s7 * s9;
	inv[9] = -s0 * s9 * s15 + s0 * s11 * s13 + s8 * s1 * s15 - s8 * s3 * s13 - s12 * s1 * s11 + s12 * s3 * s9;
	inv[10] = s0 * s5 * s15 - s0 * s7 * s13 - s4 * s1 * s15 + s4 * s3 * s13 + s12 * s1 * s7 - s12 * s3 * s5;
	inv[11] = -s0 * s5 * s11 + s0 * s7 * s9 + s4 * s1 * s11 - s4 * s3 * s9 - s8 * s1 * s7 + s8 * s3 * s5;
	inv[12] = -s4 * s9 * s14 + s4 * s10 * s13 + s8 * s5 * s14 - s8 * s6 * s13 - s12 * s5 * s10 + s12 * s6 * s9;
	inv[13] = s0 * s9 * s14 - s0 * s10 * s13 - s8 * s1 * s14 + s8 * s2 * s13 + s12 * s1 * s10 - s12 * s2 * s9;
	inv[14] = -s0 * s5 * s14 + s0 * s6 * s13 + s4 * s1 * s14 - s4 * s2 * s13 - s12 * s1 * s6 + s12 * s2 * s5;
	inv[15] = s0 * s5 * s10 - s0 * s6 * s9 - s4 * s1 * s10 + s4 * s2 * s9 + s8 * s1 * s6 - s8 * s2 * s5;

	float det = s0 * inv[0] + s1 * inv[4] + s2 * inv[8] + s3 * inv[12];
	if (det != 0.0)
		det = 1.0f / det;
	for (int i{ 0 }; i < 16; i++)
		m.data[i] = inv[i] * det;

	return m;
}

constexpr Mat4 Mat4::Identity() noexcept
{
	Mat4	m;

	m.data[0] = 1.f;
	m.data[5] = 1.f;
	m.data[10] = 1.f;
	m.data[15] = 1.f;

	return m;
}

Vec3 Mat4::ToEulerAngles() const noexcept
{
	double	sinThetaY = data[2];
	double	cosThetaY = sqrt(1 - sinThetaY * sinThetaY);
	double	sinThetaX;
	double	cosThetaX;
	double	sinThetaZ;
	double	cosThetaZ;

	if (cosThetaY == 0)
	{
		sinThetaZ = 0;
		cosThetaZ = 1;
		sinThetaX = data[9];
		cosThetaX = data[5];
}
	else
	{
		sinThetaX = -data[6] / cosThetaY;
		cosThetaX = data[10] / cosThetaY;
		sinThetaZ = -data[1] / cosThetaY;
		cosThetaZ = data[0] / cosThetaY;
	}

	return  Vec3{	static_cast<float>(atan2(sinThetaX, cosThetaX) * G_RAD2DEG),
					static_cast<float>(atan2(sinThetaY, cosThetaY) * G_RAD2DEG),
					static_cast<float>(atan2(sinThetaZ, cosThetaZ) * G_RAD2DEG)
	};
}

constexpr Mat4 Mat4::MultipliedBy(const Mat4& _TRS) noexcept
{
	return *this = _TRS * *this;
}

constexpr Mat4 Mat4::CreateOrthogonalMatrix(int _left, int _right, int _bot, int _top, float _near, float _far) noexcept
{
	Mat4 result{ Mat4::Identity() };

	float top{ (float)_top };
	float left{ (float)_left };
	float bot{ (float)_bot };
	float right{ (float)_right };

	result.data2d[0][0] = 2 / (right - left);
	result.data2d[1][1] = 2 / (top - bot);
	result.data2d[2][2] = -2 / (_far - _near);
	result.data2d[3][0] = -((right + left) / (right - left));
	result.data2d[3][1] = -((top + bot) / (top - bot));
	result.data2d[3][2] = -((_far + _near) / (_far - _near));
	
	return result;
}

Mat4  Mat4::CreatePerspectiveMatrix(int _width, int _height, float _near, float _far, float _fov) noexcept
{
	Mat4 result;

	float top = _near * tanf((_fov / 2.f) * G_DEG2RAD);
	float bot = -top;
	float left = top * ((float)_width / (float)_height);	// TODO: ???
	float right = -left;

	result.data2d[0][0] = (-2.f * _near) / (right - left);
	result.data2d[1][1] = (2.f * _near) / (top - bot);
	result.data2d[2][0] = (right + left) / (right - left);
	result.data2d[2][1] = (top + bot) / (top - bot);
	//result.data2d[2][2] = (-far - near) / (far - near);			// TODO: ???
	result.data2d[2][3] = 1.f;										// TODO: ???
	result.data2d[3][2] = (-2.f * _near * _far) / (_far - _near);

	return result;
}

#if USE_SIMD

__m128 Mat4::MultiplySIMDFunc(const __m128& _a, const Mat4& _B) const noexcept
{
	__m128 result =				_mm_mul_ps(_mm_shuffle_ps(_a, _a, 0x00), _B.rows[0]);
	result = _mm_add_ps(result, _mm_mul_ps(_mm_shuffle_ps(_a, _a, 0x55), _B.rows[1]));
	result = _mm_add_ps(result, _mm_mul_ps(_mm_shuffle_ps(_a, _a, 0xaa), _B.rows[2]));
	result = _mm_add_ps(result, _mm_mul_ps(_mm_shuffle_ps(_a, _a, 0xff), _B.rows[3]));
	return result;
}

#endif // USE_SIMD

#pragma endregion

#pragma region Operator

Mat4 Mat4::operator+(const Mat4& _m) const noexcept
{
	Mat4	r;
#if USE_SIMD
	for (int i{ 0 }; i < 4; ++i)
		r.rows[i] = _mm_add_ps(rows[i], _m.rows[i]);
#else
	for (unsigned int i{ 0 }; i < 16; i++)
		r.data[i] = data[i] + _m.data[i];
#endif // USE_SIMD
	return r;
}

Mat4 Mat4::operator-(const Mat4& _m) const noexcept
{
	Mat4	r;
#if USE_SIMD
	for (unsigned int i = 0; i < 4; ++i)
		r.rows[i] = _mm_sub_ps(rows[i], _m.rows[i]);
#else
	for (unsigned int i = 0; i < 16; i++)
		r.data[i] = data[i] - _m.data[i];
#endif // USE_SIMD
	return r;
}

Mat4 Mat4::operator*(const Mat4& _m) const noexcept
{
	Mat4	r;

#if USE_SIMD
	for (int i{ 0 }; i < 4; ++i)
		r.rows[i] = MultiplySIMDFunc(rows[i], _m);
#else
	for (unsigned int i{ 0 }, j{ 0 }; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			r.data2d[i][j] += data2d[i][0] * _m.data2d[0][j];
			r.data2d[i][j] += data2d[i][1] * _m.data2d[1][j];
			r.data2d[i][j] += data2d[i][2] * _m.data2d[2][j];
			r.data2d[i][j] += data2d[i][3] * _m.data2d[3][j];
		}
#endif // USE_SIMD

	return r;
}

Mat4 Mat4::operator*(float _scale) const noexcept
{
	Mat4	m;

#if USE_SIMD
	for (unsigned int i{ 0 }; i < 4; i++)
		m.rows[i] = _mm_mul_ps(rows[i], _mm_set_ps1(_scale));
#else
	for (unsigned int i{ 0 }; i < 16; i++)
		m.data[i] = data[i] * _scale;
#endif

	return m;
}

Vec3 Mat4::operator*(const Vec3& _v) const noexcept
{
	Vec3	r;

	r.x = data[0] * _v.x + data[1] * _v.y + data[2] * _v.z + data[3];
	r.y = data[4] * _v.x + data[5] * _v.y + data[6] * _v.z + data[7];
	r.z = data[8] * _v.x + data[9] * _v.y + data[10] * _v.z + data[11];

	return r;
}

Vec4 Mat4::operator*(const Vec4& _v) const noexcept
{
	Vec4	r;

	r.x = data[0] * _v.x + data[1] * _v.y + data[2] * _v.z + data[3] * _v.w;
	r.y = data[4] * _v.x + data[5] * _v.y + data[6] * _v.z + data[7] * _v.w;
	r.z = data[8] * _v.x + data[9] * _v.y + data[10] * _v.z + data[11] * _v.w;
	r.w = data[12] * _v.x + data[13] * _v.y + data[14] * _v.z + data[15] * _v.w;

	return r;
}

Mat4 Mat4::operator/(float _scale) const noexcept
{
	Mat4	m;

	for (unsigned int i{ 0 }; i < 16; ++i)
		m.data[i] = data[i] / _scale;

	return m;
}

Mat4& Mat4::operator=(const Mat4& _m) noexcept
{
	for (unsigned int i{ 0 }; i < 16; ++i)
		data[i] = _m.data[i];

	return (*this);
}

Mat4& Mat4::operator=(Mat4&& _m) noexcept
{
	for (unsigned int i{ 0 }; i < 16; i++)
		data[i] = std::move(_m.data[i]);

	return (*this);
}

void Mat4::operator+=(const Mat4& _m) noexcept
{
#if USE_SIMD
	for (int i{ 0 }; i < 4; ++i)
		rows[i] = _mm_add_ps(rows[i], _m.rows[i]);
#else
	for (unsigned int i{ 0 }; i < 16; i++)
		data[i] += _m.data[i];
#endif //USE_SIMD
}

void Mat4::operator-=(const Mat4& _m) noexcept
{
#if USE_SIMD
	for (unsigned int i = 0; i < 4; ++i)
		 rows[i] = _mm_sub_ps(rows[i], _m.rows[i]);
#else
	for (unsigned int i = 0; i < 16; i++)
		 data[i] = data[i] - _m.data[i];
#endif // USE_SIMD
}

void Mat4::operator*=(const Mat4& _m) noexcept
{
#if USE_SIMD
	for (int i{ 0 }; i < 4; ++i)
		rows[i] = MultiplySIMDFunc(rows[i], _m);
#else
	for (unsigned int i{ 0 }, j{ 0 }; i < 4; ++i)
		for (j = 0; j < 4; ++j)
		{
			data2d[i][j] += data2d[i][0] * _m.data2d[0][j];
			data2d[i][j] += data2d[i][1] * _m.data2d[1][j];
			data2d[i][j] += data2d[i][2] * _m.data2d[2][j];
			data2d[i][j] += data2d[i][3] * _m.data2d[3][j];
		}
#endif // USE_SIMD
}

void Mat4::operator*=(float _scale) noexcept
{
	for (unsigned int i{ 0 }; i < 16; ++i)
		data[i] *= _scale; 
}

void Mat4::operator/=(float _scale) noexcept
{
	for (unsigned int i{ 0 }; i < 16; ++i)
		data[i] /= _scale; 
}

constexpr bool Mat4::operator==(const Mat4& _m) const noexcept
{
	for (int i{ 0 }; i < 16; i++)
		if (data[i] != _m.data[i])
			return false;
	return true;
}

constexpr Vec4& Mat4::operator[](int _pos) noexcept
{
	return line[_pos];
}

#pragma endregion

#pragma region External Methods

namespace Maths
{
	Vec3 RotationMatrixToEulerAngles(const Mat4& _m) noexcept
	{
		double	sinThetaY = _m.data[2];
		double	cosThetaY = sqrt(1 - sinThetaY * sinThetaY);
		double	sinThetaX;
		double	cosThetaX;
		double	sinThetaZ;
		double	cosThetaZ;

		if (cosThetaY == 0)
		{
			sinThetaZ = 0;
			cosThetaZ = 1;
			sinThetaX = _m.data[9];
			cosThetaX = _m.data[5];
		}
		else
		{
			sinThetaX = -_m.data[6] / cosThetaY;
			cosThetaX = _m.data[10] / cosThetaY;
			sinThetaZ = -_m.data[1] / cosThetaY;
			cosThetaZ = _m.data[0] / cosThetaY;
		}

		return  Vec3{	static_cast<float>(atan2(sinThetaX, cosThetaX) * G_RAD2DEG),
						static_cast<float>(atan2(sinThetaY, cosThetaY) * G_RAD2DEG),
						static_cast<float>(atan2(sinThetaZ, cosThetaZ) * G_RAD2DEG)
		};
	}
}

#pragma endregion

#pragma region External Operator

std::ostream& operator<<(std::ostream& _os, const Mat4& _m) noexcept
{
	_os << "| ";
	for (unsigned int i = 0; i < 16; i++)
	{
		if (i != 0 && i % 4 == 0)
			_os << "\n| ";
		_os << (_m.data[i] < 0.001 && _m.data[i] > -0.001 ? 0.0 : _m.data[i]) << " | ";
	}
	return _os;
}

#pragma endregion