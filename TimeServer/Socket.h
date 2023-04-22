#pragma once

#include <iostream>
#include <string>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>

class Socket
{
private:

	const int majorWinsockVersion = 2;
	const int minorWinsockVersion = 2;
	SOCKET windowsSocket;
	sockaddr_in socketAddress;
	
public:

	~Socket();

	const SOCKET* getWindowsSocket() { return &windowsSocket; }

	void initialize(std::string ipAddress, unsigned short port, int type = SOCK_DGRAM, int protocol = IPPROTO_UDP);
	void bindToPort();
	void close();
};

