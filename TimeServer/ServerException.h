#pragma once

#include "Socket.h"

class ServerException : public std::exception
{
private:

	std::string errorMessage;

public:

	ServerException(std::string message) { errorMessage = message; }
	const char* what() { return errorMessage.c_str(); }
};

