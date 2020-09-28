#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <WS2tcpip.h>
#include "../TaTeTiClient/Player.h"
#include "Board.h"

#pragma comment (lib,"ws2_32.lib")

using namespace std;

enum PlayerTurn
{
	PLAYER_ONE = 1,
	PLAYER_TWO
};

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

	// Multiple Clients
	map<int,Player> clients;
	map<int, Player> clientsPlaying;
	int clientsConnected = 0;
	map<int, Board> boards;
	int boardsIDs = 0;

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

	void TaTeTiUpdate();
	void RandomTaTeTiTurn(Player& playerOne, Player& playerTwo);
	void TaTeTiTurn(Player& playerOne,bool turnOne, Player& playerTwo, bool turnTwo);
};

