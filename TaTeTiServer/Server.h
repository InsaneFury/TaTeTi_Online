#pragma once
#include <iostream>
#include <WS2tcpip.h>

#pragma comment (lib,"ws2_32.lib")

using namespace std;

class Server
{
private:
	// Server Data
	WSADATA data;
	WORD version;
	SOCKET inSocket;
	sockaddr_in serverHint;
	int port;
	bool shutdown = false;

	// Client Data
	sockaddr_in client;
	char clientBuffer[1024];
	int clientLenght;
	char clientIp[256];

private:
	void ShowReceivedMessage();

public:
	Server(int _port);

	// Startup Winsock
	void Initialize();
	
	// Bind socket to ip address and port
	void BindSocket();

	// Enter a loop
	// Wait for message
	// Display message and client info
	void ListenForMessages();

	void Shutdown();
	// Close socket
	// Shutdown winsock
};

