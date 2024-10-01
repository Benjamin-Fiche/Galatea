#pragma once

#include <string>

#include "DLL.h"

#pragma region Defines

/* Get the file name without the full path */
#ifndef __FILENAME__
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#endif

/*
Check the condition. Log and abort the program if the condition is false
	- _condition: the condition to check
*/
#define Assert(_condition) Assertion(_condition, __FILENAME__, __LINE__, __FUNCTION__)

/*
Check the condition. Log a custom message and abort the program if the condition is false
	- _condition: the condition to check
	- _msg: the message to add to the assertion's log
*/
#define AssertMsg(_condition, _msg) Assertion(_condition, __FILENAME__, __LINE__, __FUNCTION__, _msg)

#pragma endregion

namespace Galatea
{
	/*
	Check the condition. Log and abort the program if the condition is false
		- _condition: the condition to check
		- _file: the assertion origin file
		- _line: the assertion origin line
	*/
	GALATEA_API void	Assertion(	const bool& _condition,
									const char* _file,
									const unsigned int& _line,
									const char* _function)	noexcept;

	/*
	Check the condition. Log a custom message and abort the program if the condition is false
		- _condition: the condition to check
		- _file: the assertion origin file
		- _line: the assertion origin line
		- _msg: the message to add to the assertion's log
	*/
	GALATEA_API void	Assertion(	const bool& _condition,
									const char* _file,
									const unsigned int& _line,
									const char* _function,
									const std::string& _msg)	noexcept;
}