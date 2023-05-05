#include "TimeServer.h"

TimeServer::TimeServer()
{
	serverSocket.initialize("", serverPort);
	serverSocket.bindToPort();
	clientSocketAddressLength = sizeof(clientSocketAddress);
	initializeMethodCodes();
}

void TimeServer::initializeMethodCodes()
{
	serverMethodCodes[std::string("GetTime")] = ServerMethod::GetTime;
	serverMethodCodes[std::string("GetTimeWithoutDate")] = ServerMethod::GetTimeWithoutDate;
	serverMethodCodes[std::string("GetTimeSinceEpoch")] = ServerMethod::GetTimeSinceEpoch;
	serverMethodCodes[std::string("GetClientToServerDelayEstimation")] = ServerMethod::GetClientToServerDelayEstimation;
	serverMethodCodes[std::string("MeasureRTT")] = ServerMethod::MeasureRTT;
	serverMethodCodes[std::string("GetTimeWithoutDateOrSeconds")] = ServerMethod::GetTimeWithoutDateOrSeconds;
	serverMethodCodes[std::string("GetYear")] = ServerMethod::GetYear;
	serverMethodCodes[std::string("GetMonthAndDay")] = ServerMethod::GetMonthAndDay;
	serverMethodCodes[std::string("GetSecondsSinceBeginingOfMonth")] = ServerMethod::GetSecondsSinceBeginingOfMonth;
	serverMethodCodes[std::string("GetWeekOfYear")] = ServerMethod::GetWeekOfYear;
	serverMethodCodes[std::string("GetDaylightSavings")] = ServerMethod::GetDaylightSavings;
	serverMethodCodes[std::string("GetTimeWithoutDateInCity")] = ServerMethod::GetTimeWithoutDateInCity;
}

void TimeServer::send(const char* bytes, int length)
{
	int bytesSent;
	for (int i = 0; i < length; ++i)
		sendBuffer[i] = bytes[i];
	bytesSent = sendto(serverSocket.getWindowsSocket(), sendBuffer, (int)strlen(sendBuffer), 0, (const sockaddr*)&clientSocketAddress, clientSocketAddressLength);
	if (bytesSent == SOCKET_ERROR)
	{
		serverSocket.close();
		throw NetworkException(std::string("Send error: ") + std::to_string(WSAGetLastError()));
	}
}

int TimeServer::receive()
{
	int bytesReceived;
	bytesReceived = recvfrom(serverSocket.getWindowsSocket(), receiveBuffer, bufferSize, 0, &clientSocketAddress, &clientSocketAddressLength);
	if (bytesReceived == SOCKET_ERROR)
	{
		serverSocket.close();
		throw NetworkException(std::string("Receive error: ") + std::to_string(WSAGetLastError()));
	}
	return bytesReceived;
}

void TimeServer::sendString(const std::string& responseString)
{
	send(responseString.c_str(), (int)responseString.length() + 1);
}

std::string TimeServer::receiveString()
{
	int bytesReceived = receive();
	receiveBuffer[bytesReceived] = '\0';
	return std::string(receiveBuffer);
}

void TimeServer::run() 
{
	ServerMethod requestMethod;
	std::string requestString, responseString;
	while (true) 
	{
		try 
		{
			requestString = receiveString();
			requestMethod = serverMethodCodes[requestString];
			switch (requestMethod) 
			{
			case ServerMethod::GetTime:
				responseString = serverClock.getTime();
				break;
			case ServerMethod::GetTimeWithoutDate:
				responseString = serverClock.getTimeWithoutDate();
				break;
			case ServerMethod::GetTimeSinceEpoch:
				responseString = serverClock.getTimeSinceEpoch();
				break;
			case ServerMethod::GetClientToServerDelayEstimation:
				responseString = serverClock.getSystemUptime();
				break;
			case ServerMethod::MeasureRTT:
				responseString = serverClock.getSystemUptime();
				break;
			case ServerMethod::GetTimeWithoutDateOrSeconds:
				responseString = serverClock.getTimeWithoutDateOrSeconds();
				break;
			case ServerMethod::GetYear:
				responseString = serverClock.getYear();
				break;
			case ServerMethod::GetMonthAndDay:
				responseString = serverClock.getMonthAndDay();
				break;
			case ServerMethod::GetSecondsSinceBeginingOfMonth:
				responseString = serverClock.getSecondsSinceBeginingOfMonth();
				break;
			case ServerMethod::GetWeekOfYear:
				responseString = serverClock.getWeekOfYear();
				break;
			case ServerMethod::GetDaylightSavings:
				responseString = serverClock.getDaylightSavings();
				break;
			case ServerMethod::GetTimeWithoutDateInCity:
				sendString(serverClock.getSupportedCities());
				responseString = serverClock.getTimeForCity(receiveString());
				break;
			default:
				responseString = "Invalid request";
			}
			sendString(responseString);
		}
		catch (std::exception exception)
		{
			std::cout << exception.what();
		}
	}
}
