#pragma once

#include <iostream>
#if USE_SIMD
#include <xmmintrin.h>
#endif

#include "Vec4.h"
#include "MathsTools.h"

namespace Galatea
{
	struct Mat4
	{
		#pragma region Variables

		static constexpr unsigned int	lines = 4;
		static constexpr unsigned int	columns = 4;

		union
		{
			float								data[16];
			float								data2d[4][4];
			Vec4								line[4];

			#if USE_SIMD
			__m128								rows[4];
			#endif // USE_SIMD
		};

		#pragma endregion

		#pragma region Constructors/Destructors
		/* Base Constructor Initialize a 4x4 matrix */
		inline constexpr				Mat4()																		noexcept;
		/* Copy Constructor from matrix 4x4 */
		inline constexpr				Mat4(const Mat4& _m)														noexcept;
		inline							Mat4(const Vec4& _v1, const Vec4& _v2, const Vec4& _v3, const Vec4& _v4)	noexcept;

		#pragma endregion

		#pragma region Methods
		/* Display the matrix on the console */
		inline void						Display()						const	noexcept;
		/* Return the matrix transposed */
		inline constexpr Mat4			Transposed()					const	noexcept;
		/* Transpose the Matrix */
		inline void						Transpose()								noexcept;
		/* Return the matrix inversed */
		inline Mat4						Inverse()						const	noexcept;

		/*
		Multiply TRS by this
			- _TRS: matrix to multiply by this
			- return TRS * this
		*/
		inline constexpr Mat4			MultipliedBy(const Mat4& _TRS)				noexcept;

		/* return a 4x4 matrix fill with 0 */
		inline static constexpr Mat4	Zero()									noexcept;
		/* return a 4x4 matrix fill with 0 and a diagonal of 1 */
		inline static constexpr Mat4	Identity()								noexcept;

		/*
		Convert a rotation Matrix to an euler angles vector
			- return an euler angle vector
		*/
		inline Vec3						ToEulerAngles()					const	noexcept;

		/*
		Create an orthogonal 4x4 matrix
			- _width: screen's width
			- _height: screen's height
			- _near: if an object is closer than the near's value, it wont be draw
			- _far: if an object is farer than the far's value, it wont be draw
			- return the matrix
		*/
		inline static constexpr Mat4	CreateOrthogonalMatrix(int _left, int _right, int _bot, int _top, float _near, float _far)	noexcept;

		/*
		Create an orthogonal 4x4 matrix
			- _width: screen's width
			- _height: screen's height
			- _near: if an object is closer than the near's value, it wont be draw
			- _far: if an object is farer than the far's value, it wont be draw
			- _fov: the angle of view
			- return the matrix
		*/
		inline static Mat4				CreatePerspectiveMatrix(int _width, int _height, float _near, float _far, float _fov)		noexcept;

		#if USE_SIMD
	private:
		inline __m128	MultiplySIMDFunc(const __m128& _a, const Mat4& _B)	const	noexcept;
	public:
		#endif // USE_SIMD

		#pragma endregion

		#pragma region Operator

		inline Mat4						operator+(const Mat4& _m)		const	noexcept;
		inline Mat4						operator-(const Mat4& _m)		const	noexcept;
		inline Mat4						operator*(const Mat4& _m)		const	noexcept;
		inline Vec3						operator*(const Vec3& _v)		const	noexcept;
		inline Vec4						operator*(const Vec4& _v)		const	noexcept;
		inline Mat4						operator*(float _scale)			const	noexcept;
		inline Mat4						operator/(float _scale)			const	noexcept;
		inline Mat4&					operator=(const Mat4& _m)				noexcept;
		inline Mat4&					operator=(Mat4&& _m)					noexcept;
		inline void						operator+=(const Mat4& _m)				noexcept;
		inline void						operator-=(const Mat4& _m)				noexcept;
		inline void						operator*=(const Mat4& _m)				noexcept;
		inline void						operator*=(float _scale)				noexcept;
		inline void						operator/=(float _scale)				noexcept;
		inline constexpr bool			operator==(const Mat4& _m)		const	noexcept;
		inline constexpr Vec4&			operator[](int _pos)					noexcept;

		#pragma endregion
	};

	#pragma region External Methods

	namespace Maths
	{
		/*
			Convert a rotation Matrix to an euler angles vector
				- _m : the rotation matrix to convert
				- return an euler angle vector
		*/
		inline Vec3	RotationMatrixToEulerAngles(const Mat4& _m) noexcept;
	}

	#pragma endregion

	#pragma region External Operator

	inline std::ostream& operator<<(std::ostream& _os, const Mat4& _m) noexcept;

	#pragma endregion
	
	#include "Mat4.inl"
}