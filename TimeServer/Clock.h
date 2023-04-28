#pragma once

#include "NetworkException.h"

class Clock
{
private:

	time_t currentTime;

	std::string getFormattedTime(const char* format);

public:

	std::string getTime();
	std::string getTimeWithoutDate();
	std::string getTimeSinceEpoch();
	std::string getSystemUptime();
	std::string getTimeWithoutDateOrSeconds();
	std::string getYear();
	std::string getMonthAndDay();
};

