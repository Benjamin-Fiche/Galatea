#pragma once

namespace Galatea
{
	/* TODO: do this class */

	class Time
	{
	private:
		float	previousTime;
		float	currentTime;
		float	previousTimeFixUpdate;
		float	secondTime;
		int		frameCount;
		double	deltaTime;
		double	fixUpdatedeltaTime;

		static Time		instance;

		Time()									noexcept;

		static void		Init()					noexcept;
		static void		Update()				noexcept;
	public:

		static double	GetDeltaTime()			noexcept { return instance.deltaTime; }
		static double	GetTotalTime()			noexcept { return instance.currentTime; }
		static double	GetFixUpdateDeltaTime() noexcept { return instance.fixUpdatedeltaTime; }

		friend class Engine;
	};
}