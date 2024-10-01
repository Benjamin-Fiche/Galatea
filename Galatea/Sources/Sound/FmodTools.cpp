#include <Libraries/Fmod/fmod_errors.h>

#include "Sound/FmodTools.h"
#include "Debug/Log.h"

bool Galatea::CheckResult(const char* _file, unsigned int _line, const char* _func, FMOD_RESULT _result) noexcept
{
	if (_result == FMOD_OK)
		return true;

	Log::GetInstance()->Msg(_file, _line, _func, FMOD_ErrorString(_result), EConsoleColor::RED);
	return false;
}