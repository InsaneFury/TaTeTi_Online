#pragma once
#include <iostream>
#include <WS2tcpip.h>

#pragma comment (lib,"ws2_32.lib")

using namespace std;

class Client
{
private:
	// Client Data
	WSADATA data;
	WORD version;
	int port;
	SOCKET out;

	// Server Data
	sockaddr_in server;

private:
	//void ShowReceivedMessage();

public:
	Client(int _port);

	// Startup Winsock
	void Initialize(int argc, char* argv[]);

	
	
	
	// Close the socket

	// Bind socket to ip address and port
	//void BindSocket();

	// Enter a loop
	// Wait for message
	// Display message and client info
	//void ListenForMessages();

	// Close socket
	// Shutdown winsock
	void Shutdown();
};

