#include "Game/GameManager.h"

#include "Sound/SoundManager.h"
#include "Core/Scene.h"

using namespace Galatea;
using namespace GravityGun;

#pragma region Constructors/Destructor

GameManager::GameManager() noexcept
	: backgroundMusic{ nullptr }
{
	SoundManager::GetInstance()->AddChannelGroup(new SoundChannelGroup("Music"));
	SoundManager::GetInstance()->AddChannelGroup(new SoundChannelGroup("FX"));
	SoundManager::GetInstance()->SetMasterVolume(1.f);
	SoundManager::GetInstance()->GetChannelGroup("Music")->SetVolume(0.2f);
	SoundManager::GetInstance()->GetChannelGroup("FX")->SetVolume(1.f);
}

GameManager::~GameManager() noexcept
{}

#pragma endregion

#pragma region Methods

void GameManager::Init() noexcept
{
	backgroundMusic = owner->GetComponent<Sound>();
	backgroundMusic->SetVolume(0.25f);
}

void GameManager::Update() noexcept
{

}

#pragma endregion