/*************************************************
* Name : Logger.cpp
* Purpose : Source for logger module
* Date : 2020-11-10
* ************************************************/

#include <iostream> // cout, endl
#include "Logger.h"

Logger::Logger() noexcept
	: outStream("Trace.log"), startTime(std::chrono::system_clock::now())
{
#ifdef _DEBUG
	isDebug = true;
#else
	isDebug = false;
#endif
}

void Logger::Log(Logger::Severity sev, std::string log) noexcept
{
	std::string logMessage = "";
	logMessage = '[' + std::to_string(GetElapsedTime()) + "]\t";

	switch (sev)
	{
	case Severity::Debug:
		logMessage += "Debug\t";
		break;
	case Severity::Event:
		logMessage += "Event\t";
		break;
	case Severity::Error:
		logMessage += "Error\t";
		break;
	case Severity::Verbose:
		logMessage += "Verb \t";
		break;
	}
	logMessage += log;
	outStream << logMessage << '\n';

	if (isDebug)
	{
		std::cout << logMessage;
	}
}

double Logger::GetElapsedTime() noexcept
{
	return std::chrono::duration<double>(std::chrono::system_clock::now() - startTime).count();
}