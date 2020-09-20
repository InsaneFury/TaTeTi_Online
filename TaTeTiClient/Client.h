#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include <WS2tcpip.h>

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
	void Initialize();

	
	void SendMSG(std::string msg);

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

#endif // CLIENT_H

