#ifdef _DEBUGEXE

// Run on laptop high perf GPU
extern "C"
{
	__declspec(dllexport) int NvOptimusEnablement = 1;
	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

#include "Core/Engine.h"
//#include "Libraries/vld.h"

using namespace Galatea;

int main()
{
	Galatea::Engine engine;

	if (!engine.Init())
		return EXIT_FAILURE;

	engine.MainLoop();

	return EXIT_SUCCESS;
}

#else

// dllmain.cpp : Définit le point d'entrée de l'application DLL.
#define WIN32_LEAN_AND_MEAN             // Exclure les en-têtes Windows rarement utilisés
#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

#endif