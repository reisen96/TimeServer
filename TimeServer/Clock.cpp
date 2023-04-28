#include "Clock.h"

std::string Clock::getFormattedTime(const char* format)
{
	char buffer[255];
	std::tm* timeWithoutDate;
	currentTime = std::time(nullptr);
	timeWithoutDate = std::localtime(&currentTime);
	std::strftime(buffer, 254, format, timeWithoutDate);
	return std::string(buffer);
}

std::string Clock::getTime()
{
	std::string currentTimeString;
	currentTime = std::time(nullptr);
	currentTimeString = std::ctime(&currentTime);
	currentTimeString[currentTimeString.length() - 1] = '\0';
	return currentTimeString;
}

std::string Clock::getTimeWithoutDate() 
{
	return getFormattedTime("%T");
}

std::string Clock::getTimeSinceEpoch() 
{
	std::stringstream currentTimeString;
	currentTime = std::time(nullptr);
	currentTimeString << currentTime;
	return currentTimeString.str();
}

std::string Clock::getSystemUptime()
{
	return std::to_string(GetTickCount());
}

std::string Clock::getTimeWithoutDateOrSeconds()
{
	return getFormattedTime("%R");
}

std::string Clock::getYear() 
{
	return getFormattedTime("%Y");
}

std::string Clock::getMonthAndDay() 
{
	return getFormattedTime("%B %d");
}
