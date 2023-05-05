#pragma once

#include "Socket.h"

constexpr int bufferSize = 255;

class TimeServer
{
private:

	enum class ServerMethod {
		GetTime = 1,
		GetTimeWithoutDate,
		GetTimeSinceEpoch,
		GetClientToServerDelayEstimation,
		MeasureRTT,
		GetTimeWithoutDateOrSeconds,
		GetYear,
		GetMonthAndDay,
		GetSecondsSinceBeginingOfMonth,
		GetWeekOfYear,
		GetDaylightSavings,
		GetTimeWithoutDateInCity
	};

	const unsigned short serverPort = 27015u;
	Socket serverSocket;
	sockaddr clientSocketAddress;
	int clientSocketAddressLength;
	char receiveBuffer[bufferSize];
	char sendBuffer[bufferSize];
	std::unordered_map<std::string, ServerMethod> serverMethodCodes;
	Clock serverClock;

	void initializeMethodCodes();

	void send(const char* bytes, int length);
	int receive();

	void sendString(const std::string& responseString);
	std::string receiveString();

public:

	TimeServer();
	
	void run();
};

