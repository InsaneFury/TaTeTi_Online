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
	sock = socket(AF_INET, SOCK_DGRAM, 0);

	if (sock < 0) 
	{
		cout << "SERVER_DEBUG : Error openning socket" << endl;
	}
	server.sin_family = AF_INET;
	server.sin_addr.S_un.S_addr = ADDR_ANY;
	server.sin_port = htons(port);
	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
}

void Server::BindSocket()
{
	if(bind(sock,(sockaddr*) &server,sizeof(server)) == SOCKET_ERROR)
	{
		cout << "SERVER_DEBUG : Can't bind socket! " << WSAGetLastError() << endl;
		return;
	}
	cout << "SERVER_DEBUG : Server binded correctly!" << endl;

	dataLenght = sizeof(from);
	ZeroMemory(&from, dataLenght);
	ZeroMemory(dataBuffer, 1024);
}

void Server::ListenForMessages()
{
	while (!shutdown)
	{
		ZeroMemory(dataBuffer, 1024);
		int bytesIn = recvfrom(sock, dataBuffer, 1024, 0, (sockaddr*)&from, &dataLenght);
		if(bytesIn == SOCKET_ERROR)
		{
			cout << "Error receiving from client " << WSAGetLastError() << endl;
			continue;
		}
		
		ZeroMemory(clientIp, 256);
		ShowReceivedMessage();
		SendMSG("MSG Recieved");
	}
}

void Server::SendMSG(std::string msg)
{
	// Write out to that socket
	int sendOk = sendto(sock, msg.c_str(), msg.size() + 1, 0, (sockaddr*)&from, sizeof(from));
	if (sendOk == SOCKET_ERROR)
	{
		std::cout << " SERVER_DEBUG : Can't send msg" << WSAGetLastError << std::endl;
	}
}

void Server::ShowReceivedMessage()
{
	inet_ntop(AF_INET, &from.sin_addr, clientIp, 256);
	cout << "Message recv from " << clientIp << " : " << dataBuffer << endl;
}

void Server::Shutdown()
{
	closesocket(sock);
	WSACleanup();
}
