#pragma once

#include <fstream>
#include "DLL.h"

#include "Cereal/archives/binary.hpp"
#include "Cereal/archives/json.hpp"
#include "Cereal/archives/xml.hpp"
#include "Cereal/types/unordered_map.hpp"
#include "Cereal/types/string.hpp"
#include "Cereal/types/polymorphic.hpp"

#include "ComponentSystem/UpdatableComponent.h"
#include "Core/Camera/Camera.h"
#include "Physic/RigidBody.h"
#include "Core/Render/Mesh.h"
#include "Core/Render/Light.h"
#include "Core/SceneManager.h"
#include "Core/ResourcesManager.h"
#include "Core/Camera/CameraFreeFlyMovement.h"
#include "Core/Render/Text2D.h"
#include "Core/Render/Quad2D.h"
#include "Game/Player.h"
#include "Game/Gun.h"
#include "Game/CameraFPSRotation.h"
#include "Sound/AudioListener.h"
#include "Game/InteractableObject.h"
#include "Game/Door.h"
#include "Game/GameManager.h"
#include "Game/WinTrigger.h"
#include "Game/MenuManager.h"

namespace Galatea
{	
	namespace SerializationManager
	{
		void SaveScene(const SceneManager& _var);
		void LoadScene(SceneManager& _var);
	};
}