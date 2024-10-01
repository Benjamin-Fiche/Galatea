#pragma once

#include <string>
#include <vector>

#include "SoundMode.h"

namespace FMOD
{
	class ChannelGroup;
}

namespace Galatea
{
	class SoundManager;
	class Sound;

	class SoundChannelGroup
	{
		friend SoundManager;
		friend Sound;

	private:
		#pragma region Variables

		FMOD::ChannelGroup*				channelGroup;
		SoundChannelGroup*				parent;
		std::vector<SoundChannelGroup*>	children;

		#pragma endregion

	public:
		#pragma region Variables

		std::string	name;

		#pragma endregion

		#pragma region Constructors/Destructors

		SoundChannelGroup()									noexcept;
		SoundChannelGroup(const SoundChannelGroup& _scg)	noexcept;
		SoundChannelGroup(SoundChannelGroup&& _scg)			noexcept;
		SoundChannelGroup(const std::string& _name)			noexcept;
		SoundChannelGroup(std::string&& _name)				noexcept;
		SoundChannelGroup(const char* _name)				noexcept;
		~SoundChannelGroup()								noexcept;

		#pragma endregion

		#pragma region Properties

		inline SoundChannelGroup*	GetChild(const char* _name)			noexcept;
		inline size_t				GetChildCount()				const	noexcept;
		inline SoundChannelGroup*	GetParent()					const	noexcept;
		bool						GetIsPlaying()				const	noexcept;
		bool						GetPaused()					const	noexcept;
		G_SOUND_MODE				GetMode()					const	noexcept;
		float						GetPitch()					const	noexcept;
		float						GetAudibility()				const	noexcept;
		float						GetVolume()					const	noexcept;
		bool						GetVolumeRamp()				const	noexcept;
		bool						GetMute()					const	noexcept;

		inline SoundChannelGroup*	SetParent(SoundChannelGroup* _scg)	noexcept;
		void						SetMode(G_SOUND_MODE _mode)			noexcept;
		void						SetPitch(float _pitch)				noexcept;
		void						SetVolume(float _volume)			noexcept;
		void						SetVolumeRamp(bool _volumeRamp)		noexcept;
		void						SetPan(float _pan)					noexcept;

		#pragma endregion

		#pragma region Methods

		bool	Init()										noexcept;
		void	AddChild(SoundChannelGroup* _scg = nullptr)	noexcept;
		void	Pause(bool _pause = true)					noexcept;
		void	Stop()										noexcept;
		void	Mute(bool _mute = true)						noexcept;

		#pragma endregion

		#pragma region Operators

		SoundChannelGroup& operator=(const SoundChannelGroup& _scg)	noexcept;
		SoundChannelGroup& operator=(SoundChannelGroup&& _scg)		noexcept;

		#pragma endregion
	};

	#include "SoundChannelGroup.inl"
}