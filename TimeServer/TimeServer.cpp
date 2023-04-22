#include "TimeServer.h"

TimeServer::TimeServer()
{
	serverSocket.initialize("", port);
	clientSocketAddressLength = sizeof(clientSocketAddress);
}

void TimeServer::send() 
{

}

void TimeServer::receive() 
{

}

void TimeServer::run() {

}
