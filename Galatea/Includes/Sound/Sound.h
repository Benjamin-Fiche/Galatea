#pragma once

#include "Cereal/types/polymorphic.hpp"
#include "Cereal/types/string.hpp"
#include "rttr/registration.h"

#include "DLL.h"
#include "ComponentSystem/UpdatableComponent.h"
#include "SoundMode.h"
#include "SoundTimeUnit.h"
#include "Maths/Vec3.h"
#include "Sound/SoundManager.h"

namespace FMOD
{
	class Sound;
	class Channel;
}

namespace Galatea
{
	class SoundChannelGroup;

	class GALATEA_API Sound : public UpdatableComponent
	{
	private:
		#pragma region Variables

		FMOD::Sound*	sound;
		FMOD::Channel*	channel;
		std::string		channelGroup;
		G_SOUND_MODE	mode;

		int				priority;
		float			pitch;
		float			volume;
		bool			volumeRamp;
		bool			muted;
		float			pan;

		#pragma endregion

	public:
		#pragma region Variables
		
		std::string	source;
		bool		playOnAwake;
		
		#pragma endregion

		#pragma region Constructors/Destructor

		Sound()											noexcept;
		Sound(const Sound& _sound)						noexcept;
		Sound(Sound&& _sound)							noexcept;
		Sound(GameObject* _owner)						noexcept;
		Sound(	const char* _src,
				const char* _channelGroup = "Master",
				bool _playOnAwake = false,
				G_SOUND_MODE _mode = G_SOUND_DEFAULT)	noexcept;
		~Sound()										noexcept;

		#pragma endregion

		#pragma region Properties

		inline int					GetPriority()											const	noexcept;
		unsigned int				GetPosition(G_SOUND_TIMEUNIT _timeUnit)					const	noexcept;
		inline SoundChannelGroup*	GetChannelGroup()										const	noexcept;
		int							GetLoopCount()											const	noexcept;
		void						GetLoopPoints(	unsigned int& _loopStart,
													G_SOUND_TIMEUNIT _loopStartType,
													unsigned int& _loopEnd,
													G_SOUND_TIMEUNIT _loopEndType)			const	noexcept;
		bool						GetIsPlaying()											const	noexcept;
		bool						GetPaused()												const	noexcept;
		inline G_SOUND_MODE			GetMode()												const	noexcept;
		inline bool					IsModePresent(G_SOUND_MODE _mode)						const	noexcept;
		inline float				GetPitch()												const	noexcept;
		float						GetAudibility()											const	noexcept;
		inline float				GetVolume()												const	noexcept;
		inline bool					GetVolumeRamp()											const	noexcept;
		inline float				GetPan()												const	noexcept;
		inline bool					GetMute()												const	noexcept;
		void						Get3DConeSettings(	float& _insideConeAngle,
														float& _outsideConeAngle,
														float& _outsideVolume)				const	noexcept;
		void						Get3DCustomRolloff(Vector3** _points, int& _numPoints)	const	noexcept;
		void						Get3DMinMaxDistance(float& _min, float& _max)			const	noexcept;

		void						SetPriority(int _priority = 128)								noexcept;
		void						SetPosition(unsigned int _position, G_SOUND_TIMEUNIT _timeUnit)	noexcept;
		void						SetChannelGroup(const char* _channelGroup = "Master")			noexcept;
		void						SetLoopCount(int _loopCount = -1)								noexcept;
		void						SetLoopPoints(	unsigned int __loopStart,
													G_SOUND_TIMEUNIT _loopStartType,
													unsigned int _loopEnd,
													G_SOUND_TIMEUNIT _loopEndType)					noexcept;
		void						SetMode(G_SOUND_MODE _mode = G_SOUND_DEFAULT)					noexcept;
		void						AddMode(G_SOUND_MODE _mode)										noexcept;
		void						RemoveMode(G_SOUND_MODE _mode)									noexcept;
		void						SetPitch(float _pitch = 1.f)									noexcept;
		void						SetVolume(float _volume = 1.f)									noexcept;
		void						SetVolumeRamp(bool _volumeRamp = true)							noexcept;
		void						SetPan(float _pan = 0.f)										noexcept;
		void						Set3DConeSettings(	float _insideConeAngle = 360.f,
														float _outsideConeAngle = 360.f,
														float _outsideVolume = 1)					noexcept;
		void						Set3DCustomRolloff(const Vector3* _points, int _numpoints)		noexcept;
		void						Set3DMinMaxDistance(float _min = 1.f, float _max = 1.f)			noexcept;

		#pragma endregion

		#pragma endregion Methods

		#if defined(GALATEADLL_EXPORTS) || defined(_DEBUGEXE)

		void	Init()						noexcept override;
		void	InitChannel()				noexcept;
		void	Update()					noexcept override;
		
		template<class Archive>
		void	serialize(Archive& _ar)
		{
			_ar(isActive, channelGroup, mode, source, playOnAwake);
		}

		#endif

		void	Play()						noexcept;
		void	Pause(bool _pause = true)	noexcept;
		void	Stop()						noexcept;
		void	Mute(bool _mute = true)		noexcept;

		#pragma endregion

		#pragma region Operators
		
		Sound&	operator=(const Sound& _sound)	noexcept;
		Sound&	operator=(Sound&& _sound)		noexcept;

		#pragma endregion

		friend cereal::access;
		RTTR_ENABLE(UpdatableComponent)
		RTTR_REGISTRATION_FRIEND
	};

	#include "Sound.inl"
}

CEREAL_REGISTER_TYPE(Galatea::Sound);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Galatea::UpdatableComponent, Galatea::Sound)