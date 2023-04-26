#pragma once

#include "NetworkException.h"

class Clock
{
private:

	time_t currentTime;

public:

	std::string getTime();
	std::string getTimeWithoutDate();
	std::string getTimeSinceEpoch();
};

