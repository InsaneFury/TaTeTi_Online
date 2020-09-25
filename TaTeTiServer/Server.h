#pragma once
#include <iostream>
#include <map>
#include <vector>
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
	SOCKET listenSocket;
	sockaddr_in server;
	int port;
	bool shutdown = false;
	unsigned int client_ID;

	// Multiple Clients
	map<unsigned int, SOCKET> clients_sockets;
	vector<sockaddr_in> clients_addrs; // info on client sockets
	int number_of_clients = 0;

	// Client Data
	SOCKET clientSocket;
	sockaddr_in from;
	char dataBuffer[1024];
	int dataLenght;
	char clientIp[256];
	PlayerData playerData;

private:
	void ShowReceivedMessage();

public:
	Server(int _port);
	~Server();

	// Startup Winsock
	void Start();
	void Update();

	// Bind socket to ip address and port
	void BindSocket();
	//Accept new client and add it to the map
	bool AcceptNewClient(unsigned int& id);
	void ListenForMessages();
	int SendMessageTo(SOCKET _currentSocket, PlayerData _playerData, sockaddr_in _from);
	int SendMessageToAll(SOCKET _currentSocket, PlayerData _playerData);

	// Shutdown winsock & Close socket
	void Shutdown();
};

