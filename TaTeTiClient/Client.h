#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include <WS2tcpip.h>

class Client
{
	struct PlayerData
	{
		int input = 0;
		std::string name = "";
		std::string gameState = "";
		int ID = 0;
	};

private:
	// Client Data
	WSADATA data;
	WORD version;
	int port;
	SOCKET sock = INVALID_SOCKET;
	sockaddr_in server;
	PlayerData playerData;

	// Server Data
	sockaddr_in from;
	char dataBuffer[1024];
	int dataLenght;
	char serverIp[256];

private:
	void ShowReceivedMessage();

public:
	Client(int _port);

	// Startup Winsock
	void Initialize();
	
	void SendMSG();

	// Enter a loop
	// Wait for message
	// Display message and client info
	void ListenForMessages();

	// Close socket
	// Shutdown winsock
	void Shutdown();
};

#endif // CLIENT_H

