#include "Core/SerializationManager.h"

#include "Debug/Log.h"

using namespace Galatea;

void SerializationManager::SaveScene(const SceneManager& _var)
{
	std::ofstream ofs("Scene.Galatea");
	cereal::JSONOutputArchive archive(ofs);

	archive(_var);
}

void SerializationManager::LoadScene(SceneManager& _var)
{
	std::ifstream ifs("Scene.Galatea");
	if (ifs.is_open())
	{
		cereal::JSONInputArchive archive(ifs);
		archive(_var);
	}
	else
		LogError("Can't find Scene.Galatea");
}