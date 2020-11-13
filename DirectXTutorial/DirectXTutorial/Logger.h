/*************************************************
* Name : Logger.h
* Purpose : Header file for logger module, referred Logger from class
* Date : 2020-11-10
* ************************************************/
#pragma once

#include <fstream> // ofstream
#include <string>
#include <chrono> // time related

class Logger
{
public:
	enum class Severity
	{
		Debug,
		Event,
		Error,
		Verbose
	};
	inline static Logger& GetLogger() noexcept { static Logger instance;  return instance; };
	inline void LogDebug(std::string log) noexcept { Log(Severity::Debug, log); }
	inline void LogEvent(std::string log) noexcept { Log(Severity::Event, log); }
	inline void LogError(std::string log) noexcept { Log(Severity::Error, log); }
	inline void LogVerbose(std::string log) noexcept { Log(Severity::Verbose, log); }
private:
	Logger() noexcept;
	void Log(Severity sev, std::string log) noexcept;
	double GetElapsedTime() noexcept;

	bool isDebug;
	std::ofstream outStream;
	std::chrono::system_clock::time_point startTime;
};