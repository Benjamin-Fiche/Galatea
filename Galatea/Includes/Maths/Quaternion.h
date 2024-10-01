#pragma once

#include <math.h>

#include "DLL.h"

#include "MathsTools.h"
#include "Mat4.h"

namespace Galatea
{
	struct GALATEA_API Quaternion
	{
		#pragma region Variables

		static Quaternion	zero;
		static Quaternion	identity;

		union
		{
			struct
			{
				float			w;
				union
				{
					struct
					{
						float	x, y, z;
					};
					struct
					{
						Vec2	xy;
						float	z;
					};
					struct
					{
						float	x;
						Vec2	yz;
					};
					Vec3		xyz;
				};
			};
			float				wxyz[4];
			//Vec4				wxyz;
		};

		#pragma endregion

		#pragma region Constructor/Destructor

		/* Construction of a quaternion (1, (0, 0, 0)) */
		inline constexpr				Quaternion()																noexcept;
		/* Copy Constructor of a quaternion */
		inline constexpr				Quaternion(const Quaternion& _q)											noexcept;
		/* Construction of a quaternion from float w and a vector for xyz */
		inline constexpr				Quaternion(float _w, const Vec3& _v)										noexcept;
		/* Construction of a quaternion from float w, x, y and z */
		inline constexpr				Quaternion(float _w, float _x, float _y, float _z)							noexcept;
		/* Construction of a quaternion from a vector in space and the rot angle around that vector in degree */
		inline 							Quaternion(const Vec3& _v, float _teta)										noexcept;
		/* Construction of a quaternion from a Matrix4x4 */
		inline							Quaternion(const Mat4& _m)													noexcept;

		#pragma endregion

		#pragma region Methods

		/*
		Display the quaternion's values in the console
		*/
		inline void						Display()											const	noexcept;
		
		///* Return a quaternion filled with 0 */
		//inline static Quaternion		Zero()														noexcept;

		/* fill the quaternion with 0 */
		inline constexpr void			Reset()														noexcept;
		
		/* Return the length of the quaternion */
		inline float					Length()											const	noexcept;
		
		/* Return the length of the quaternion squared */
		inline constexpr float			SquareLength()										const	noexcept;
		
		/* Return the quaternion Normalized */	
		inline Quaternion				Normalized()										const	noexcept;
		
		/* Normalize the quaternion */
		inline void						Normalize()													noexcept;
		
		/* Return the quaternion Conjugated */
		inline constexpr Quaternion		Conjugated()										const	noexcept;
		
		/* Conjugate the quaternion */
		inline constexpr void			Conjugate()													noexcept;
		
		/* Return the quaternion inversed */
		inline constexpr Quaternion		Inversed()											const	noexcept;
		
		/* Inverse the quaternion */
		inline constexpr void			Inverse()													noexcept;
		
		/* Return the quaternion Negated */
		inline constexpr Quaternion		Negated()											const	noexcept;
		
		/* Negate the quaternion */
		inline constexpr void			Negate()													noexcept;
		
		/* 
		Return a quaternion used to go from this quaternion to the quaternion in parameter
			- _q : the quaternion you optain by mutiplying your quaternion to the returned quaternion
		*/
		inline constexpr Quaternion		Difference(const Quaternion& _q)					const	noexcept;
		
		/*
		Convert your quaternion to a rotation matrix
		*/
		inline Mat4						ToMatrix()											const	noexcept;
		
		/*
		Return the Quaternion Lerped between this Quaternion and the one in parameter with an advancement of t.
			- this : the Quaternion returned when t = 0
			- _q : The Quaternion returned when t = 1
			- _t : advancement of the lerp
		*/
		inline constexpr Quaternion		Lerp(const Quaternion& _q, float _t)				const	noexcept;
		
		/*
		Return the Quaternion Slerped between this Quaternion and the one in parameter with an advancement of t. 
		(Smooth lerp)
			- this : the Quaternion returned when t = 0
			- _q : The Quaternion returned when t = 1
			- _t : advancement of the lerp
		*/
		inline Quaternion				Slerp(const Quaternion& _q, float _t)				const	noexcept;
		
		/*
		Return the Quaternion Nlerped between this Quaternion and the one in parameter with an advancement of t.
		(Normalized Lerp)
			- this : the Quaternion returned when t = 0
			- _q : The Quaternion returned when t = 1
			- _t : advancement of the lerp
		*/
		inline Quaternion				NLerp(const Quaternion& _q, float _t)				const	noexcept;
		
		/*	
		Return the Quaternion Nlerped between this Quaternion and the one in parameter with an advancement of t.
		(Normalized Slerp)
			- this : the Quaternion returned when t = 0
			- _q : The Quaternion returned when t = 1
			- _t : advancement of the lerp
		*/
		inline Quaternion				NSlerp(const Quaternion& _q, float _t)				const	noexcept;

		/*
		Return the rotation quaternion used to go from the first vector in parameter to the 2nd vector
			- _start : the start vector
			- _end : the end vector
		*/
		inline static Quaternion		RotationBetweenVector(const Vec3& _start, const Vec3& _end)	noexcept;
		
		/*
		Create a quaternion from euler Angle.
			- _angles : Euler angle where x = pitch = phi, y = yaw = theta, z = roll = rho
		*/
		inline static Quaternion		FromEulerAngle(const Vec3& _angles)							noexcept;

		/*
		Return the euler angles from this quaternion
			- return the euler angle vector
		*/
		inline Vec3						ToEulerAngles()										const	noexcept;

		template<class Archive>
		void serialize(Archive& _ar)
		{
			_ar(w, x, y, z);
		}

		#pragma endregion

		#pragma region Operator

		inline constexpr Quaternion		operator+(const Quaternion& _q)		const	noexcept;
		inline constexpr void			operator+=(const Quaternion& _q)			noexcept;
		inline constexpr Quaternion		operator-(const Quaternion& _q)		const	noexcept;
		inline constexpr void			operator-=(const Quaternion& _q)			noexcept;
		inline constexpr Quaternion		operator*(const Quaternion& _q)		const	noexcept;
		inline constexpr void			operator*=(const Quaternion& _q)			noexcept;
		inline constexpr Quaternion		operator*(float _s)					const	noexcept;
		inline constexpr void			operator*=(float _s)						noexcept;
		/* Cross product operator */
		inline constexpr float			operator^(const Quaternion& _q)		const	noexcept;
		inline constexpr Quaternion		operator/(float _s)					const	noexcept;
		inline constexpr void			operator/=(float _s)						noexcept;
		inline constexpr Quaternion		operator=(const Quaternion& _q)				noexcept;
		inline constexpr Quaternion		operator=(const Vec3& _v)					noexcept;
		inline			 Quaternion		operator=(const Mat4& _m)					noexcept;
		inline constexpr Vector3		operator*(const Vec3& point)		const	noexcept;
		
		inline constexpr bool			operator==(const Quaternion& _q)	const	noexcept;
		
		//x* qx + y * qy + z * qz + i(x * qw - y * qz + z * qy) + j(x * qz + y * qw - z * qx) + k(-x * qy + y * qx + z * qw)
		#pragma endregion
	};
	typedef Quaternion Quat;

	#pragma region External Methods

	namespace Maths
	{
		/*
		Return a vector of euler angles from a quaternion.
			- _quat : the quaternion to convert
			- return the euler angles vector
		*/
		inline Vec3			QuaternionToEulerAngles(const Quaternion& _quat)	noexcept;

		/*
		Return a rotation quaternion from an euler angles vector
			- _angles : the euler angles vector
			- return the rotation quaternion
		*/
		inline Quaternion	EulerAnglesToQuaternion(const Vec3& _angles)		noexcept;

		/*
		Create a rotation matric from a quaternion
			- _m : the quaternion to convert
			- return the rotation matrix
		*/
		inline Mat4			QuaternionToMatrix(const Quaternion& _q)					noexcept;
	}

	#pragma endregion

	#pragma region External Operators

	inline std::ostream& operator<<(std::ostream& _os, const Quaternion& _q)	noexcept;
	
	#pragma endregion

	#include "Quaternion.inl"
}