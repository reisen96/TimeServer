#pragma once

#include "Socket.h"

constexpr int bufferSize = 255;

class TimeServer
{
private:

	const unsigned short port = 27015u;
	Socket serverSocket;
	sockaddr clientSocketAddress;
	int clientSocketAddressLength;
	char receiveBuffer[bufferSize];
	char sendBuffer[bufferSize];

	void send(const char* bytes, int length);
	int receive();

public:

	TimeServer();
	
	void run();
};

