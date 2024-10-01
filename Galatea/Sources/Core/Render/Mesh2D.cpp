#include "Core/Render/Mesh2D.h"
#include "Core/Render/WindowManager.h"

using namespace Galatea;

Mesh2D::Mesh2D() noexcept
{
	WindowManager::GetWindowSize(width, height);
}

void Mesh2D::Resize(int _width, int _height) noexcept
{
	if (!useProportion)
		return;

	float wCoef{ 1 * static_cast<float>(width) /  static_cast<float>(_width) };
	float hCoef{ 1 * static_cast<float>(height) / static_cast<float>(_height) };
	width = _width;
	height = _height;

	owner->transform.scale.x *= wCoef;
	owner->transform.scale.y *= hCoef;

	owner->transform.position.x *= wCoef;
	owner->transform.position.y *= hCoef;
}