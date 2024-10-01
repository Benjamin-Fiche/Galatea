#pragma once

#pragma region Properties

int Sound::GetPriority() const noexcept
{
	return priority;
}

SoundChannelGroup* Sound::GetChannelGroup() const noexcept
{
	return SoundManager::GetInstance()->GetChannelGroup(channelGroup.c_str());
}

G_SOUND_MODE Sound::GetMode() const noexcept
{
	return mode;
}

bool Sound::IsModePresent(G_SOUND_MODE _mode) const noexcept
{
	return (mode & _mode) == _mode;
}

float Sound::GetPitch() const noexcept
{
	return pitch;
}

float Sound::GetVolume() const noexcept
{
	return volume;
}

bool Sound::GetVolumeRamp() const noexcept
{
	return volumeRamp;
}

float Sound::GetPan() const noexcept
{
	return pan;
}

bool Sound::GetMute() const noexcept
{
	return muted;
}

#pragma endregion