#pragma once

#include <vector>

#include "assimp/Importer.hpp"
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/material.h"

#include "Core/Render/Material.h"

namespace Galatea
{
	class Mesh;
	class Model
	{
	private:
		struct Vertex
		{
			float vertex[11];
			Vertex(const aiVector3D& _pos, const aiVector3D& _uv, const aiVector3D& _normal, const aiVector3D& _tangent)
			{
				vertex[0] = _pos.x; vertex[1] = _pos.y;		vertex[2] = _pos.z; vertex[3] = _uv.x;
				vertex[4] = _uv.y;	vertex[5] = _normal.x;	vertex[6] = _normal.y; vertex[7] = _normal.z;
				vertex[8] = _tangent.x;	vertex[9] = _tangent.y;	vertex[10] = _tangent.z;
			}
		};
		struct Face
		{
			unsigned int first;
			unsigned int second;
			unsigned int thrid;

			Face(unsigned int _first, unsigned int _second, unsigned int _thrid)
			{
				first = _first; second = _second; thrid = _thrid;
			}
		};

		unsigned int				flagCharacteristics;
		unsigned int				VAO;
		std::string                 name;

		std::vector<Material*>		materials;
		std::vector<unsigned int>   indicesCount;
		std::vector<unsigned int>   indicesIndex;

		std::vector<Vertex>			vertices;
		std::vector<Face>			indices;

		Model()																								noexcept = default;
		~Model()																							noexcept;
		
		bool	Load(const char* _meshPath, const char* _customTexture = nullptr, unsigned int _flag = 0)	noexcept;
        Mesh*	CreateMeshFromModel()																const	noexcept;

		bool InitFromScene(const aiScene* _scene, const char* _meshPath)									noexcept;
		void InitMesh(unsigned int _index, const aiMesh* _mesh)												noexcept;
		bool InitMaterials(const aiScene* _scene, const char* _meshPath, unsigned int _flag)				noexcept;
	public:

		friend class ResourcesManager;
	};
}