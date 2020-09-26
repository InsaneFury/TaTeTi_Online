#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <WS2tcpip.h>
#include "Player.h"

#pragma comment (lib,"ws2_32.lib")

using namespace std;

class Server
{	
private:
	// Server Data
	WSADATA data;
	WORD version;
	SOCKET listenSocket;
	sockaddr_in server;
	int port;
	bool shutdown = false;
	unsigned int client_ID;
	bool board[8];

	// Multiple Clients
	map<sockaddr, Player> clients_sockets;
	vector<Player> clients_addrs; // info on client sockets
	int number_of_clients = 0;

	// Client Data
	SOCKET clientSocket;
	sockaddr_in from;
	char dataBuffer[1024];
	int dataLenght;
	char clientIp[256];
	Player player;

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
	void AcceptNewClient();
	void ListenForMessages();
	int SendMessageTo(Player _player);
	int SendMessageToAll(string gameState);

	// Shutdown winsock & Close socket
	void Shutdown();

	bool IsPositionAvailable(int pos);
};

