#pragma once
#include <iostream>
#include <map>
#include <WS2tcpip.h>

#pragma comment (lib,"ws2_32.lib")

using namespace std;

class Server
{
	struct PlayerData
	{
		int input = 0;
		std::string name = "";
		std::string gameState = "";
		int ID = 0;
	};
private:
	// Server Data
	WSADATA data;
	WORD version;
	SOCKET sock;
	sockaddr_in server;
	int port;
	bool shutdown = false;
	
	// Multiple Clients
	map<unsigned int, SOCKET> Clients;

	// Client Data
	sockaddr_in from;
	char dataBuffer[1024];
	int dataLenght;
	char clientIp[256];
	PlayerData playerData;

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

	void SendMSG();

	void Shutdown();
	// Close socket
	// Shutdown winsock
};

