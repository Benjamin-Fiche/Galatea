#pragma once

#include "DLL.h"

#include "Cereal/types/polymorphic.hpp"
#include "Cereal/types/vector.hpp"

#include "ComponentSystem/ComponentsManager.h"
#include "ComponentSystem/GameObject.h"
#include "Core/Camera/CameraInEditor.h"

#include "Core/Render/Framebuffer.h"
#include "Core/Render/PostProcess/PostProcessPass.h"

#include "Physic/Physics.h"
#include "Maths/Mat4.h"

namespace Galatea
{

	class Scene final
	{
	private:
		#pragma region Variables

		bool							isInit;
		std::shared_ptr<GameObject>		world;
		std::shared_ptr<GameObject>		world2D;
		PostProcessPass					postProcessPass;	///TODO serialization
		ComponentsManager*				componentsManager;
		std::vector<GameObject*>		gameObjectList;
		std::vector<GameObject*>		gameObject2DList;
		Framebuffer*					finalFBO;
		Framebuffer*					sceneFBO;
		Mat4							perspectifProjectionMatrix;
		Mat4							orthogonalProjectionMatrix;
		CameraInEditor					cameraScene;

		#pragma endregion

		#pragma region Constructors/Destructor

		Scene()														noexcept;

		#pragma endregion

	public:
		#pragma region Variables

		std::string	name;

		#pragma endregion

		#pragma region Constructors/Destructors

		GALATEA_API	Scene(const char* _name)						noexcept;
		GALATEA_API	~Scene()										noexcept;

		#pragma endregion

		#if defined(GALATEADLL_EXPORTS) || defined(_DEBUGEXE)

		void	Init()											noexcept;
		void	Update()										noexcept;
		void	FixedUpdate()									noexcept;
		void	LateUpdate()									noexcept;
		void	Resize(int _width, int _height)					noexcept;
		void	ResizeCameraScene(int _width, int _height)		noexcept;

		ComponentsManager*	GetComponentsManager()					noexcept { return componentsManager; };
		ComponentsManager*	GetComponentsManager() const			noexcept { return componentsManager; };

		template<class Archive>
		void save(Archive& _ar) const
		{
			_ar(name, world, world2D);
		}

		template<class Archive>
		void load(Archive& _ar)
		{
			_ar(name, world, world2D);
			SceneManager::instance.physics.CreateScene();
			Init();
		}

		#endif

		const std::string&							GetName()									const	noexcept { return name; }
		const std::vector<GameObject*>&				GetGameObjectList()							const	noexcept { return gameObjectList; };
		std::vector<Light*>&						GetLights()											noexcept { return componentsManager->lightList; }
		Light*										GetLight(unsigned int _index)						noexcept { return _index < componentsManager->lightList.size() ? componentsManager->lightList[_index] : nullptr; }
		GameObject*									GetWorld2D()								const	noexcept { return world2D.get(); };
		GameObject*									GetWorld()									const	noexcept { return world.get(); };
		const Mat4&									GetPerspectiveMatrix()						const	noexcept { return perspectifProjectionMatrix; };
		const Mat4&									GetOrthogonalMatrix()						const	noexcept { return orthogonalProjectionMatrix; };
		CameraInEditor&								GetCameraInEditor()									noexcept { return cameraScene; };
		bool										IsSceneInit()								const	noexcept { return isInit; };
		const PostProcessPass&						GetPostProcessPass()						const	noexcept { return postProcessPass; };
		
		GALATEA_API	void							AddCamera(Camera* _camera)							noexcept;
		/*Return true if success, else return false*/
		GALATEA_API	bool							SetUsedCamera(unsigned int _index)					noexcept;
		GALATEA_API	GameObject*						GetGameObjectByName(std::string _s)					noexcept;
		GALATEA_API	Camera*							GetCamera(unsigned int _index)						noexcept;
		GALATEA_API	unsigned int					GetCameraCount()							const	noexcept;
		GALATEA_API	Camera*							GetCurrentCamera()									noexcept;
		GALATEA_API	const Camera*					GetCurrentCamera()							const	noexcept;
		GALATEA_API const Framebuffer*				GetFinalFramebuffer()						const	noexcept;
		GALATEA_API const Framebuffer*				GetSceneFramebuffer()						const	noexcept;
		//Function used to delete a gameobject from the scene
		GALATEA_API bool							DeleteGameObject(GameObject* _gO)					noexcept;
		//function used by the DeleteGameObject function to go threw the scene's tree
		bool										SearchAndDestruct(GameObject*, GameObject*)			noexcept;
		GALATEA_API static void						ResizeScenes(int _width, int _height)				noexcept;
		GALATEA_API static void						ResizeCameraEditor(int _width, int _height)			noexcept;
		GALATEA_API static void						UpdateCameraInEditor()								noexcept;

		//Statics Function using SceneManager
		GALATEA_API	static Scene*					GetCurrentScene()									noexcept;

		GALATEA_API	static void						AddScene(Scene* newScene)							noexcept;
		GALATEA_API	static void						AddScene(std::shared_ptr<Scene> newScene)			noexcept;
		GALATEA_API	static void						ChangeScene(unsigned int _index)					noexcept;
		GALATEA_API	static void						ChangeScene(const char* _name)						noexcept;

		GALATEA_API	static  Camera*					GetCurrentSceneCamera()								noexcept;
		GALATEA_API	static unsigned int				GetCurrentSceneIndex()								noexcept;
		GALATEA_API	static const std::string& 		GetCurrentSceneName()								noexcept;
		GALATEA_API	static const std::string& 		GetSceneName(unsigned int _index)					noexcept;
		GALATEA_API	static unsigned int				GetSceneIndex(const char* _name)					noexcept;
		GALATEA_API	static unsigned int				GetSceneNumbers()									noexcept;

		friend class SceneManager;
		friend GameObject;
		friend cereal::access;
	};
}
