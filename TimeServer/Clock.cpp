#include "Clock.h"

std::string Clock::getTime()
{
	currentTime = std::time(nullptr);
	return std::string(std::ctime(&currentTime));
}
