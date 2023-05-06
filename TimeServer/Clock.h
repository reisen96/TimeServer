#pragma once

#include "NetworkException.h"

constexpr int formattedTimeBufferSize = 255;

class Clock
{
private:

	time_t currentTime;
	std::tm* timeObject;
	std::unordered_map<std::string, int> timeDifference;

	inline void calculateCurrentTime();
	void initializeTimeDifference();
	std::string getFormattedTime(const char* format);

public:

	Clock();

	std::string getTime();
	std::string getTimeWithoutDate();
	std::string getTimeSinceEpoch();
	std::string getTimeWithoutDateOrSeconds();
	std::string getYear();
	std::string getMonthAndDay();
	std::string getSecondsSinceBeginingOfMonth();
	std::string getWeekOfYear();
	std::string getDaylightSavings();
	std::string getSupportedCities();
	std::string getTimeForCity(const std::string& city);
};

