#include <Libraries/Fmod/fmod.hpp>

#include "Debug/Log.h"

#include "Sound/Sound.h"
#include "Sound/FmodTools.h"

using namespace Galatea;

#pragma region Constructors/Destructors

Sound::Sound() noexcept
	:	UpdatableComponent(),
		sound			{ nullptr },
		channel			{ nullptr },
		channelGroup	{ "Master" },
		mode			{ G_SOUND_DEFAULT },
		priority		{ 128 },
		pitch			{ 1 },
		volume			{ 0.5 },
		volumeRamp		{ true },
		muted			{ false },
		pan				{ 0 },
		source			{ "" },
		playOnAwake		{ false }
{}

Sound::Sound(const Sound& _sound) noexcept
	:	UpdatableComponent(_sound.owner),
		sound			{ _sound.sound },
		channel			{ _sound.channel },
		channelGroup	{ _sound.channelGroup },
		mode			{ _sound.mode },
		priority		{ _sound.priority },
		pitch			{ _sound.pitch },
		volume			{ _sound.volume },
		volumeRamp		{ _sound.volumeRamp },
		muted			{ _sound.muted },
		pan				{ _sound.pan },
		source			{ _sound.source },
		playOnAwake		{ _sound.playOnAwake }
{}

Sound::Sound(Sound&& _sound) noexcept
	:	UpdatableComponent(std::move(_sound.owner)),
		sound			{ std::move(_sound.sound) },
		channel			{ std::move(_sound.channel) },
		channelGroup	{ std::move(_sound.channelGroup) },
		mode			{ std::move(_sound.mode) },
		priority		{ std::move(_sound.priority) },
		pitch			{ std::move(_sound.pitch) },
		volume			{ std::move(_sound.volume) },
		volumeRamp		{ std::move(_sound.volumeRamp) },
		muted			{ std::move(_sound.muted) },
		pan				{ std::move(_sound.pan) },
		source			{ std::move(_sound.source) },
		playOnAwake		{ std::move(_sound.playOnAwake) }
{}

Sound::Sound(GameObject* _owner) noexcept
	:	UpdatableComponent(_owner),
		sound			{ nullptr },
		channel			{ nullptr },
		channelGroup	{ "Master" },
		mode			{ G_SOUND_DEFAULT },
		priority		{ 128 },
		pitch			{ 1 },
		volume			{ 0.5 },
		volumeRamp		{ true },
		muted			{ false },
		pan				{ 0 },
		source			{ "" },
		playOnAwake		{ false }
{}

Sound::Sound(const char* _src, const char* _channelGroup, bool _playOnAwake, G_SOUND_MODE _mode) noexcept
	:	UpdatableComponent(),
		sound			{ nullptr },
		channel			{ nullptr },
		channelGroup	{ _channelGroup },
		mode			{ _mode },
		priority		{ 128 },
		pitch			{ 1 },
		volume			{ 0.5 },
		volumeRamp		{ true },
		muted			{ false },
		pan				{ 0 },
		source			{ _src },
		playOnAwake		{ _playOnAwake }
{}

Sound::~Sound() noexcept
{
	Stop();
	sound->release();
}

#pragma endregion

#pragma region Properties

unsigned int Sound::GetPosition(G_SOUND_TIMEUNIT _timeUnit) const noexcept
{
	unsigned int	position;
	Fmod_CheckResult(channel->getPosition(&position, _timeUnit));
	return position;
}

int Sound::GetLoopCount() const noexcept
{
	int	loopCount;
	Fmod_CheckResult(sound->getLoopCount(&loopCount));
	return loopCount;
}

void Sound::GetLoopPoints(	unsigned int& _loopStart, G_SOUND_TIMEUNIT _loopStartType,
							unsigned int& _loopEnd, G_SOUND_TIMEUNIT _loopEndType) const noexcept
{
	Fmod_CheckResult(sound->getLoopPoints(&_loopStart, _loopStartType, &_loopEnd, _loopEndType));
}

bool Sound::GetIsPlaying() const noexcept
{
	bool	isPlaying;
	Fmod_CheckResult(channel->isPlaying(&isPlaying));
	return isPlaying;
}

bool Sound::GetPaused() const noexcept
{
	bool	isPaused;
	Fmod_CheckResult(channel->getPaused(&isPaused));
	return isPaused;
}

float Sound::GetAudibility() const noexcept
{
	float	audibility;
	Fmod_CheckResult(channel->getAudibility(&audibility));
	return audibility;
}

void Sound::Get3DConeSettings(float& _insideConeAngle, float& _outsideConeAngle, float& _outsideVolume) const noexcept
{
	Fmod_CheckResult(sound->get3DConeSettings(&_insideConeAngle, &_outsideConeAngle, &_outsideVolume));
}

void Sound::Get3DCustomRolloff(Vector3** _points, int& _numPoints) const noexcept
{
	FMOD_VECTOR* points{ nullptr };
	
	Fmod_CheckResult(sound->get3DCustomRolloff(&points, &_numPoints));

	for (int i = 0; i < _numPoints; ++i)
		(*_points)[i] = { points[i].x, points[i].y, points[i].z };
}

void Sound::Get3DMinMaxDistance(float& _min, float& _max) const noexcept
{
	Fmod_CheckResult(sound->get3DMinMaxDistance(&_min, &_max));
}

void Sound::SetPriority(int _priority) noexcept
{
	priority = _priority;
	Fmod_CheckResult(channel->setPriority(priority));
}

void Sound::SetPosition(unsigned int _position, G_SOUND_TIMEUNIT _timeUnit) noexcept
{
	Fmod_CheckResult(channel->setPosition(_position, _timeUnit));
}

void Sound::SetChannelGroup(const char* _channelGroup) noexcept
{
	channelGroup = _channelGroup;
	Fmod_CheckResult(channel->setChannelGroup(SoundManager::GetInstance()->GetChannelGroup(channelGroup.c_str())->channelGroup));
}

void Sound::SetLoopCount(int _loopCount) noexcept
{
	Fmod_CheckResult(sound->setLoopCount(_loopCount));
}

void Sound::SetLoopPoints(	unsigned int _loopStart, G_SOUND_TIMEUNIT _loopStartType,
							unsigned int _loopEnd, G_SOUND_TIMEUNIT _loopEndType) noexcept
{
	Fmod_CheckResult(sound->setLoopPoints(_loopStart, _loopStartType, _loopEnd, _loopEndType));
}

void Sound::SetMode(G_SOUND_MODE _mode) noexcept
{
	mode = _mode;
	Fmod_CheckResult(sound->setMode(mode));
}

void Sound::AddMode(G_SOUND_MODE _mode) noexcept
{
	mode |= _mode;
	Fmod_CheckResult(sound->setMode(mode));
}

void Sound::RemoveMode(G_SOUND_MODE _mode) noexcept
{
	mode &= ~_mode;
	Fmod_CheckResult(sound->setMode(mode));
}

void Sound::SetPitch(float _pitch) noexcept
{
	pitch = _pitch;
	Fmod_CheckResult(channel->setPitch(pitch));
}

void Sound::SetVolume(float _volume) noexcept
{
	volume = _volume;
	Fmod_CheckResult(channel->setVolume(volume));
}

void Sound::SetVolumeRamp(bool _volumeRamp) noexcept
{
	volumeRamp = _volumeRamp;
	Fmod_CheckResult(channel->setVolumeRamp(volumeRamp));
}

void Sound::SetPan(float _pan) noexcept
{
	pan = _pan;
	Fmod_CheckResult(channel->setPan(pan));
}

void Sound::Set3DConeSettings(float _insideConeAngle, float _outsideConeAngle, float _outsideVolume) noexcept
{
	Fmod_CheckResult(sound->set3DConeSettings(_insideConeAngle, _outsideConeAngle, _outsideVolume));
}

void Sound::Set3DCustomRolloff(const Vector3* _points, int _numpoints) noexcept
{
	FMOD_VECTOR*	points{ new FMOD_VECTOR[_numpoints] };
	for (int i = 0; i < _numpoints; ++i)
		points[i] = { _points[i].x, _points[i].y, _points[i].z };
	Fmod_CheckResult(sound->set3DCustomRolloff(points, _numpoints));
	if (points != nullptr)
		delete points;
}

void Sound::Set3DMinMaxDistance(float _min, float _max) noexcept
{
	Fmod_CheckResult(sound->set3DMinMaxDistance(_min, _max));
}

#pragma endregion

#pragma region Methods

void Sound::Init() noexcept
{
	Fmod_CheckResult(SoundManager::GetInstance()->system->createSound(source.c_str(), mode, nullptr, &sound));
	Fmod_CheckResult(SoundManager::GetInstance()->system->playSound(sound, SoundManager::GetInstance()->GetChannelGroup(channelGroup.c_str())->channelGroup, !playOnAwake, &channel));
	InitChannel();
}

void Sound::InitChannel() noexcept
{
	if (channel == nullptr)
		return;

	SetPriority(priority);
	SetPitch(pitch);
	SetVolume(volume);
	SetVolumeRamp(volumeRamp);
}

void Sound::Update() noexcept
{
	if (IsModePresent(G_SOUND_3D))
	{
		/* TODO: set cone orientation when Quaternion.ToEulerAngles will work */
		Vector3	worldPosition{ owner->GetWorldPosition() };
		//Vector3	worldRotation{ owner->GetWorldRotation().ToEulerAngles() };
		FMOD_VECTOR	position{ worldPosition.x, worldPosition.y, worldPosition.z };
		//FMOD_VECTOR rotation{ worldRotation.x, worldRotation.y, worldRotation.z };
		channel->set3DAttributes(&position, nullptr);
		//channel->set3DConeOrientation(&rotation);
	}
}

void Sound::Play() noexcept
{
	Stop();
	Fmod_CheckResult(SoundManager::GetInstance()->system->playSound(sound, SoundManager::GetInstance()->GetChannelGroup(channelGroup.c_str())->channelGroup, false, &channel));
	InitChannel();
}

void Sound::Pause(bool _pause) noexcept
{
	Fmod_CheckResult(channel->setPaused(_pause));
}

void Sound::Stop() noexcept
{
	bool	isPlaying;
	channel->isPlaying(&isPlaying);
	
	if (isPlaying)
		Fmod_CheckResult(channel->stop());
}

void Sound::Mute(bool _mute) noexcept
{
	Fmod_CheckResult(channel->setMute(_mute));
}

#pragma endregion

#pragma region Operators

Sound& Sound::operator=(const Sound& _sound) noexcept
{
	sound			= _sound.sound;
	channel			= _sound.channel;
	channelGroup	= _sound.channelGroup;
	mode			= _sound.mode;
	priority		= _sound.priority;
	pitch			= _sound.pitch;
	volume			= _sound.volume;
	volumeRamp		= _sound.volumeRamp;
	muted			= _sound.muted;
	pan				= _sound.pan;
	source			= _sound.source;
	playOnAwake		= _sound.playOnAwake;
	return *this;
}

Sound& Sound::operator=(Sound&& _sound) noexcept
{
	sound			= std::move(_sound.sound);
	channel			= std::move(_sound.channel);
	channelGroup	= std::move(_sound.channelGroup);
	mode			= std::move(_sound.mode);
	priority		= std::move(_sound.priority);
	pitch			= std::move(_sound.pitch);
	volume			= std::move(_sound.volume);
	volumeRamp		= std::move(_sound.volumeRamp);
	muted			= std::move(_sound.muted);
	pan				= std::move(_sound.pan);
	source			= std::move(_sound.source);
	playOnAwake		= std::move(_sound.playOnAwake);
	return *this;
}

#pragma endregion