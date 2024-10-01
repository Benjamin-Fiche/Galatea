#pragma once

#include "Editor/EditorWindow.h"

namespace Galatea
{
	class MainWindow : public EditorWindow
	{
	private:
		void Update(const int _windowPosX,
					const int _windowPosY,
					const unsigned int _windowWidth,
					const unsigned int _windowHeight) noexcept override;
	};
}