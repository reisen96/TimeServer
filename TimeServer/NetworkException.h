#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib")
#include <winsock2.h>

class NetworkException : public std::exception
{
private:

	std::string errorMessage;

public:

	NetworkException(std::string message) { errorMessage = message; }
	const char* what() { return errorMessage.c_str(); }
};

