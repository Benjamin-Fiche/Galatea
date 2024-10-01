#include "Core/Time.h"

#include "Core/Render/WindowManager.h"

using namespace Galatea;

Time Time::instance;

Time::Time() noexcept
{

}

void Time::Init() noexcept
{
	instance.previousTime = WindowManager::GetInstance().GetTime(), instance.currentTime;	/* TODO: class Time */
	instance.previousTimeFixUpdate = instance.previousTime;
	instance.secondTime = 0.f;
	instance.frameCount = 0;
}

void Time::Update() noexcept
{
	instance.currentTime = WindowManager::GetInstance().GetTime();
	instance.frameCount++;

	instance.deltaTime = (instance.currentTime - instance.previousTime);
	instance.secondTime += instance.deltaTime;
	instance.previousTime = instance.currentTime;
}