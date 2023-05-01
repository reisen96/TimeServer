#pragma once

#include "NetworkException.h"

class Clock
{
private:

	time_t currentTime;
	std::unordered_map<std::string, int> timeDifference;

	void initializeTimeDifference();
	std::string getFormattedTime(const char* format);

public:

	Clock();

	std::string getTime();
	std::string getTimeWithoutDate();
	std::string getTimeSinceEpoch();
	std::string getSystemUptime();
	std::string getTimeWithoutDateOrSeconds();
	std::string getYear();
	std::string getMonthAndDay();
	std::string getSecondsSinceBeginingOfMonth();
	std::string getWeekOfYear();
	std::string getDaylightSavings();
	std::string getSupportedCities();
};

