#pragma once

#include <iostream>
#include "Cereal/types/string.hpp"
#include <sstream>

#include "DLL.h"

#include "MathsTools.h"

namespace Galatea
{
    struct GALATEA_API Vec2
    {

		#pragma region Variable
		
		static Vec2 zero;
		static Vec2	right;
		static Vec2	left;
		static Vec2	up;
		static Vec2 down;

		union 
		{
			struct 
			{
				float x, y;
			};
			float   xy[2];
		};
		
		#pragma endregion

		#pragma region Constructor/Destructor
		/* Constuction of Vector from x and y */
		inline constexpr	Vec2(float _x = 0, float _y = 0)		noexcept;
		/* Copy Constuctor of Vector */
		inline constexpr	Vec2(const Vec2& _v)					noexcept;
		/* R-Value Constuctor of Vector */
		inline constexpr	Vec2(Vec2&& _v)							noexcept;

		#pragma endregion
        
		#pragma region Methods

		/*  Used To display the vector into the console. */
		inline void					Display()										const	noexcept;
		/* Return the length of the vector squared (no sqrt operation). */
        inline constexpr float		SquareLength()									const	noexcept;
		/* Return the length of the vector. */
        inline float				Length()										const	noexcept;
		/* Return the Vector Normalized. */
		inline Vec2					Normalized()									const	noexcept;
		/* Normalize the Vector. */
        inline void					Normalize()												noexcept;
		/* Return the Vector Negateed. */
		inline constexpr Vec2		Negated()										const	noexcept;
		/* Normalize the Vector. */ 
        inline constexpr void		Negate()												noexcept;
		/*
		Return the dot product between this Vector and the vector in parameter.
			- Vec2 v : the second vector used to do the dot product
		*/
        inline constexpr float		DotProduct(const Vec2& _v)						const	noexcept;
		/*
		Return the angle between this Vector and the vector in parameter.
			- Vec2 v : the second vector used to calcul the angle
		*/
        inline float				Angle(const Vec2& _v)							const	noexcept;
		/*
		Return the distance between this vector and the one in parameter (both considered as point).
			- this : the first position
			- Vec3 v : The position of the second point
		*/
		inline float				DistanceBetweenPoint(const Vec2& _v)			const	noexcept;
		/*
		Return the distance squared between this vector and the one in parameter (both considered as point).
			- this : the first position
			- Vec3 v : The position of the second point
		*/
		inline float				SquareDistanceBetweenPoint(const Vec2& _v)		const	noexcept;
		
		/* Function used by the cereal librarie to serialize and deserialize */
		template<class Archive>
		void						serialize(Archive& _ar)
		{
			_ar(x, y);
		}

		#pragma endregion

		#pragma region Operator

        inline constexpr Vec2	        operator+(const Vec2& _v)		const	noexcept;
		inline constexpr Vec2	        operator-(const Vec2& _v)		const	noexcept;
		inline constexpr Vec2	        operator*(float _scale)			const	noexcept;
		inline constexpr Vec2	        operator/(float _scale)			const	noexcept;
        inline constexpr Vec2&			operator=(const Vec2& _v)				noexcept;
		inline constexpr void	        operator+=(const Vec2& _v)				noexcept;
		inline constexpr void	        operator-=(const Vec2& _v)				noexcept;
		inline constexpr void	        operator*=(float _scale)				noexcept;
		inline constexpr void	        operator/=(float _scale)				noexcept;
		inline			 bool	        operator==(const Vec2& _v)		const	noexcept;
        inline constexpr float&         operator[](unsigned _index)				noexcept;

		#pragma endregion
    };
	typedef Vec2 Vector2;

	/* Function needed for the unitary test verification */
	inline static std::wstring ToString(const Vec2& v);

	inline std::ostream&		operator<<(std::ostream& _os, const Vec2& _v)	noexcept;

	#include "Vec2.inl"
}