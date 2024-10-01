#include "Editor/EditorWindow.h"

using namespace Galatea;

#pragma region Contructors/Destructor

EditorWindow::EditorWindow() noexcept
	: name{ "EditorWindow" }, isOpen { true }
{}

EditorWindow::EditorWindow(const char* _name) noexcept
	: name{ _name }, isOpen{ true }
{}

EditorWindow::EditorWindow(const std::string& _name) noexcept
	: name{ _name }, isOpen{ true }
{}

EditorWindow::EditorWindow(std::string&& _name) noexcept
	: name{ std::move(_name) }, isOpen{ true }
{}

#pragma endregion