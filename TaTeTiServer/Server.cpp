
#include "Server.h"
#include <string>

Server::Server(int _port)
	:
	port(_port),
	listenSocket(INVALID_SOCKET),
	clientSocket(INVALID_SOCKET),
	client_ID(0)
{
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
	server.sin_addr.S_un.S_addr = INADDR_ANY;
	server.sin_port = htons(port);
	inet_pton(AF_INET, "192.168.1.38", &server.sin_addr);


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
	if (AcceptNewClient(client_ID))
	{
		cout << "Client " + client_ID + playerData.name + " has been connected to the server" << endl;
		cout << "Total Clients Connected: " + client_ID + 1 << endl;
		client_ID++;
	}
	ListenForMessages();
}

bool Server::AcceptNewClient(unsigned int& id)
{
	clientSocket = accept(listenSocket, (sockaddr*)&from, &dataLenght);
	if (clientSocket != INVALID_SOCKET) {
			clients_sockets.insert(std::pair<unsigned int, SOCKET>(id, clientSocket));
			clients_addrs.push_back(from);
			return true;
	}
	return false;
}

void Server::ListenForMessages()
{
	int bytesIn = recvfrom(listenSocket, (char*)&playerData, sizeof(playerData), 0, (sockaddr*)&from, &dataLenght);
	if (bytesIn == SOCKET_ERROR)
	{
		// Drop the client
		closesocket(listenSocket);
		cout << "Error receiving from client " << WSAGetLastError() << endl;
	}
	else 
	{
		ZeroMemory(clientIp, 256);
		ShowReceivedMessage();			
		SendMessageTo(listenSocket,playerData,from);
	}	
}

int Server::SendMessageTo(SOCKET _currentSocket, PlayerData _playerData,sockaddr_in _from)
{
	int sendOk = sendto(_currentSocket, (char*)&_playerData, sizeof(_playerData), 0, (sockaddr*)&_from, sizeof(_from));
	if (sendOk == SOCKET_ERROR)
	std::cout << " SERVER_DEBUG : Can't send msg" << WSAGetLastError << std::endl;

	return sendOk;
}

int Server::SendMessageToAll(SOCKET _currentSocket, PlayerData _playerData)
{
	SOCKET currentSocket;
	std::map<unsigned int, SOCKET>::iterator iter;
	int iSendResult;

	for (iter = clients_sockets.begin(); iter != clients_sockets.end(); iter++)
	{
		currentSocket = iter->second;
		iSendResult = SendMessageTo(currentSocket, playerData, from);

		if (iSendResult == SOCKET_ERROR)
		{
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(currentSocket);
		}
	}

	return iSendResult;
}

void Server::ShowReceivedMessage()
{
	inet_ntop(AF_INET, &from.sin_addr, clientIp, 256);
	cout << "Message recv from " << clientIp << " : " << playerData.name << endl;
}

void Server::Shutdown()
{
	if (listenSocket != INVALID_SOCKET)
		closesocket(listenSocket);

	if (clientSocket != INVALID_SOCKET)
		closesocket(clientSocket);
	
	WSACleanup();
}
