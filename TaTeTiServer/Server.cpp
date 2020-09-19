#include "Server.h"

Server::Server(int _port)
	:
	port(_port)
{
}

void Server::Initialize()
{
	version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if(wsOk != 0)
	{
		cout << "SERVER_DEBUG : Can't start Winsock! " << wsOk;
		return;
	}
	cout << "SERVER_DEBUG : Server initialized correctly!" << endl;
}

void Server::BindSocket()
{
	inSocket = socket(AF_INET, SOCK_DGRAM, 0);
	serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
	serverHint.sin_family = AF_INET;
	serverHint.sin_port = htons(port);

	if(bind(inSocket,(sockaddr*) &serverHint,sizeof(serverHint)) == SOCKET_ERROR)
	{
		cout << "SERVER_DEBUG : Can't bind socket! " << WSAGetLastError() << endl;
		return;
	}
	cout << "SERVER_DEBUG : Server binded correctly!" << endl;

	clientLenght = sizeof(client);
	ZeroMemory(&client, clientLenght);
	ZeroMemory(clientBuffer, 1024);
}

void Server::ListenForMessages()
{
	while (!shutdown)
	{
		ZeroMemory(clientBuffer, 1024);
		int bytesIn = recvfrom(inSocket, clientBuffer, 1024, 0, (sockaddr*)&client, &clientLenght);
		if(bytesIn == SOCKET_ERROR)
		{
			cout << "Error receiving from client " << WSAGetLastError() << endl;
			continue;
		}

		ZeroMemory(clientIp, 256);
		ShowReceivedMessage();
	}
}

void Server::ShowReceivedMessage()
{
	inet_ntop(AF_INET, &client.sin_addr, clientIp, 256);
	cout << "Message recv from " << clientIp << " : " << clientBuffer << endl;
}

void Server::Shutdown()
{
	closesocket(inSocket);
	WSACleanup();
}
