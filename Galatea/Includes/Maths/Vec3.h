#pragma once

#include "DLL.h"

#include "Vec2.h"

namespace Galatea
{
    struct GALATEA_API Vec3
    {
		#pragma region Variables

		static  Vec3 zero;
		static  Vec3 up;
		static  Vec3 down;
		static  Vec3 left;
		static  Vec3 right;
		static  Vec3 forward;
		static  Vec3 backward;
		union
		{
			struct
			{
				float x, y, z;
			};
			struct
			{
				float r, g, b;
			};
			struct
			{
				float phi, theta, rho;
			};
			struct
			{
				float pitch, yaw, roll;
			};/*
			struct
			{
				float heading, bank, attitude;
			};*/
			struct
			{
				Vec2		xy;
				float		z;
			};
			struct
			{
				Vec2		rg;
				float		b;
			};
			struct
			{
				float		x;
				Vec2		yz;
			};
			struct
			{
				float		r;
				Vec2		gb;
			};

			float			xyz[3];
			float			rgb[3];
		};
		#pragma endregion

		#pragma region Constructors/Destructors

		/* Constuction of Vector from x, y and z */
		inline constexpr		Vec3(float _x = 0.f, float _y = 0.f, float _z = 0.f)	noexcept;
		/* Copy Constructor of Vector */
		inline constexpr		Vec3(const Vec3& _v)									noexcept;
		/* Construction of Vector from an R-value */
		inline constexpr		Vec3(Vec3&& _v)											noexcept;
		/* Constuction of Vector between two point a and b */
		inline constexpr		Vec3(const Vec3& _a, const Vec3& _b)					noexcept;
		/* Constuction of Vector from a Vector2D and z */
		inline constexpr		Vec3(const Vec2& _v, float _z = 0.f)					noexcept;
		/* Constuction of Vector from x and a Vector2D */
		inline constexpr		Vec3(float _x, const Vec2& _v)							noexcept;
		/* Copy Constructor from a Vector 4 */
	//	inline					Vec3(const Vec4& _v)									noexcept;
        
		#pragma endregion

		#pragma region Methods

		/*  Used To display the vector into the console. */
		inline void  					Display()										const	noexcept;
		/* Return the length of the vector squared (no sqrt operation). */
        inline constexpr float	        SquareLength()									const	noexcept;
		/* Return the length of the vector. */
		inline float					Length()										const	noexcept;
		/* Return the Vector Normalized. */
		inline Vec3						Normalized()									const	noexcept;
		/* Normalize the Vector. */
		inline void						Normalize()												noexcept;
		/* Return the Vector Negated. */
		inline constexpr Vec3		    Negated()										const	noexcept;
		/* Negate the Vector. */
		inline constexpr void			Negate()												noexcept;
		/* 
		Return the dot product between this Vector and the vector in parameter.
			- Vec3 v : the second vector used to do the dot product
		*/
		inline constexpr float	        DotProduct(const Vec3& _v)						const	noexcept;
		/*
		Return the angle between this Vector and the vector in parameter.
			- Vec3 v : the second vector used to calcul the angle
		*/
		inline float					Angle(const Vec3& _v)							const	noexcept;
		/*
		Return the true/false the the Vector and the one in parameter are collinear.
			- Vec3 v : the second vector used to calcul if they are collinear
		*/
		inline constexpr bool			IsCollinear(const Vec3& _v)						const	noexcept;
		/*
		Return the cross product between this Vector and the vector in parameter.
			- Vec3 v : the second vector used to do the cross product
		*/
		inline constexpr Vec3			CrossProduct(const Vec3& _v)						const	noexcept;
		/*
		Return the Vector Lerped between this vector and the one in parameter with an advancement of t.
			- this : the vector returned when t = 0
			- Vec3 v : The vector returned when t = 1
			- float t : advancement of the lerp
		*/
		inline constexpr Vec3			Lerp(const Vec3& _v, float _t)					const	noexcept;
		/*
		Return the distance between this vector and the one in parameter (both considered as point).
			- this : the first position
			- Vec3 v : The second position
		*/
		inline float					DistanceBetweenPoint(const Vec3& _v)				const	noexcept;
		/*
		Return the distance squared between this vector and the one in parameter (both considered as point).
			- this : the first position
			- Vec3 v : The second position
		*/
		inline constexpr float			SquareDistanceBetweenPoint(const Vec3& _v)		const	noexcept;
		/* Function used by the cereal librarie to serialize and deserialize */
		template<class Archive>
		void serialize(Archive& _ar)
		{
			_ar(x, y, z);
		}

		#pragma endregion

		#pragma region Operator

        inline constexpr Vec3		operator+(const Vec3& _v)						const	noexcept;
        inline constexpr Vec3		operator-(const Vec3& _v)						const	noexcept;
        inline constexpr Vec3		operator*(float _scale)							const	noexcept;
		/* Cross product * operator */
        inline constexpr Vec3		operator*(const Vec3& _v)						const	noexcept;		//cross product
        inline constexpr Vec3		operator/(float _scale)							const	noexcept;
        inline constexpr Vec3&		operator=(const Vec3& _v)								noexcept;
        inline constexpr Vec3&		operator=(Vec3&& _v)									noexcept;
        inline constexpr void		operator+=(const Vec3& _v)								noexcept;
        inline constexpr void		operator-=(const Vec3& _v)								noexcept;
        inline constexpr void		operator*=(float _scale)								noexcept;
        inline constexpr void		operator*=(const Vec3& _v)								noexcept;		//cross product
        inline constexpr void		operator/=(float _scale)								noexcept;
		inline constexpr bool		operator==(const Vec3& _v)						const	noexcept;
		inline constexpr bool		operator==(float _scale)						const	noexcept;
		inline constexpr bool		operator!=(const Vec3& _v)						const	noexcept;
		inline constexpr Vec3		operator-()										const	noexcept;		//negate vector
		inline constexpr float&		operator[](unsigned _index)								noexcept;

		#pragma endregion
    };
	typedef Vec3 Vector3;

	/* Function needed for the unitary test verification */
	inline static std::wstring ToString(const Vec3& v);

	#pragma region External Operator
	
	inline constexpr Vec3				operator*(const float& _f, const Vec3 _v)					noexcept;
	inline std::ostream&				operator<<(std::ostream& _os, const Vec3& _v)				noexcept;
		
	#pragma endregion

	#include "Vec3.inl"	
}