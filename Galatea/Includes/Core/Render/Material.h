#pragma once

#include "DLL.h"

#include "assimp/material.h"
#include "Core/Render/Texture.h"
#include "Maths/Vec3.h"

namespace Galatea
{
	class Material
	{
	public:
		float			shininess			{};
		float			opacity				{};
		float			transparencyFactor	{};
		float			reflectivity		{};
		float			bumpScaling			{};
											
		Vec3			ambientColor;
		Vec3			diffuseColor;
		Vec3			specularColor;
		Vec3			emissiveColor;
		Vec3			reflectiveColor;
		Vec3			transparentColor;

		Texture*		ambientTexture		{};
		Texture*		diffuseTexture		{};
		Texture*		specularTexture		{};
		Texture*		emissiveTexture		{};
		Texture*		bumpTexture			{};

		std::string		materialName;
		std::string		directory;

		unsigned int	flag				{};
		
	private:
		Material()																																	noexcept = default;
		Material(Material* _material)																												noexcept;

		void				FillMaterial(const aiMaterial* _material)																				noexcept;
	public:
		#if defined(GALATEADLL_EXPORTS) || defined(_DEBUGEXE)

		Material(const aiMaterial* _material, const std::string& directory, unsigned int _flag)														noexcept;

		void						BindMaterial(const class Shader* _shader)																		noexcept;
		static Material*			GetDefaultMaterial(const char* _texture = "Resources/Textures/MissingTexture.jpg", unsigned int _flag = 0u)		noexcept;

		#endif

		unsigned int				GetFlag()																								const	noexcept { return flag; };

		GALATEA_API void			SetShininess(float _newValue)																					noexcept;
		GALATEA_API void			SetOpacity(float _newValue)																						noexcept;
		GALATEA_API void			SetTransparencyFactor(float _newValue)																			noexcept;
		GALATEA_API void			SetReflectivity(float _newValue)																				noexcept;
		GALATEA_API void			SetBumpScaling(float _newValue)																					noexcept;

		GALATEA_API void			SetAmbientColor(const Vec3& _newColor)																			noexcept;
		GALATEA_API void			SetDiffuseColor(const Vec3& _newColor)																			noexcept;
		GALATEA_API void			SetSpecularColor(const Vec3& _newColor)																			noexcept;
		GALATEA_API void			SetEmissiveColor(const Vec3& _newColor)																			noexcept;
		GALATEA_API void			SetReflectiveColor(const Vec3& _newColor)																		noexcept;
		GALATEA_API void			SetTransparentColor(const Vec3& _newColor)																		noexcept;

		GALATEA_API bool			SetDiffuseTexture(const char* _texturePath)																		noexcept;
		GALATEA_API bool			SetAmbientTexture(const char* _texturePath)																		noexcept;
		GALATEA_API bool			SetSpecularTexture(const char* _texturePath)																	noexcept;
		GALATEA_API bool			SetEmissiveTexture(const char* _texturePath)																	noexcept;
		GALATEA_API bool			SetBumpTexture(const char* _texturePath)																		noexcept;

		GALATEA_API float			GetShininess()																							const	noexcept;
		GALATEA_API float			GetOpacity()																							const	noexcept;
		GALATEA_API float			GetTransparencyFactor()																					const	noexcept;
		GALATEA_API float			GetReflectivity()																						const	noexcept;
		GALATEA_API float			GetBumpScaling()																						const	noexcept;
																																			
		GALATEA_API const Vec3&		GetAmbientColor()																						const	noexcept;
		GALATEA_API const Vec3&		GetDiffuseColor()																						const	noexcept;
		GALATEA_API const Vec3&		GetSpecularColor()																						const	noexcept;
		GALATEA_API const Vec3&		GetEmissiveColor()																						const	noexcept;
		GALATEA_API const Vec3&		GetReflectiveColor()																					const	noexcept;
		GALATEA_API const Vec3&		GetTransparentColor()																					const	noexcept;
																																			
		GALATEA_API const Texture*	GetDiffuseTexture()																						const	noexcept;
		GALATEA_API const Texture*	GetAmbientTexture()																						const	noexcept;
		GALATEA_API const Texture*	GetSpecularTexture()																					const	noexcept;
		GALATEA_API const Texture*	GetEmissiveTexture()																					const	noexcept;
		GALATEA_API const Texture*	GetBumpTexture()																						const	noexcept;

		RTTR_REGISTRATION_FRIEND
	};
}