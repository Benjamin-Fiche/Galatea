#include <iostream>

#include "Debug/Log.h"
#include "Debug/Assert.h"

int main()
{
	using namespace Galatea;

	for (char i = 0; i < 16; i++)
	{
		//LogValue(static_cast<int>(i));
		Log::SetConsoleColor((EConsoleColor)i);
		std::cout << "coucou\n";
	}

	const char* coucou { "Bonjour je m'appelle Adrien" };
	int	value{ 11 };
	
	LogValue(value);
	LogMsg("ceci est un message");
	LogWarning("attention c'est risque");
	LogError("ca marche pas ton truc");
	LogValue(coucou);

	LogColoredMsg("Je suis un message colore", EConsoleColor::FUCHSIA);
	LogColoredValue(coucou, EConsoleColor::LIGHT_GREEN);

	Assert(true);
	AssertMsg(false, "Euh ton truc ca marche pas trop");

	delete Log::GetInstance();
}