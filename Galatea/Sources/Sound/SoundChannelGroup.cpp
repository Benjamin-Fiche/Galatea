#include <Fmod/fmod.hpp>

#include "Sound/SoundChannelGroup.h"
#include "Sound/SoundManager.h"
#include "Sound/FmodTools.h"

using namespace Galatea;

#pragma region Constructors/Destructor

SoundChannelGroup::SoundChannelGroup() noexcept
	:	channelGroup{ nullptr }, parent{ nullptr },
		children{}, name{ "Channel group" }
{}

SoundChannelGroup::SoundChannelGroup(const SoundChannelGroup& _scg) noexcept
	:	channelGroup{ _scg.channelGroup }, parent{ _scg.parent },
		children{ _scg.children }, name{ _scg.name }
{}

SoundChannelGroup::SoundChannelGroup(SoundChannelGroup&& _scg) noexcept
	:	channelGroup{ std::move(_scg.channelGroup) }, parent{ std::move(_scg.parent) },
		children{ std::move(_scg.children) }, name{ std::move(_scg.name) }
{}

SoundChannelGroup::SoundChannelGroup(const std::string& _name) noexcept
	:	channelGroup{ nullptr }, parent{ nullptr },
		children{}, name{ _name }
{}

SoundChannelGroup::SoundChannelGroup(std::string&& _name) noexcept
	:	channelGroup{ nullptr }, parent{ nullptr },
		children{}, name{ _name }
{}

SoundChannelGroup::SoundChannelGroup(const char* _name) noexcept
	:	channelGroup{ nullptr }, parent{ nullptr },
		children{}, name{ _name }
{}

SoundChannelGroup::~SoundChannelGroup() noexcept
{
	parent = nullptr;
	children.clear();
	Stop();
	channelGroup->release();
}

#pragma endregion

#pragma region Properties

bool SoundChannelGroup::GetIsPlaying() const noexcept
{
	bool	isPlaying;
	Fmod_CheckResult(channelGroup->isPlaying(&isPlaying));
	return isPlaying;
}

bool SoundChannelGroup::GetPaused() const noexcept
{
	bool	isPaused;
	Fmod_CheckResult(channelGroup->getPaused(&isPaused));
	return isPaused;
}

G_SOUND_MODE SoundChannelGroup::GetMode() const noexcept
{
	G_SOUND_MODE	mode;
	Fmod_CheckResult(channelGroup->getMode(&mode));
	return mode;
}

float SoundChannelGroup::GetPitch() const noexcept
{
	float	pitch;
	Fmod_CheckResult(channelGroup->getPitch(&pitch));
	return pitch;
}

float SoundChannelGroup::GetAudibility() const noexcept
{
	float	audibility;
	Fmod_CheckResult(channelGroup->getAudibility(&audibility));
	return audibility;
}

float SoundChannelGroup::GetVolume() const noexcept
{
	float	volume;
	Fmod_CheckResult(channelGroup->getVolume(&volume));
	return volume;
}

bool SoundChannelGroup::GetVolumeRamp() const noexcept
{
	bool	volumeRamp;
	Fmod_CheckResult(channelGroup->getVolumeRamp(&volumeRamp));
	return volumeRamp;
}

bool SoundChannelGroup::GetMute() const noexcept
{
	bool	mute;
	Fmod_CheckResult(channelGroup->getMute(&mute));
	return mute;
}

void SoundChannelGroup::SetMode(G_SOUND_MODE _mode) noexcept
{
	Fmod_CheckResult(channelGroup->setMode(_mode));
}

void SoundChannelGroup::SetPitch(float _pitch) noexcept
{
	Fmod_CheckResult(channelGroup->setPitch(_pitch));
}

void SoundChannelGroup::SetVolume(float _volume) noexcept
{
	Fmod_CheckResult(channelGroup->setVolume(_volume));
}

void SoundChannelGroup::SetVolumeRamp(bool _volumeRamp) noexcept
{
	Fmod_CheckResult(channelGroup->setVolumeRamp(_volumeRamp));
}

void SoundChannelGroup::SetPan(float _pan) noexcept
{
	Fmod_CheckResult(channelGroup->setPan(_pan));
}

#pragma endregion

#pragma region Methods

bool SoundChannelGroup::Init() noexcept
{
	if (channelGroup == nullptr)
		return Fmod_CheckResult(SoundManager::GetInstance()->system->createChannelGroup(name.c_str(), &channelGroup));
	return true;
}

void SoundChannelGroup::AddChild(SoundChannelGroup* _scg) noexcept
{
	SoundManager::GetInstance()->channelGroups.push_back(_scg);
	children.push_back(_scg);
	channelGroup->addGroup(_scg->channelGroup);
	_scg->SetParent(this);
	_scg->Init();
}

void SoundChannelGroup::Pause(bool _pause) noexcept
{
	Fmod_CheckResult(channelGroup->setPaused(_pause));
}

void SoundChannelGroup::Stop() noexcept
{
	Fmod_CheckResult(channelGroup->stop());
}

void SoundChannelGroup::Mute(bool _mute) noexcept
{
	Fmod_CheckResult(channelGroup->setMute(_mute));
}

#pragma region Operators

SoundChannelGroup& SoundChannelGroup::operator=(const SoundChannelGroup& _scg) noexcept
{
	channelGroup	= _scg.channelGroup;
	parent			= _scg.parent;
	children		= _scg.children;
	name			= _scg.name;
	return *this;
}

SoundChannelGroup& SoundChannelGroup::operator=(SoundChannelGroup&& _scg) noexcept
{
	channelGroup	= std::move(_scg.channelGroup);
	parent			= std::move(_scg.parent);
	children		= std::move(_scg.children);
	name			= std::move(_scg.name);
	return *this;
}

#pragma endregion