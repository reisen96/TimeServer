
#include "TimeServer.h"

int main(int argc, char* argv[]) {
	try 
	{
		TimeServer timeServer;
		timeServer.run();
	}
	catch (std::exception exception)
	{
		std::cout << exception.what();
	}
	return 0;
}