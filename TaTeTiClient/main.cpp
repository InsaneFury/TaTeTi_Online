#include <iostream>
#include "Client.h"

void main(int argc, char*argv[])
{
	Client* client = new Client(8900);

	client->Initialize(argc, argv);
	client->Shutdown();

	delete client;
}