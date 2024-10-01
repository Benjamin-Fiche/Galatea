#include "Debug/Log.h"

using namespace Galatea;

#pragma region Variables

Log* Log::instance{ nullptr };

#pragma endregion

#pragma region Constructors/Destructors

Log::~Log() noexcept
{
	PrintLogsInFile();
	logs.clear();
}

#pragma endregion

#pragma region Methods

void Log::SaveLog(const std::string& _log) noexcept
{
	/* If there is not enough place to save the log in the string */
	if (logs.size() + _log.size() >= logs.max_size())
	{
		if (!PrintLogsInFile())	/* Try to save logs in a file */
			Msg(__FILENAME__, __LINE__, __FUNCTION__, "ERROR: The logs has been deleted without printing in a file", EConsoleColor::RED);
		logs.clear();	/* Clear the saved logs' string */
	}

	/* Then save the log in the string */
	logs += _log;
}

bool Log::PrintLogsInFile() noexcept
{
	std::ofstream	file{ logsFile, std::ios::out | std::ios::trunc };

	/* Check if the file has been opened */
	if (!file.is_open())
	{
		/*
		If it has not been opened it might be because the directory doesn't exist.
		Then try to open the directory and check if the directory has been created.
		*/
		if (_mkdir(logsDirectory) != 0)
		{
			/* If the directory hasn't been opened then log an error and return false */
			Msg(__FILENAME__, __LINE__, __FUNCTION__, "ERROR: Can't create directory", EConsoleColor::RED, false);
			return false;
		}

		Msg(__FILENAME__, __LINE__, __FUNCTION__, "INFO: Logs Directory created", EConsoleColor::LIGHT_BLUE);

		/* Try to open again the logs' file */
		file.open(logsFile, std::ios::out | std::ios::app);

		/* Check if the file has been opened */
		if (!file.is_open())
		{
			/* If the file has not been opened then log an error and return false */
			Msg(__FILENAME__, __LINE__, __FUNCTION__, "ERROR: Can't open logs file", EConsoleColor::RED, false);
			return false;
		}
	}

	file << "====================================================================================================\n";

	/* Print logs in the file */
	file << logs;

	/* Close the file */
	file.close();

	return true;
}

#pragma endregion