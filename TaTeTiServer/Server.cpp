
#include "Server.h"
#include <string>

Server::Server(int _port)
	:
	port(_port),
	listenSocket(INVALID_SOCKET),
	clientSocket(INVALID_SOCKET),
	client_ID(0)
{
	for (int i = 0; i < 8; i++)
	{
		board[i] = 0;
	}
}

Server::~Server()
{
	Shutdown();
}

void Server::Start()
{
	version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if(wsOk != 0)
	{
		cout << "SERVER_DEBUG : Can't start Winsock! " << wsOk;
		return;
	}
	cout << "SERVER_DEBUG : Server initialized correctly!" << endl;
	listenSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (listenSocket < 0) 
	{
		cout << "SERVER_DEBUG : Error openning socket" << endl;
	}
	server.sin_family = AF_INET;
	server.sin_addr.S_un.S_addr = ADDR_ANY;
	server.sin_port = htons(port);
	//inet_pton(AF_INET, "192.168.1.38", &server.sin_addr); not neccesary because im using ADDR_ANY


	BindSocket();
}

void Server::BindSocket()
{
	if(bind(listenSocket,(sockaddr*) &server,sizeof(server)) == SOCKET_ERROR)
	{
		cout << "SERVER_DEBUG : Can't bind socket! " << WSAGetLastError() << endl;
		return;
	}
	cout << "SERVER_DEBUG : Server binded correctly!" << endl;

	dataLenght = sizeof(from);
	ZeroMemory(&from, dataLenght);
}

void Server::Update()
{
	if (number_of_clients == 2) {
		SendMessageToAll("Hello ");
		number_of_clients++;
	}
	ListenForMessages();
}

void Server::AcceptNewClient()
{
		Player tempPlayer = player;
		clients_addrs.insert(std::pair<string,Player>(tempPlayer.GetName(), tempPlayer));
		cout << "Client " + player.GetName() + " has been connected to the server" << endl;
		client_ID++;
		number_of_clients++;
}

void Server::ListenForMessages()
{
	int bytesIn = recvfrom(listenSocket, (char*)&player, sizeof(player), 0, (sockaddr*)&from, &dataLenght);
	if (bytesIn == SOCKET_ERROR)
	{
		// Drop the client
		closesocket(listenSocket);
		cout << "Error receiving from client " << WSAGetLastError() << endl;
	}
	else 
	{
		player.SetAddress(from);	
		AcceptNewClient();

		ZeroMemory(clientIp, 256);
		ShowReceivedMessage();
	}	
}

int Server::SendMessageTo(Player _player)
{
	int sendOk = sendto(listenSocket, (char*)&_player, sizeof(_player), 0, (sockaddr*)&_player.GetAddress(), sizeof(_player.GetAddress()));
	if (sendOk == SOCKET_ERROR)
	std::cout << " SERVER_DEBUG : Can't send msg" << WSAGetLastError << std::endl;

	return sendOk;
}

int Server::SendMessageToAll(string gameState)
{
	int iSendResult = 0;

	for (auto iter = clients_addrs.begin(); iter != clients_addrs.end(); iter++)
	{
		player = iter->second;
		player.SetGameState(gameState + player.GetName());
		iSendResult = SendMessageTo(player);

		if (iSendResult == SOCKET_ERROR)
		{
			printf("send failed with error: %d\n", WSAGetLastError());
		}
	}

	return iSendResult;
}

void Server::ShowReceivedMessage()
{
	inet_ntop(AF_INET, &from.sin_addr, clientIp, 256);
	cout << "Message recv from " << clientIp << " : " << player.GetInput() << endl;
}

void Server::Shutdown()
{
	if (listenSocket != INVALID_SOCKET)
		closesocket(listenSocket);

	if (clientSocket != INVALID_SOCKET)
		closesocket(clientSocket);
	
	WSACleanup();
}

bool Server::IsPositionAvailable(int pos)
{
	if (board[pos] == 0)
	{
		board[pos] = pos;
		return true;
	}
	return false;
}
