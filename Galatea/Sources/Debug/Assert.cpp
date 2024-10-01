#include "Debug/Log.h"
#include "Debug/Assert.h"

namespace Galatea
{
	void Assertion(	const bool& _condition,
					const char* _file,
					const unsigned int& _line,
					const char* _function) noexcept
	{
		if (_condition)
			return;

		Log::GetInstance()->Msg(_file, _line, _function, "ERROR: Assert failed", EConsoleColor::RED);
		delete Log::GetInstance();
		abort();
	}

	void Assertion(	const bool& _condition,
					const char* _file,
					const unsigned int& _line,
					const char* _function,
					const std::string& _msg) noexcept
	{
		if (_condition)
			return;

		Log::GetInstance()->Msg(_file, _line, _function, (std::string)"ERROR: Assert failed: " + _msg, EConsoleColor::RED);
		delete Log::GetInstance();
		abort();
	}
}