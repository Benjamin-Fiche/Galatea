#pragma once

namespace Galatea
{
	#pragma region Properties

	Log* Log::GetInstance() noexcept
	{
		if (instance == nullptr)
			instance = new Log;
		return instance;
	}

	#pragma endregion

	#pragma region Methods

	void Log::Msg(	const char* _file,
					const unsigned int& _line,
					const char* _function,
					const std::string& _msg,
					const EConsoleColor& _color,
					const bool& _saveLog) noexcept
	{
		/* Create the log string */
		std::string	log{ _file + (std::string)" L"  + std::to_string(_line) + " in function " + _function + ": " + _msg + "\n" };
		
		/* Save the log if it has to */
		if (_saveLog)
			SaveLog(log);

		/* Change console's color, print the log in the console and reset the color to default */
		SetConsoleColor(_color);
		std::cout << log;
		SetConsoleColor(EConsoleColor::DEFAULT);
	}

	template<typename T>
	void Log::Value(const char* _file,
		const unsigned int& _line,
		const char* _function,
		const std::string& _name,
		const T& _variable,
		const EConsoleColor& _color,
		const bool& _saveLog) noexcept
	{
		/* Create the log string */
		std::stringstream	log{};
		log << _file << " L" << _line << " in function " << _function << ": " << _name << " = " << _variable << std::endl;

		/* Save the log if it has to */
		if (_saveLog)
			SaveLog(log.str());

		/* Change console's color, print the log in the console and reset the color to default */
		SetConsoleColor(_color);
		std::cout << log.str();
		SetConsoleColor(EConsoleColor::DEFAULT);
	}

	void Log::SetConsoleColor(const EConsoleColor& _color) noexcept
	{
		HANDLE	handle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(handle, static_cast<int>(_color));
	}

	#pragma endregion
}