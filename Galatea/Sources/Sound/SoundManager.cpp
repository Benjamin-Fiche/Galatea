#include <Libraries/Fmod/fmod.hpp>

#include "Debug/Log.h"

#include "Sound/SoundManager.h"
#include "Sound/FmodTools.h"

using namespace Galatea;

#pragma region Variables

SoundManager* SoundManager::instance{ nullptr };

#pragma endregion

#pragma region Constructors/Destructor

SoundManager::SoundManager() noexcept
	: system{ nullptr }, channelGroups{ new SoundChannelGroup("Master") }
{}

SoundManager::~SoundManager() noexcept
{
	std::vector<SoundChannelGroup*>::iterator	it;
	for (it = channelGroups.begin(); it != channelGroups.end(); ++it)
		if (*it != nullptr)
			delete	*it;
	channelGroups.clear();

	if (system == nullptr)
		return;
	system->close();
	system->release();
}

#pragma endregion

#pragma region Methods

bool SoundManager::Init() noexcept
{
	FMOD::System_Create(&system);
	if (!Fmod_CheckResult(system->init(4093, FMOD_INIT_NORMAL, nullptr)))
		return false;

	system->getMasterChannelGroup(&GetChannelGroup("Master")->channelGroup);

	std::vector<SoundChannelGroup*>::iterator	it;
	for (it = channelGroups.begin(); it != channelGroups.end(); ++it)
		if (!(*it)->Init())
			return false;

	PauseAll(true);

	return true;
}

void SoundManager::AddChannelGroup(SoundChannelGroup* _scg, const char* _name) noexcept
{
	GetChannelGroup(_name)->AddChild(_scg);
}

void SoundManager::Update() noexcept
{
	system->update();
}

void SoundManager::MuteAll(bool _mute) noexcept
{
	std::vector<SoundChannelGroup*>::iterator	it;
	for (it = channelGroups.begin(); it != channelGroups.end(); ++it)
		(*it)->Mute(_mute);
}

void SoundManager::StopAll() noexcept
{
	std::vector<SoundChannelGroup*>::iterator	it;
	for (it = channelGroups.begin(); it != channelGroups.end(); ++it)
		(*it)->Stop();
}

void SoundManager::PauseAll(bool _pause) noexcept
{
	std::vector<SoundChannelGroup*>::iterator	it;
	for (it = channelGroups.begin(); it != channelGroups.end(); ++it)
		(*it)->Pause(_pause);
}

#pragma endregion
