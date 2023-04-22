#include "TimeServer.h"

TimeServer::TimeServer()
{
	serverSocket.initialize("", port);
	clientSocketAddressLength = sizeof(clientSocketAddress);
}

void TimeServer::send(char* bytes, int length)
{
	int bytesSent;
	for (int i = 0; i < length; ++i)
		sendBuffer[i] = bytes[i];
	bytesSent = sendto(*serverSocket.getWindowsSocket(), sendBuffer, (int)strlen(sendBuffer), 0, (const sockaddr*)&clientSocketAddress, clientSocketAddressLength);
	if (SOCKET_ERROR == bytesSent)
	{
		serverSocket.close();
		throw "Error: " + WSAGetLastError();
	}
}

void TimeServer::receive() 
{

}

void TimeServer::run() {

}
