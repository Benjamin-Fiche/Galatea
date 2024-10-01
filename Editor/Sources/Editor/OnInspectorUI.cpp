#include <Maths/Vec2.h>
#include <Maths/Vec3.h>
#include <Maths/Vec4.h>
#include <Maths/Quaternion.h>

#include "Editor/OnInspectorUI.h"
#include "ImGUI/imgui.h"

namespace Galatea::OnInspectorUI
{
	#pragma region Methods

	void DragValue(const char* _name, bool _value) noexcept
	{
		ImGui::Checkbox(_name, &_value);
	}

	void DragValue(const char* _name, bool* _value) noexcept
	{
		ImGui::Checkbox(_name, _value);
	}

	void DragValue(const char* _name, int _value) noexcept
	{
		ImGui::DragInt(_name, &_value);
	}

	void DragValue(const char* _name, int* _value) noexcept
	{
		ImGui::DragInt(_name, _value);
	}

	void DragValue(const char* _name, unsigned int _value) noexcept
	{
		ImGui::DragScalar(_name, ImGuiDataType_U32, &_value, 1);
	}

	void DragValue(const char* _name, unsigned int* _value) noexcept
	{
		ImGui::DragScalar(_name, ImGuiDataType_U32, _value, 1);
	}

	void DragValue(const char* _name, float _value) noexcept
	{
		ImGui::DragFloat(_name, &_value);
	}

	void DragValue(const char* _name, float* _value) noexcept
	{
		ImGui::DragFloat(_name, _value);
	}

	void DragValue(const char* _name, double _value) noexcept
	{
		ImGui::DragScalar(_name, ImGuiDataType_Double, &_value, 0.2f);
	}

	void DragValue(const char* _name, double* _value) noexcept
	{
		ImGui::DragScalar(_name, ImGuiDataType_Double, &_value, 0.2f);
	}

	void DragValue(const char* _name, Vector2 _value) noexcept
	{
		ImGui::DragFloat2(_name, _value.xy);
	}

	void DragValue(const char* _name, Vector2* _value) noexcept
	{
		ImGui::DragFloat2(_name, _value->xy);
	}

	void DragValue(const char* _name, Vector3 _value) noexcept
	{
		ImGui::DragFloat3(_name, _value.xyz);
	}

	void DragValue(const char* _name, Vector3* _value) noexcept
	{
		ImGui::DragFloat3(_name, _value->xyz);
	}

	void DragValue(const char* _name, Vector4 _value) noexcept
	{
		ImGui::DragFloat4(_name, _value.xyzw);
	}

	void DragValue(const char* _name, Vector4* _value) noexcept
	{
		ImGui::DragFloat4(_name, _value->xyzw);
	}

	void DragValue(const char* _name, Quaternion _value) noexcept
	{
		ImGui::DragFloat4(_name, _value.wxyz);
	}

	void DragValue(const char* _name, Quaternion* _value) noexcept
	{
		ImGui::DragFloat4(_name, _value->wxyz);
	}

	void DragColor(const char* _name, Vector3 _color) noexcept
	{
		ImGui::ColorEdit3(_name, _color.rgb);
	}

	void DragColor(const char* _name, Vector3* _color) noexcept
	{
		ImGui::ColorEdit3(_name, _color->rgb);
	}

	void DragColor(const char* _name, Vector4 _color) noexcept
	{
		ImGui::ColorEdit4(_name, _color.rgba);
	}

	void DragColor(const char* _name, Vector4* _color) noexcept
	{
		ImGui::ColorEdit4(_name, _color->rgba);
	}

	void SliderValue(const char* _name, int _value, int _min, int _max) noexcept
	{
		ImGui::SliderInt(_name, &_value, _min, _max);
	}

	void SliderValue(const char* _name, int* _value, int _min, int _max) noexcept
	{
		ImGui::SliderInt(_name, _value, _min, _max);
	}
	
	void SliderValue(const char* _name, unsigned int _value, unsigned int _min, unsigned int _max) noexcept
	{
		ImGui::SliderScalar(_name, ImGuiDataType_U32, &_value, &_min, &_max);
	}

	void SliderValue(const char* _name, unsigned int* _value, unsigned int _min, unsigned int _max) noexcept
	{
		ImGui::SliderScalar(_name, ImGuiDataType_U32, _value, &_min, &_max);
	}

	void SliderValue(const char* _name, float _value, float _min, float _max) noexcept
	{
		ImGui::SliderFloat(_name, &_value, _min, _max);
	}

	void SliderValue(const char* _name, float* _value, float _min, float _max) noexcept
	{
		ImGui::SliderFloat(_name, _value, _min, _max);
	}

	void SliderValue(const char* _name, double _value, double _min, double _max) noexcept
	{
		ImGui::SliderScalar(_name, ImGuiDataType_Double, &_value, &_min, &_max);
	}

	void SliderValue(const char* _name, double* _value, double _min, double _max) noexcept
	{
		ImGui::SliderScalar(_name, ImGuiDataType_Double, &_value, &_min, &_max);
	}

	#pragma endregion
}