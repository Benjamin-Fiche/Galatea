#pragma once

namespace Galatea
{
	enum class EInputState : unsigned char
	{
		RELEASED = 0,
		PRESSED,
		UP,
		DOWN,
		UNKNOWN,
	};
}