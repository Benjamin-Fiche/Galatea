#include "Core/Render/Material.h"
#include "Core/ResourcesManager.h"
#include "Core/EModelCharacteristics.h"
#include "Core/Render/Shader.h"
#include "Core/Render/RHI.h"

using namespace Galatea;

Material::Material(Material* _material) noexcept:
    shininess               {_material->shininess},
    opacity                 {_material->opacity},
    transparencyFactor      {_material->transparencyFactor},
    reflectivity            {_material->reflectivity},
    bumpScaling             {_material->bumpScaling},
    ambientColor            {_material->ambientColor},
    diffuseColor            {_material->diffuseColor},
    specularColor           {_material->specularColor},
    emissiveColor           {_material->emissiveColor},
    reflectiveColor         {_material->reflectiveColor},
    transparentColor        {_material->transparentColor},
    ambientTexture          {_material->ambientTexture},
    diffuseTexture          {_material->diffuseTexture},
    specularTexture         {_material->specularTexture},
    emissiveTexture         {_material->emissiveTexture},
    bumpTexture             {_material->bumpTexture},
    materialName            {_material->materialName},
    directory               {_material->directory},
    flag                    {_material->flag}
{

}

Material::Material(const aiMaterial* _material, const std::string& _directory, unsigned int _flag) noexcept
{
    aiString Path;
    std::string fullPath;

    if (_material->GetTexture(aiTextureType_DIFFUSE, 0, &Path) == AI_SUCCESS)
    {
        fullPath = _directory + "/" + Path.data;
        if (!ResourcesManager::CreateTextureResource(fullPath.c_str(), _flag))
            std::cout << "Fail to load texture " << fullPath << "\n";
        diffuseTexture = ResourcesManager::GetResource<Texture>(fullPath.c_str());
        flag |= HAS_DIFFUSE_TEXTURE;
    }
    if (_material->GetTexture(aiTextureType_AMBIENT, 0, &Path) == AI_SUCCESS)
    {
        fullPath = _directory + "/" + Path.data;
        if (!ResourcesManager::CreateTextureResource(fullPath.c_str(), _flag))
            std::cout << "Fail to load texture " << fullPath << "\n";
        ambientTexture = ResourcesManager::GetResource<Texture>(fullPath.c_str());
        flag |= HAS_AMBIENT_TEXTURE;
    }
    if (_material->GetTexture(aiTextureType_SPECULAR, 0, &Path) == AI_SUCCESS)
    {
        fullPath = _directory + "/" + Path.data;
        if (!ResourcesManager::CreateTextureResource(fullPath.c_str(), _flag))
            std::cout << "Fail to load texture " << fullPath << "\n";
        specularTexture = ResourcesManager::GetResource<Texture>(fullPath.c_str());
        flag |= HAS_SPECULAR_TEXTURE;
    }
    if (_material->GetTexture(aiTextureType_EMISSIVE, 0, &Path) == AI_SUCCESS)
    {
        fullPath = _directory + "/" + Path.data;
        if (!ResourcesManager::CreateTextureResource(fullPath.c_str(), _flag))
            std::cout << "Fail to load texture " << fullPath << "\n";
        emissiveTexture = ResourcesManager::GetResource<Texture>(fullPath.c_str());
        flag |= HAS_EMISSIVE_TEXTURE;
    }
    if (_material->GetTexture(aiTextureType_HEIGHT, 0, &Path) == AI_SUCCESS)
    {
        fullPath = _directory + "/" + Path.data;
        if (!ResourcesManager::CreateTextureResource(fullPath.c_str(), _flag))
            std::cout << "Fail to load texture " << fullPath << "\n";
        bumpTexture = ResourcesManager::GetResource<Texture>(fullPath.c_str());
        flag |= HAS_BUMP_TEXTURE;
    }

    FillMaterial(_material);

    directory = _directory;
    aiString* str = new aiString;
    aiGetMaterialString(_material, AI_MATKEY_NAME, str);
    materialName = str->C_Str();
    delete str;

    if ((flag & HAS_DIFFUSE_TEXTURE) == 0)
    {
        diffuseTexture = ResourcesManager::GetResource<Texture>(MISSING_TEXTURE);
        flag |= HAS_DIFFUSE_TEXTURE;
    }
    if ((flag & HAS_BUMP_TEXTURE) == 0)
    {
        bumpTexture = ResourcesManager::GetResource<Texture>(DEFAULT_NORMAL_MAP);
        flag |= HAS_BUMP_TEXTURE;
    }
    if (bumpScaling == 0.f)
        bumpScaling = 1.f;
}

void Material::FillMaterial(const aiMaterial* _material) noexcept
{
    aiGetMaterialFloat(_material, AI_MATKEY_OPACITY, &opacity);
    aiGetMaterialFloat(_material, AI_MATKEY_SHININESS, &shininess);
    aiGetMaterialFloat(_material, AI_MATKEY_REFLECTIVITY, &reflectivity);
    aiGetMaterialFloat(_material, AI_MATKEY_BUMPSCALING, &bumpScaling);
    aiGetMaterialFloat(_material, AI_MATKEY_TRANSPARENCYFACTOR, &transparencyFactor);
    aiGetMaterialFloatArray(_material, AI_MATKEY_COLOR_AMBIENT, ambientColor.rgb, 0);
    aiGetMaterialFloatArray(_material, AI_MATKEY_COLOR_DIFFUSE, diffuseColor.rgb, 0);
    aiGetMaterialFloatArray(_material, AI_MATKEY_COLOR_SPECULAR, specularColor.rgb, 0);
    aiGetMaterialFloatArray(_material, AI_MATKEY_COLOR_EMISSIVE, emissiveColor.rgb, 0);
    aiGetMaterialFloatArray(_material, AI_MATKEY_COLOR_REFLECTIVE, reflectiveColor.rgb, 0);
    aiGetMaterialFloatArray(_material, AI_MATKEY_COLOR_TRANSPARENT, transparentColor.rgb, 0);
}

void Material::BindMaterial(const Shader* _shader) noexcept
{
    if (flag & HAS_NO_TEXTURE)
    {
        RHI::SetActiveTexture(0);
        ResourcesManager::GetResource<Texture>("Resources/Textures/MissingTexture.jpg")->Bind();
        return;
    }
    if (flag & HAS_DIFFUSE_TEXTURE & _shader->GetFlag())
    {
        RHI::SetActiveTexture(0);
        diffuseTexture->Bind();
    }
    if (flag & HAS_AMBIENT_TEXTURE & _shader->GetFlag())
    {
        RHI::SetActiveTexture(1);
        ambientTexture->Bind();
    }
    if (flag & HAS_SPECULAR_TEXTURE & _shader->GetFlag())
    {
        RHI::SetActiveTexture(2);
        specularTexture->Bind();
    }
    if (flag & HAS_EMISSIVE_TEXTURE & _shader->GetFlag())
    {
        RHI::SetActiveTexture(3);
        emissiveTexture->Bind();
    }
    if (flag & HAS_BUMP_TEXTURE & _shader->GetFlag())
    {
        RHI::SetActiveTexture(4);
        bumpTexture->Bind();
    }
    RHI::SetActiveTexture(0);

    _shader->SendFloat("material.shininess", shininess);
    _shader->SendFloat("material.opacity", opacity);
    _shader->SendFloat("material.transparencyFactor", transparencyFactor);
    _shader->SendFloat("material.reflectivity", reflectivity);
    _shader->SendFloat("material.bumpScaling", bumpScaling);
    _shader->SendVec3("material.ambient", ambientColor);
    _shader->SendVec3("material.specular", specularColor);
    _shader->SendVec3("material.diffuse", diffuseColor);
    _shader->SendVec3("material.emissive", emissiveColor);
    _shader->SendVec3("material.reflective", reflectiveColor);
}

Material* Material::GetDefaultMaterial(const char* _texture, unsigned int _flag) noexcept
{
    Material* material = new Material;

    ResourcesManager::CreateTextureResource(_texture, _flag);
    material->diffuseTexture = ResourcesManager::GetResource<Texture>(_texture);
    material->ambientTexture = nullptr;
    material->specularTexture = nullptr;
    material->emissiveTexture = nullptr;
    material->bumpTexture = ResourcesManager::GetResource<Texture>(DEFAULT_NORMAL_MAP);

    material->shininess = 2.2f;
    material->opacity = 1.f;
    material->bumpScaling = 1.f;
    material->transparencyFactor = 0.f;
    material->reflectivity = 0.f;
    material->ambientColor = Vec3{ 0.1f, 0.1f, 0.1f };
    material->diffuseColor = Vec3{ 0.5f, 0.5f, 0.5f };
    material->specularColor = Vec3{ 0.2f, 0.2f, 0.2f };
    material->emissiveColor = Vec3{ 1.f, 1.f, 1.f };
    material->reflectiveColor = Vec3{ 1.f, 1.f, 1.f };
    material->transparentColor = Vec3{ 0.1f, 0.1f, 0.1f };
    
    material->materialName = "DefaultMaterial";
    material->directory = "";

    material->flag |= HAS_DIFFUSE_TEXTURE;
    material->flag |= HAS_BUMP_TEXTURE;

    return material;
}

void Material::SetShininess(float _newValue) noexcept
{
    shininess = _newValue;
}

void Material::SetOpacity(float _newValue) noexcept
{
    opacity = _newValue;
}

void Material::SetTransparencyFactor(float _newValue) noexcept
{
    transparencyFactor = _newValue;
}
void Material::SetReflectivity(float _newValue) noexcept
{
    reflectivity = _newValue;
}

void Material::SetBumpScaling(float _newValue) noexcept
{
    bumpScaling = _newValue;
}

void Material::SetAmbientColor(const Vec3& _newColor) noexcept
{
    ambientColor = _newColor;
}

void Material::SetDiffuseColor(const Vec3& _newColor) noexcept
{
    diffuseColor = _newColor;
}

void Material::SetSpecularColor(const Vec3& _newColor) noexcept
{
    specularColor = _newColor;
}

void Material::SetEmissiveColor(const Vec3& _newColor) noexcept
{
    emissiveColor = _newColor;
}

void Material::SetReflectiveColor(const Vec3& _newColor) noexcept
{
    reflectiveColor = _newColor;
}

void Material::SetTransparentColor(const Vec3& _newColor) noexcept
{
    transparentColor = _newColor;
}

bool Material::SetDiffuseTexture(const char* _texturePath) noexcept
{
    diffuseTexture = ResourcesManager::GetResource<Texture>(_texturePath);

    if (diffuseTexture != nullptr)
    {
        flag |= HAS_SPECULAR_TEXTURE;
        return true;
    }
    flag &= ~HAS_SPECULAR_TEXTURE;
    return false;
}

bool Material::SetAmbientTexture(const char* _texturePath) noexcept
{
    ambientTexture = ResourcesManager::GetResource<Texture>(_texturePath);

    if (ambientTexture != nullptr)
    {
        flag |= HAS_SPECULAR_TEXTURE;
        return true;
    }
    flag &= ~HAS_SPECULAR_TEXTURE;
    return false;
}

bool Material::SetSpecularTexture(const char* _texturePath) noexcept
{
    specularTexture = ResourcesManager::GetResource<Texture>(_texturePath);

    if (specularTexture != nullptr)
    {
        flag |= HAS_SPECULAR_TEXTURE;
        return true;
    }
    flag &= ~HAS_SPECULAR_TEXTURE;
    return false;
}

bool Material::SetEmissiveTexture(const char* _texturePath) noexcept
{
    emissiveTexture = ResourcesManager::GetResource<Texture>(_texturePath);

    if (emissiveTexture != nullptr)
    {
        flag |= HAS_SPECULAR_TEXTURE;
        return true;
    }
    flag &= ~HAS_SPECULAR_TEXTURE;
    return false;
}

bool Material::SetBumpTexture(const char* _texturePath) noexcept
{
    bumpTexture = ResourcesManager::GetResource<Texture>(_texturePath);

    if (bumpTexture != nullptr)
    {
        flag |= HAS_SPECULAR_TEXTURE;
        return true;
    }
    flag &= ~HAS_SPECULAR_TEXTURE;
    return false;
}

float Material::GetShininess() const noexcept
{
    return shininess;
}

float Material::GetOpacity() const noexcept
{
    return opacity;
}

float Material::GetTransparencyFactor() const noexcept
{
    return transparencyFactor;
}

float Material::GetReflectivity() const noexcept
{
    return reflectivity;
}

float Material::GetBumpScaling() const noexcept
{
    return bumpScaling;
}

const Vec3& Material::GetAmbientColor() const noexcept
{
    return ambientColor;
}

const Vec3& Material::GetDiffuseColor() const noexcept
{
    return diffuseColor;
}

const Vec3& Material::GetSpecularColor() const noexcept
{
    return specularColor;
}

const Vec3& Material::GetEmissiveColor() const noexcept
{
    return emissiveColor;
}

const Vec3& Material::GetReflectiveColor() const noexcept
{
    return reflectiveColor;
}

const Vec3& Material::GetTransparentColor() const noexcept
{
    return transparentColor;
}

const Texture* Material::GetDiffuseTexture() const noexcept
{
    return diffuseTexture;
}

const Texture* Material::GetAmbientTexture() const noexcept
{
    return ambientTexture;
}

const Texture* Material::GetSpecularTexture() const noexcept
{
    return specularTexture;
}

const Texture* Material::GetEmissiveTexture() const noexcept
{
    return emissiveTexture;
}

const Texture* Material::GetBumpTexture() const noexcept
{
    return bumpTexture;
}