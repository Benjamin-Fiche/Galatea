#pragma once

#include <iostream>

#include "DLL.h"

#include "Maths/Vec3.h"
#include "Maths/Quaternion.h"
#include "Maths/MathsTools.h"

namespace Galatea
{
	struct Transform
	{
		#pragma region Variables

		Vec3	position;
		Quat	rotation;
		Vec3	scale;

		Mat4	globalMatrix;

		#pragma endregion
		
		#pragma region Constructors/Destructors

		GALATEA_API Transform()																										noexcept;
		GALATEA_API Transform(const Transform& _trs)																				noexcept;
		GALATEA_API Transform(Transform&& _trs)																						noexcept;
		GALATEA_API Transform(const Vec3& _position, const Quat& _rotation = Quat::identity, const Vec3& _scale = Vec3(1, 1, 1))	noexcept;
		GALATEA_API Transform(Vec3&& _position, Quat&& _rotation, Vec3&& _scale)													noexcept;
		GALATEA_API Transform(const Vec3& _position, const Vec3& _rotation, const Vec3& _scale)										noexcept;
		//GALATEA_API Transform(Vec3&& _position, const Vec3& _rotation, Vec3&& _scale)												noexcept;
		GALATEA_API ~Transform()																									noexcept = default;

		#pragma endregion

		#pragma region Methods

		/* Display the transform in the console */
		GALATEA_API void		Display()					const	noexcept;

		/* Reset the transform's values */
		GALATEA_API void		Reset()								noexcept;

		/*
		Translate the object
			- _translation: the translation vector to apply to the object
		*/
		GALATEA_API Transform&	Translate(const Vec3& _translation)	noexcept;

		/*
		Rotate the object
			- _rotation: the rotation quaternion to apply to the object
		*/
		GALATEA_API Transform&	Rotate(const Quat& _rotation)		noexcept;

		/*
		Rotate the object
			- _rotation: the rotation vector to apply to the object
		*/
		GALATEA_API Transform&	Rotate(const Vec3& _rotation)		noexcept;

		/*
		Scale the object
			- _scale: the scale vector to apply to the object
		*/
		GALATEA_API Transform&	Scale(const Vec3& _scale)			noexcept;

		/*
		Calculate the transform matrix and return it
			- return the transform matrix
		*/
		GALATEA_API inline Mat4	GetMatrix()					const	noexcept;

		/*
		Calculate the Vector up of the transform and return it
			- return the up vector.
		*/
		GALATEA_API inline Vec3 GetUpVector()				const	noexcept;
		/*
		Calculate the Vector front of the transform and return it
			- return the Front vector.
		*/
		GALATEA_API inline Vec3 GetFrontVector()			const	noexcept;
		/*
		Calculate the Vector Right of the transform and return it
			- return the Right vector.
		*/
		GALATEA_API inline Vec3 GetRightVector()			const	noexcept;

		#if defined(GALATEADLL_EXPORTS) || defined(_DEBUGEXE)
		/* Function used by the cereal librarie to serialize and deserialize */
		template<class Archive>
		void serialize(Archive& _ar)
		{
			_ar(position, rotation, scale);
		}
		#endif

		#pragma endregion
		
		#pragma region Operators

		GALATEA_API Transform&	operator=(const Transform& _trs)	noexcept;
		GALATEA_API Transform&	operator=(Transform&& _trs)			noexcept;

		#pragma endregion
	};

	#pragma region External Methods

	namespace TRS
	{
		/*
		Create a translation matrix
			- _translation: the translation's vector
			- return the matrix
		*/
		inline Mat4	CreateTranslationMatrix(const Vec3& _translation)											noexcept;

		/*
		Create a rotation matrix around the X axis
			- _angle: the rotation angle
			- return the matrix
		*/
		inline Mat4	CreateXRotationMatrix(float _angle)															noexcept;

		/*
		Create a rotation matrix around the Y axis
			- _angle: the rotation angle
			- return the matrix
		*/
		inline Mat4	CreateYRotationMatrix(float _angle)															noexcept;

		/*
		Create a rotation matrix around the Z axis
			- _angle: the rotation angle
			- return the matrix
		*/
		inline Mat4	CreateZRotationMatrix(float _angle)															noexcept;

		/*
		Create a rotation matrix around an axis
			- _axis: the rotation axis
			- _angle: the rotation angle
			- return the matrix
		*/
		inline Mat4	CreateRotationMatrix(const Vec3& _axis, float _angle)										noexcept;

		/*
		Create a fixed euler angle rotation matrix
			- _angles: the rotations angles for each axis
			- return the matrix
		*/
		inline Mat4 CreateFixedAngleEulerRotationMatrix(const Vec3& _angles)									noexcept;

		/*
		Create a scale matrix
			- _scales: the scale vector
			- return the matrix
		*/
		inline Mat4 CreateScaleMatrix(const Vec3& _scales)														noexcept;

		/*
		Create a TRS matrix
			- _translation: the translation vector
			- _rotations: the rotation vector
			- _scales: the scale vector
			- return the matrix
		*/
		inline Mat4 CreateTRSMatrix(const Vec3& _translation, const Vec3& _rotation, const Vec3& _scale)		noexcept;
		
		/*
		Create a TRS matrix
			- _translation: the translation vector
			- _rotations: the rotation quaternion
			- _scales: the scale vector
			- return the matrix
		*/
		inline Mat4 CreateTRSMatrix(const Vec3& _translation, const Quaternion& _rotation, const Vec3& _scale)	noexcept;
	}

	#pragma endregion

	#pragma region External Operators

	/*
	Print the transform values in an ostream
		- _os: the ostream to print in
		- _trs: the transform to print
		- return the ostream
	*/
	std::ostream&	operator<<(std::ostream& _os, const Transform& _trs)	noexcept;

	#pragma endregion

	#include "Transform.inl"
}