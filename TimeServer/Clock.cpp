#include "Clock.h"

Clock::Clock() 
{
	initializeTimeDifference();
}

void Clock::initializeTimeDifference()
{
	timeDifference["Doha"] = 3;
	timeDifference["Prague"] = 2;
	timeDifference["New York"] = -4;
	timeDifference["Berlin"] = 2;
}

std::string Clock::getFormattedTime(const char* format)
{
	char buffer[255];
	currentTime = std::time(nullptr);
	timeObject = std::localtime(&currentTime);
	std::strftime(buffer, 254, format, timeObject);
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

std::string Clock::getSecondsSinceBeginingOfMonth()
{
	currentTime = std::time(nullptr);
	timeObject = std::localtime(&currentTime);
	timeObject->tm_mday = 1;
	timeObject->tm_hour = 0;
	timeObject->tm_min = 0;
	timeObject->tm_sec = 0;
	return std::to_string(std::difftime(currentTime, mktime(timeObject)));
}

std::string Clock::getWeekOfYear() 
{
	return getFormattedTime("%U");
}

std::string Clock::getDaylightSavings() 
{
	currentTime = std::time(nullptr);
	return std::localtime(&currentTime)->tm_isdst ? std::string("1") : std::string("0");
}

std::string Clock::getSupportedCities() 
{
	std::string supportedCities("Supported cities:\n");
	for (std::pair<std::string, int> pair : timeDifference) 
		supportedCities.append(pair.first + '\n');
	return supportedCities;
}

std::string Clock::getTimeForCity(const std::string& city)
{
	int difference = timeDifference[city];
	if (!difference)
		return std::string("Unsupported city");
	currentTime = std::time(nullptr);
	timeObject = std::gmtime(&currentTime);
	timeObject->tm_hour = (timeObject->tm_hour + difference) % 24;
	return getFormattedTime("%T");
}
