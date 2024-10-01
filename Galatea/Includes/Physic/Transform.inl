#pragma once

#pragma region Methods

Mat4 Transform::GetMatrix() const noexcept
{
	return TRS::CreateTRSMatrix(position, rotation, scale);
}

Vec3 Transform::GetUpVector() const noexcept
{
	return rotation.ToMatrix() * Vec3::up;
}

Vec3 Transform::GetFrontVector() const noexcept
{
	return rotation.ToMatrix() * Vec3::forward;
}

Vec3 Transform::GetRightVector() const noexcept
{
	return rotation.ToMatrix() * Vec3::right;
}

#pragma endregion

#pragma region External Methods

namespace TRS
{
	Mat4 CreateTranslationMatrix(const Vec3& _translation) noexcept
	{
		Mat4	m{ Mat4::Identity() };

		m.data[3]	= _translation.x;
		m.data[7]	= _translation.y;
		m.data[11]	= _translation.z;

		return m;
	}

	Mat4 CreateXRotationMatrix(float _angle) noexcept
	{
		Mat4	m{ Mat4::Identity() };
		
		_angle *= G_DEG2RAD;

		m.data[5]	= cos(_angle);
		m.data[6]	= -sin(_angle);
		m.data[9]	= sin(_angle);
		m.data[10]	= cos(_angle);

		return m;
	}

	Mat4 CreateYRotationMatrix(float _angle) noexcept
	{
		Mat4	m{ Mat4::Identity() };

		_angle *= G_DEG2RAD;

		m.data[0]	= cos(_angle);
		m.data[2]	= sin(_angle);
		m.data[8]	= -sin(_angle);
		m.data[10]	= cos(_angle);

		return m;
	}

	Mat4 CreateZRotationMatrix(float _angle) noexcept
	{
		Mat4	m{ Mat4::Identity() };

		_angle *= G_DEG2RAD;

		m.data[0]	= cos(_angle);
		m.data[1]	= -sin(_angle);
		m.data[4]	= sin(_angle);
		m.data[5]	= cos(_angle);

		return m;
	}

	Mat4 CreateRotationMatrix(const Vec3& _axis, float _angle) noexcept
	{
		Mat4	m{ Mat4::Identity() };

		_angle *= G_DEG2RAD;

		float	c{ static_cast<float>(cos(_angle)) };
		float	s{ static_cast<float>(sin(_angle)) };
		float	t{ static_cast<float>(1 - cos(_angle)) };

		m.data[0]	= (t * _axis.x * _axis.x) + c;
		m.data[1]	= (t * _axis.x * _axis.y) - (s * _axis.z);
		m.data[2]	= (t * _axis.x * _axis.z) + (s * _axis.y);
		m.data[4]	= (t * _axis.x * _axis.y) + (s * _axis.z);
		m.data[5]	= (t * _axis.y * _axis.y) + c;
		m.data[6]	= (t * _axis.y * _axis.z) - (s * _axis.x);
		m.data[8]	= (t * _axis.x * _axis.z) - (s * _axis.y);
		m.data[9]	= (t * _axis.y * _axis.z) + (s * _axis.x);
		m.data[10]	= (t * _axis.z * _axis.z) + c;

		return m;
	}

	Mat4 CreateFixedAngleEulerRotationMatrix(const Vec3& _angles) noexcept
	{
		return { CreateYRotationMatrix(_angles.y) * CreateXRotationMatrix(_angles.x) * CreateZRotationMatrix(_angles.z) };
	}

	Mat4 CreateScaleMatrix(const Vec3& _scales) noexcept
	{
		Mat4	m{ Mat4::Identity() };

		m.data[0]	= _scales.x;
		m.data[5]	= _scales.y;
		m.data[10]	= _scales.z;

		return m;
	}

	Mat4 CreateTRSMatrix(const Vec3& _translation, const Vec3& _rotation, const Vec3& _scale) noexcept
	{
		return { CreateTranslationMatrix(_translation) * CreateFixedAngleEulerRotationMatrix(_rotation) * CreateScaleMatrix(_scale) };
	}

	Mat4 CreateTRSMatrix(const Vec3& _translation, const Quaternion& _rotation, const Vec3& _scale) noexcept
	{
		return { CreateTranslationMatrix(_translation) * _rotation.ToMatrix() * CreateScaleMatrix(_scale) };
	}
}

#pragma endregion