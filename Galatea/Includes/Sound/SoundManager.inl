#pragma once

#pragma region Properties

SoundManager* SoundManager::GetInstance() noexcept
{
	if (instance == nullptr)
		instance = new SoundManager();
	return instance;
}

const SoundChannelGroup* SoundManager::GetChannelGroup(const char* _name) const noexcept
{
	std::vector<SoundChannelGroup*>::const_iterator	it;
	for (it = channelGroups.begin(); it != channelGroups.end(); ++it)
		if ((*it)->name == _name)
			return *it;
	return nullptr;
}

SoundChannelGroup* SoundManager::GetChannelGroup(const char* _name) noexcept
{
	std::vector<SoundChannelGroup*>::iterator	it;
	for (it = channelGroups.begin(); it != channelGroups.end(); ++it)
		if ((*it)->name == _name)
			return *it;
	return nullptr;
}

float SoundManager::GetMasterVolume() const noexcept
{
	return GetChannelGroup("Master")->GetVolume();
}

void SoundManager::SetMasterVolume(float _volume) noexcept
{
	GetChannelGroup("Master")->SetVolume(_volume);
}

#pragma endregion