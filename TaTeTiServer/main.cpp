#include <iostream>
#include "Server.h"

void main()
{
	Server* server = new Server(8900);

	server->Start();
	while (true) 
	{
		server->Update();
	}
	delete server;
}