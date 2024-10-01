#include <iostream>
//#include "Editor/EditorManager.h"
#include "Editor/Editor.h"

// Run on laptop high perf GPU
extern "C"
{
	__declspec(dllexport) int NvOptimusEnablement = 1;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

int main()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	/*if (Galatea::EditorManager::GetInstance().Init(4.5, "#version 450"))
	{
		Galatea::EditorManager::GetInstance().MainLoop();
	}*/

	//Galatea::Engine	engine;
	//engine.InitInEditor();
	Galatea::Editor	editor;

	if (!editor.Init())
		return EXIT_FAILURE;

	editor.Start();

	return EXIT_SUCCESS;
}
