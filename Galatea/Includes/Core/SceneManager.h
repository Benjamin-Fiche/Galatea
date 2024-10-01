#pragma once

#include "Cereal/types/unordered_map.hpp"
#include "Cereal/types/string.hpp"
#include "Core/Scene.h"

#include "Physic/Physics.h"

namespace Galatea
{
	class SceneManager
	{
	private:
		int															changeSceneID{ -1 };

		unsigned int												currentSceneID{};
		Scene*														currentScene;
		std::unordered_map<std::string, std::shared_ptr<Scene>>		scenesList;
		Physics														physics;

		static SceneManager											instance;

		void						ChangeScene()					noexcept;

		SceneManager()												noexcept;
	protected:
		static void					SetCurrentScene(Scene* _scene)	noexcept;
	public:
		~SceneManager()												noexcept;

		static SceneManager&		GetInstance()					noexcept;
		Physics&					GetPhysics()					noexcept;

		/* 
		Initialize the SceneManager class by creating a new basic scene if there is none loaded else it set the current
		scene to the first in the scene list.
		*/
		void						Init()							noexcept;
		void						Update()						noexcept;
		void						FixedUpdate()					noexcept;
		void						LateUpdate()					noexcept;
		void						Destroy()						noexcept;

		template<class Archive>
		void save(Archive& _ar) const
		{
			_ar(scenesList);

			for (int i = 0; i <= scenesList.size(); i++)
				instance.physics.CreateScene();
		}

		template<class Archive>
		void load(Archive& _ar)
		{
			LogMsg("Load SceneManager");
			physics.Init();

			_ar(scenesList);

			for (int i = 0; i <= scenesList.size(); i++)
				instance.physics.CreateScene();
		}

		friend class Scene;
	};
}
