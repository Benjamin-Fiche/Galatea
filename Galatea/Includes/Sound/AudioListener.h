#pragma once

#include "Cereal/types/polymorphic.hpp"
#include "DLL.h"

#include "ComponentSystem/UpdatableComponent.h"

namespace Galatea
{
	class AudioListener : public UpdatableComponent
	{
	public:
		#pragma region Variables
		#pragma endregion

		#pragma region Constructors/Destructor

		AudioListener()							noexcept;
		AudioListener(const AudioListener& _al)	noexcept;
		AudioListener(AudioListener&& _al)		noexcept;
		~AudioListener()						noexcept;

		#pragma endregion

		#pragma region Properties
		#pragma endregion

		#pragma region Methods

		#if defined(GALATEADLL_EXPORTS) || defined(_DEBUGEXE)
		
		void	Update()	noexcept override;

		template<class Archive>
		void	serialize(Archive& _ar)
		{}

		#endif

		#pragma endregion

		#pragma region Operators

		AudioListener&	operator=(const AudioListener& _al) noexcept;
		AudioListener&	operator=(AudioListener&& _al)		noexcept;

		#pragma endregion
	};
}

CEREAL_REGISTER_TYPE(Galatea::AudioListener);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Galatea::UpdatableComponent, Galatea::AudioListener)