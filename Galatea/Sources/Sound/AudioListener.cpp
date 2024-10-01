#include "Fmod/fmod.hpp"

#include "Sound/AudioListener.h"
#include "Sound/FmodTools.h"
#include "Sound/SoundManager.h"

using namespace Galatea;

#pragma region Constructors/Destructor

AudioListener::AudioListener() noexcept
	: UpdatableComponent()
{}

AudioListener::AudioListener(const AudioListener& _al) noexcept
	: UpdatableComponent(_al.owner)
{}

AudioListener::AudioListener(AudioListener&& _al) noexcept
	: UpdatableComponent(std::move(_al.owner))
{}

AudioListener::~AudioListener() noexcept
{}

#pragma endregion

#pragma region Properties
#pragma endregion

#pragma region Methods

void AudioListener::Update() noexcept
{
	Vector3	position{ owner->GetWorldPosition() },
			forward{ owner->GetWorldRotation() * Vector3::forward },
			up{ owner->GetWorldRotation() * Vector3::up };
	
	FMOD_VECTOR fmodPosition{ position.x, position.y, position.z },
				fmodForward{ forward.x, forward.y, forward.z },
				fmodUp{ up.x, up.y, up.z };

	SoundManager::GetInstance()->system->set3DListenerAttributes(0, &fmodPosition, nullptr, &fmodForward, &fmodUp);
}

#pragma endregion

#pragma region Operators

AudioListener& AudioListener::operator=(const AudioListener& _al) noexcept
{
	UpdatableComponent::operator=(_al);
	return *this;
}

AudioListener& AudioListener::operator=(AudioListener&& _al) noexcept
{
	UpdatableComponent::operator=(std::move(_al));
	return *this;
}


#pragma endregion