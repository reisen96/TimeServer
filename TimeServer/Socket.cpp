#include "Socket.h"

Socket::~Socket()
{
	close();
}

void Socket::initialize(std::string ipAddress, unsigned short port, int type, int protocol)
{
	WSAData wsaData;
	if (NO_ERROR != WSAStartup(MAKEWORD(majorWinsockVersion, minorWinsockVersion), &wsaData))
		throw "Error initializing Winsock";
	windowsSocket = socket(AF_INET, type, protocol);
	if (INVALID_SOCKET == windowsSocket)
	{
		WSACleanup();
		throw "Error initializing socket: " + WSAGetLastError();
	}
	socketAddress.sin_family = AF_INET;
	socketAddress.sin_addr.s_addr = ipAddress.length() ? inet_addr(ipAddress.c_str()) : INADDR_ANY;
	socketAddress.sin_port = htons(port);
}

void Socket::bindToPort()
{
	if (SOCKET_ERROR == bind(windowsSocket, (SOCKADDR*)&socketAddress, sizeof(socketAddress)))
	{
		close();
		throw "Error binding socket: " + WSAGetLastError();
	}
}

void Socket::close() 
{
	closesocket(windowsSocket);
	WSACleanup();
}
