#include "TimeServer.h"

TimeServer::TimeServer()
{
	serverSocket.initialize("", port);
	clientSocketAddressLength = sizeof(clientSocketAddress);
	serverSocket.bindToPort();
}

void TimeServer::send(char* bytes, int length)
{
	int bytesSent;
	for (int i = 0; i < length; ++i)
		sendBuffer[i] = bytes[i];
	bytesSent = sendto(serverSocket.getWindowsSocket(), sendBuffer, (int)strlen(sendBuffer), 0, (const sockaddr*)&clientSocketAddress, clientSocketAddressLength);
	if (bytesSent == SOCKET_ERROR)
	{
		serverSocket.close();
		throw "Send error: " + WSAGetLastError();
	}
}

int TimeServer::receive()
{
	int bytesReceived;
	bytesReceived = recvfrom(serverSocket.getWindowsSocket(), receiveBuffer, bufferSize, 0, &clientSocketAddress, &clientSocketAddressLength);
	if (bytesReceived == SOCKET_ERROR)
	{
		serverSocket.close();
		std::cout << std::to_string(WSAGetLastError());
	}
	return bytesReceived;
}

void TimeServer::run() 
{
	int bytesReceived;
	while (true) 
	{
		bytesReceived = receive();
		receiveBuffer[bytesReceived] = '\0';
		std::cout << bytesReceived << std::endl;
		std::cout << receiveBuffer;
		return;
	}
}
