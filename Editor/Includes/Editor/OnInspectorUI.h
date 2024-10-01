#pragma once

namespace Galatea
{
	struct Vec2;
	struct Vec3;
	struct Vec4;
	struct Quaternion;

	namespace OnInspectorUI
	{
		/* Drag */
		void	DragValue(const char* _name, bool _value)													noexcept;
		void	DragValue(const char* _name, bool* _value)													noexcept;
		void	DragValue(const char* _name, int _value)													noexcept;
		void	DragValue(const char* _name, int* _value)													noexcept;
		void	DragValue(const char* _name, unsigned int _value)											noexcept;
		void	DragValue(const char* _name, unsigned int* _value)											noexcept;
		void	DragValue(const char* _name, float _value)													noexcept;
		void	DragValue(const char* _name, float* _value)													noexcept;
		void	DragValue(const char* _name, double _value)													noexcept;
		void	DragValue(const char* _name, double* _value)												noexcept;
		void	DragValue(const char* _name, Vector2 _value)												noexcept;
		void	DragValue(const char* _name, Vector2* _value)												noexcept;
		void	DragValue(const char* _name, Vector3 _value)												noexcept;
		void	DragValue(const char* _name, Vector3* _value)												noexcept;
		void	DragValue(const char* _name, Vector4 _value)												noexcept;
		void	DragValue(const char* _name, Vector4* _value)												noexcept;
		void	DragValue(const char* _name, Quaternion _value)												noexcept;
		void	DragValue(const char* _name, Quaternion* _value)											noexcept;
		void	DragColor(const char* _name, Vector3 _color)												noexcept;
		void	DragColor(const char* _name, Vector3* _color)												noexcept;
		void	DragColor(const char* _name, Vector4 _color)												noexcept;
		void	DragColor(const char* _name, Vector4* _color)												noexcept;

		/* Slider */
		void	SliderValue(const char* _name, int _value, int _min, int _max)								noexcept;
		void	SliderValue(const char* _name, int* _value, int _min, int _max)								noexcept;
		void	SliderValue(const char* _name, unsigned int _value, unsigned int _min, unsigned int _max)	noexcept;
		void	SliderValue(const char* _name, unsigned int* _value, unsigned int _min, unsigned int _max)	noexcept;
		void	SliderValue(const char* _name, float _value, float _min, float _max)						noexcept;
		void	SliderValue(const char* _name, float* _value, float _min, float _max)						noexcept;
		void	SliderValue(const char* _name, double _value, double _min, double _max)						noexcept;
		void	SliderValue(const char* _name, double* _value, double _min, double _max)					noexcept;
	}
}