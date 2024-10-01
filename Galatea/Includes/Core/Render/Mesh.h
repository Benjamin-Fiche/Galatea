#pragma once

#include <string>
#include <vector>

#include "DLL.h"

#include "Cereal/types/string.hpp"
#include "Cereal/types/polymorphic.hpp"
#include "ComponentSystem/Component.h"
#include "rttr/registration_friend.h"
#include "../ResourcesManager.h"

namespace Galatea
{
	class Mesh : public Component
	{
		friend class Model;
		friend class Shader;
		friend class Material;
		friend class Renderer;
		friend class cereal::access;

	protected:
		unsigned char				flagCharacteristics;
		unsigned char				flagPostProcess;
		unsigned int				VAO;
		std::string					name;

		const unsigned int*			indices;
		std::vector<unsigned int>	indicesCount;
		std::vector<unsigned int>	indicesIndex;
		std::vector<Material*>		materials;

		Mesh()													noexcept = default;
		Mesh(GameObject* _owner)								noexcept;

		virtual void RenderMesh(const Shader* _shader)	const	noexcept;
	public:
		~Mesh()													noexcept;

		GALATEA_API static Mesh* CreateCube(std::string _texture = "Resources/Textures/MissingTexture.jpg")		noexcept;
		GALATEA_API static Mesh* CreateSphere(std::string _texture = "Resources/Textures/MissingTexture.jpg")	noexcept;

		#if defined(GALATEADLL_EXPORTS) || defined(_DEBUGEXE)

		template<class Archive>
		void save(Archive& _ar) const 
		{
			_ar(isActive, name, flagCharacteristics);
		}

		template<class Archive>
		void load(Archive& _ar)
		{
			_ar(isActive, name, flagCharacteristics);

			std::string s = name.substr(0, name.find(' '));

			if (name.find(' ') == std::string::npos)
				s = ResourcesManager::CreateMeshResource(s.c_str(), nullptr, flagCharacteristics);
			else
				s = ResourcesManager::CreateMeshResource(s.c_str(), name.substr(name.find(' ') + 1).c_str(), flagCharacteristics);

			*this = *ResourcesManager::GetResource<Mesh>(s.c_str());
		}

		inline unsigned int					GetVAO()										const	noexcept { return VAO; }
		inline std::vector<unsigned int>	GetIndicesCount()								const	noexcept { return indicesCount; }
		inline std::vector<unsigned int>	GetIndicesIndex()								const	noexcept { return indicesIndex; }
		#endif

		GALATEA_API void					AddPostProcessEffect(unsigned char _postProcessIndex)	noexcept;
		GALATEA_API void					RemovePostProcessEffect(unsigned char _postProcessIndex)noexcept;
		GALATEA_API unsigned char			GetPostProcessFlag()									noexcept;

		GALATEA_API inline const Material*	GetMaterial(unsigned int i)						const	noexcept { return i < materials.size() ? materials[i] : nullptr; }
		GALATEA_API inline Material*		GetMaterial(unsigned int i)								noexcept { return i < materials.size() ? materials[i] : nullptr; }
		GALATEA_API inline const auto&		GetMaterials()									const	noexcept { return materials; }
		GALATEA_API inline auto&			GetMaterials()											noexcept { return materials; }

		RTTR_ENABLE(Component)
		RTTR_REGISTRATION_FRIEND
	};
}

namespace cereal
{
	template <class Archive>
	struct specialize<Archive, Galatea::Mesh, cereal::specialization::member_load_save> {};
	// cereal no longer has any ambiguity when serializing Mesh
}

CEREAL_REGISTER_TYPE(Galatea::Mesh);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Galatea::Component, Galatea::Mesh)
