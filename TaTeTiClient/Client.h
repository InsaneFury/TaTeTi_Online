#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include <WS2tcpip.h>
#include "Player.h"

class Client
{
private:
	// Client Data
	WSADATA data;
	WORD version;
	int port;
	SOCKET sock = INVALID_SOCKET;
	sockaddr_in server;
	SOCKET connectionSocket;
	HANDLE EventHandler;

	// Server Data
	sockaddr_in from;
	char dataBuffer[1024];
	int dataLenght;
	char serverIp[256];

private:

public:
	Player player;
	Client(int _port);

	// Startup Winsock
	void Initialize();
	
	void SendMessageToServer();

	void ShowReceivedMessage();
	// Enter a loop
	// Wait for message
	// Display message and client info
	bool ListenForMessages();

	void ListenForEvents();
	// Close socket
	// Shutdown winsock
	void Shutdown();
};

#endif // CLIENT_H

