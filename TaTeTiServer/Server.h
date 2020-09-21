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
	SOCKET sock;
	sockaddr_in server;
	int port;
	bool shutdown = false;

	// Client Data
	sockaddr_in from;
	char dataBuffer[1024];
	int dataLenght;
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

	void SendMSG(std::string msg);

	void Shutdown();
	// Close socket
	// Shutdown winsock
};

