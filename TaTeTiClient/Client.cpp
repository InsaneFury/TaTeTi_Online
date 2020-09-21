#include "Client.h"
#include <string>



Client::Client(int _port)
	:
	port(_port)
{
}

void Client::Initialize()
{
	version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		std::cout << "CLIENT_DEBUG : Can't start Winsock! " << wsOk;
		return;
	}
	std::cout << "CLIENT_DEBUG : Client initialized correctly!" << std::endl;

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

	std::cout << "Ingrese su nombre: " << std::endl;
	std::getline(std::cin, playerData.name);
	SendMSG();
	ListenForMessages();
}

void Client::SendMSG()
{
	// Write out to that socket
	int sendOk = sendto(sock, (char*)&playerData, sizeof(playerData), 0, (sockaddr*)&server, sizeof(server));
	if (sendOk == SOCKET_ERROR)
	{
		std::cout << " CLIENT_DEBUG : Can't send msg" << WSAGetLastError << std::endl;
	}
}

void Client::ListenForMessages()
{
	dataLenght = sizeof(from);
	ZeroMemory(&from, dataLenght);
	ZeroMemory(dataBuffer, 1024);

	int bytesIn = recvfrom(sock, dataBuffer, 1024, 0, (sockaddr*)&from, &dataLenght);
	if (bytesIn == SOCKET_ERROR)
	{
		std::cout << "Error receiving from client " << WSAGetLastError() << std::endl;
	}
	else {
		ZeroMemory(serverIp, 256);
		ShowReceivedMessage();
	}
	
}

void Client::ShowReceivedMessage()
{
	inet_ntop(AF_INET, &from.sin_addr, serverIp, 256);
	std::cout << "Message recv from " << serverIp << " : " << dataBuffer << std::endl;
}

void Client::Shutdown()
{
	closesocket(sock);
	WSACleanup();
}
