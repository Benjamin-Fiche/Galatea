#pragma once

#include <vector>

#include "DLL.h"
#include "Sound/SoundChannelGroup.h"

namespace FMOD
{
	class System;
}

namespace Galatea
{
	class Sound;
	class AudioListener;

	class GALATEA_API SoundManager
	{
		friend Sound;
		friend SoundChannelGroup;
		friend AudioListener;

	private:
		#pragma region Variables

		FMOD::System*					system;

		std::vector<SoundChannelGroup*>	channelGroups;

		static SoundManager*			instance;

		#pragma endregion

		#pragma region Constructors/Destructor

		SoundManager()	noexcept;

		#pragma endregion

	public:
		#pragma region Constructors/Destructors

		~SoundManager()	noexcept;

		#pragma endregion

		#pragma region Properties

		static inline SoundManager*		GetInstance()								noexcept;
		inline const SoundChannelGroup*	GetChannelGroup(const char* _name)	const	noexcept;
		inline SoundChannelGroup*		GetChannelGroup(const char* _name)			noexcept;
		inline float					GetMasterVolume()					const	noexcept;

		inline void						SetMasterVolume(float _volume)				noexcept;

		#pragma endregion

		#pragma region Methods

		bool	Init()																								noexcept;
		void	AddChannelGroup(SoundChannelGroup* _scg = new SoundChannelGroup(), const char* _parent = "Master")	noexcept;
		void	Update()																							noexcept;
		void	MuteAll(bool _mute)																					noexcept;
		void	StopAll()																							noexcept;
		void	PauseAll(bool _pause)																				noexcept;

		#pragma endregion
	};

	#include "SoundManager.inl"
}