#pragma once

#include <Libraries/Fmod/fmod_common.h>

#ifndef __FILENAME__
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#endif

#define Fmod_CheckResult(_result)	CheckResult(__FILENAME__, __LINE__, __FUNCTION__, _result)

namespace Galatea
{
	bool	CheckResult(const char* _file, unsigned int _line, const char* _func, FMOD_RESULT _result) noexcept;
};