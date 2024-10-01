#pragma once

#if USE_SIMD
#include <xmmintrin.h>
#endif

#include "Vec3.h"

namespace Galatea
{
	struct Vec4
	{
		#pragma region Variable

		union 
		{
			struct
			{
				float	x, y, z, w;
			};
			struct
			{
				Vec3	xyz;
				float	w;
			};
			struct
			{
				float r, g, b, a;
			};
			struct
			{
				Vec3	rgb;
				float	a;
			};

			float		rgba[4];
			float		xyzw[4];

			#if USE_SIMD
			__m128  row;
			#endif		
		};
		
		#pragma endregion

		#pragma region Constructor/Destructor

		inline constexpr	Vec4(float _x = 0.f, float _y = 0.f, float _z = 0.f, float _w = 0.f)	noexcept;
		inline constexpr	Vec4(const Vec4& _v)													noexcept;
		inline constexpr	Vec4(Vec4&& _v)															noexcept;
		inline constexpr	Vec4(const Vec3& _v, float _w = 0.f)									noexcept;
		#if USE_SIMD
		inline				Vec4(const __m128& v)													noexcept;
		#endif	
		
		#pragma endregion 

		#pragma region Methods

		/* Display the Vector on console */
        inline void					Display()					const	noexcept;
		/* Homogenise the Vector and then returns it */
		inline constexpr Vec4		Homogenized()				const	noexcept;
		/* Homogenise the Vector */
		inline constexpr void		Homogenize()						noexcept;
		/* Return the length of the vector at square. */
		inline constexpr float		SquareLength()				const	noexcept;
		/* Return the length of the vector. */
		inline float				Length()					const	noexcept;
		/* Return the Vector Normalized. */
		inline Vec4					Normalized()				const	noexcept;
		/* Normalize the Vector. */
		inline void					Normalize()							noexcept;
		/* Return the Vector Negated. */
		inline constexpr Vec4		Negated()					const	noexcept;
		/* Negate the Vector. */
		inline constexpr void		Negate()							noexcept;
		/*
		Return the dot product between this Vector and the Vector in parameter.
			- Vec4 v : the second vector used to do the dot product
		*/
		inline constexpr float		DotProduct(const Vec4& _v)	const	noexcept;
		/*
		Return the Vector Lerped between this vector and the one in parameter with an advancement of t.
			- this : the vector returned when t = 0
			- Vec4 v : The vector returned when t = 1
			- float t : advancement of the lerp
		*/
		inline constexpr Vec4			Lerp(const Vec4& _v, float _t)					const	noexcept;
		/* Function used by the cereal librarie to serialize and deserialize */
		template<class Archive>
		void serialize(Archive& _ar)
		{
			_ar(x, y, z, w);
		}
		#pragma endregion 	


		#pragma region Operator

		inline constexpr Vec4		operator=(const Vec4& _v)										noexcept;
		inline constexpr Vec4		operator+(const Vec4& _v)								const	noexcept;
		inline constexpr Vec4		operator-(const Vec4& _v)								const	noexcept;
		inline constexpr Vec4		operator*(float _scale)									const	noexcept;
		inline constexpr Vec4		operator/(float _scale)									const	noexcept;
		inline constexpr void		operator+=(const Vec4& _v)										noexcept;
		inline constexpr void		operator-=(const Vec4& _v)										noexcept;
		inline constexpr void		operator*=(float _scale)										noexcept;
		inline constexpr void		operator/=(float _scale)										noexcept;
		inline constexpr bool		operator==(const Vec4& _v)								const	noexcept;
		inline constexpr float&		operator[](unsigned _index)										noexcept;
		/* Cast Operator Used to counter mesure the invalid forward definition of Vec4 in Vec3 */
		inline						operator Vec3 ()												noexcept;

		#pragma endregion 
	};
	typedef Vec4 Vector4;

	/* Function needed for the unitary test verification */
	inline static std::wstring ToString(const Vec4& v);

	#pragma region ExternalOperator

	inline Vec4						operator-(const Vec4 _v)											noexcept;//negate vector
	inline std::ostream&			operator<<(std::ostream& _os, const Vec4& _v)						noexcept;

	#pragma endregion

	#include "Vec4.inl"
}