#pragma once

#include <string>
#include <iostream>
#include <Windows.h>	/* SetConsoleAttribute func */
#ifdef near
#undef near
#endif
#ifdef far
#undef far
#endif
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif
#include <fstream>		/* Write and read in a file */
#include <direct.h>		/* _mkdir func */
#include <sstream>

#include "DLL.h"
#include "EConsoleColor.h"

#pragma region Defines

/* Get the file name without the full path */
#ifndef __FILENAME__
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#endif

/*
Allow you to get the name of a value
	- _value: the value you want to get the name
	- return the name of the value
*/
#define Name(_variable) #_variable

/*
Print a message in the console
	- _msg: the message you want to print in the console
*/
#define LogMsg(_msg) Log::GetInstance()->Msg(__FILENAME__, __LINE__, __FUNCTION__, _msg)

/*
Print a warning in the console
	- _warning: the warning you want to print in the console
*/
#define LogWarning(_warning) Log::GetInstance()->Msg(__FILENAME__, __LINE__, __FUNCTION__, (std::string)"WARNING: " + _warning, EConsoleColor::GOLD)

/*
Print an error in the console
	- _error: the error you want to print in the console
*/
#define LogError(_error) Log::GetInstance()->Msg(__FILENAME__, __LINE__, __FUNCTION__, (std::string)"ERROR: " + _error, EConsoleColor::RED)

/*
Print a variable in the console
	- _variable: the variable you want to display in the console
*/
#define LogValue(_value) Log::GetInstance()->Value(__FILENAME__, __LINE__, __FUNCTION__, Name(_value), _value)

/*
Print a message in the console with the selected color
	- _msg: the message you want to print in the console
	- _color: the selected color you want to use to print
*/
#define LogColoredMsg(_msg, _color) Log::GetInstance()->Msg(__FILENAME__, __LINE__, __FUNCTION__, _msg, _color)

/*
Print a value in the console with the selected color
	- _msg: the value you want to print in the console
	- _color: the selected color you want to use to prints
*/
#define LogColoredValue(_value, _color) Log::GetInstance()->Value(__FILENAME__, __LINE__, __FUNCTION__, Name(_value), _value, _color)

#pragma endregion

namespace Galatea
{
	class GALATEA_API Log
	{
	private:
		#pragma region Variables
	
		/* Singleton's instance */
		static Log* instance;
	
		/* Stocks the logs to print them in a file at the end of the program */
		std::string	logs;

		/* Path for the save of the logs in a file */
		const char* logsDirectory{ "Logs" };
		const char* logsFile{ "Logs/Logs.txt" };
	
		#pragma endregion
	
		#pragma region Constructors/Destructors
	
		Log()	noexcept = default;
	
		#pragma endregion

		#pragma region Methods

		/*
		Save the log in order to print it in a file later
			- _log: the log to save
		*/
		void	SaveLog(const std::string& _log)	noexcept;

		/*
		Print logs in a file to keep a save of them
			- return true if it has been able to write the logs in the file then return false
		*/
		bool	PrintLogsInFile()					noexcept;

		#pragma endregion
	
	public:
		#pragma region Constructors/Destructors
	
		~Log()	noexcept;
	
		#pragma endregion
	
		#pragma region Properties
	
		/*
		Returns the instance of the singleton.
		If it is the first call of the function, then allocate the instance
			- return a pointer to the singleton
		*/
		inline static Log* GetInstance()	noexcept;
	
		#pragma endregion
	
		#pragma region Methods

		/*
		Print a message in the console and save it to print it in a file later
			- _file: the log origin file name
			- _line: the log origin line
			- _msg: the message you want to display in the console
			- _color: the color you want to use
		*/
		inline void			Msg(const char* _file,
								const unsigned int& _line,
								const char* _function,
								const std::string& _msg,
								const EConsoleColor& _color = EConsoleColor::DEFAULT,
								const bool& _saveLog = true)				noexcept;

		/*
		Print a variable in the consoleand save it to print it in a file later
			- _file: the log origin file name
			- _line: the log origin line
			- _variable: the variable you want to display in the console
			- _color: the color you want to use
		*/
		template<typename T>
		inline void			Value(	const char* _file,
									const unsigned int& _line,
									const char* _function,
									const std::string& _name,
									const T& _variable,
									const EConsoleColor& _color = EConsoleColor::DEFAULT,
									const bool& _saveLog = true)			noexcept;

		/*
		Change the writing color of the console
			- _color: the color you want to use to write in the console
		*/
		inline static void	SetConsoleColor(const EConsoleColor& _color)	noexcept;
	
		#pragma endregion
	};
}

#include "Log.inl"