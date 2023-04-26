#include "Clock.h"

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
	char buffer[255];
	std::tm* timeWithoutDate;
	currentTime = std::time(nullptr);
	timeWithoutDate = std::localtime(&currentTime);
	std::strftime(buffer, 254, "%T", timeWithoutDate);
	return std::string(buffer);
}

std::string Clock::getTimeSinceEpoch() 
{
	std::stringstream currentTimeString;
	currentTime = std::time(nullptr);
	currentTimeString << currentTime;
	return currentTimeString.str();
}
