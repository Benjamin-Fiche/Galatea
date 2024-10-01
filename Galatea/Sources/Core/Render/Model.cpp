#include <iostream>

#include "Core/Render/Model.h"
#include "Core/Render/Mesh.h"
#include "Maths/Vec3.h"
#include "Core/Render/RHI.h"
#include "Core/ResourcesManager.h"
#include "Core/EModelCharacteristics.h"

using namespace Galatea;

Model::~Model()
{
    for (int i = 0; i < materials.size(); ++i)
        delete materials[i];
    materials.clear();
}

bool Model::Load(const char* _meshPath, const char* _customTexture, unsigned int _flag) noexcept
{   
    flagCharacteristics = _flag;
    name = _meshPath;
    if (_customTexture != nullptr)
        name = name + " " + _customTexture;
    bool success = false;
    #if _DEBUG
    std::cout << "starting import " << name << "|\n";
    #endif
    Assimp::Importer importer;
    
    const aiScene* scene = importer.ReadFile(_meshPath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);
    
    #if _DEBUG
    std::cout << "end of import of " << _meshPath << "\n";
    #endif

    if (scene) 
    {
        success = InitFromScene(scene, _meshPath);
        if (_customTexture == nullptr)
            success = InitMaterials(scene, _meshPath, _flag);
        else
        {
            materials.push_back(Material::GetDefaultMaterial(_customTexture, _flag));
            unsigned int indicesNum = indicesIndex[indicesIndex.size() - 1];
            indicesIndex.clear();
            indicesIndex.push_back(0);
            indicesIndex.push_back(indicesNum);
        }
    }
    else 
    {
        printf("Error parsing '%s': '%s'\n", _meshPath, importer.GetErrorString());
    }

    return success;
}

bool Model::InitFromScene(const aiScene* _scene, const char* _meshPath) noexcept
{
    indicesIndex.push_back(0);

    for (unsigned int i = 0; i < _scene->mNumMeshes; i++) 
    {
        if (i)
            indicesIndex.push_back(indicesIndex[i - 1] + indicesCount[i - 1]);
        InitMesh(i, _scene->mMeshes[i]);
    }

    VAO = RHI::CreateVAO(RHI::POSITION3D | RHI::UV | RHI::NORMAL | RHI::TANGENT, vertices.data(), vertices.size() * 11 * sizeof(float) , indices.data(), indices.size() * 3 * sizeof(unsigned), true);

    return VAO != 0;
}

void Model::InitMesh(unsigned int _index, const aiMesh* _mesh) noexcept
{
    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
    bool hasNormal = _mesh->HasNormals();
    bool hasTexCord = _mesh->HasTextureCoords(0);

    for (unsigned int i = 0; i < _mesh->mNumVertices; i++) 
    {
        vertices.push_back(Vertex{  _mesh->mVertices[i], 
                                    hasTexCord ? _mesh->mTextureCoords[0][i] : Zero3D, 
                                    hasNormal ? _mesh->mNormals[i] : Zero3D,
                                    _mesh->mTangents[i]});
    }

    unsigned int faceIndex = 0, lastIndex = 0;

    if (_index)
        lastIndex = indices.back().thrid + 1;

    for (; faceIndex < _mesh->mNumFaces; faceIndex++) 
    {
        const aiFace& face = _mesh->mFaces[faceIndex];

        indices.push_back(Face{ face.mIndices[0] + lastIndex, face.mIndices[1] + lastIndex, face.mIndices[2] + lastIndex });
    }
    indicesCount.push_back(faceIndex * 3);
}

bool Model::InitMaterials(const aiScene* _scene, const char* _meshPath, unsigned int _flag) noexcept
{
    std::string directory = _meshPath;
    directory = directory.substr(0, directory.find_last_of('/'));

    bool Ret = true;
    for (unsigned int i = 1; i < _scene->mNumMaterials; i++) 
    {
        const aiMaterial* material = _scene->mMaterials[i];
        materials.push_back(new Material(material, directory, _flag));
    }

    if (materials.size() == 0)
        materials.push_back(Material::GetDefaultMaterial());

    return Ret;
}

Mesh* Model::CreateMeshFromModel() const noexcept
{
    Mesh* mesh = new Mesh;

    mesh->flagCharacteristics = flagCharacteristics;
    mesh->VAO = VAO;
    mesh->name = name;

    for (auto it : materials)
        mesh->materials.push_back(new Material(*it));
    mesh->flagCharacteristics |= HAS_EBO;
    mesh->indices = (const unsigned int*)indices.data();
    mesh->indicesCount = indicesCount;
    mesh->indicesIndex = indicesIndex;

    return mesh;
}