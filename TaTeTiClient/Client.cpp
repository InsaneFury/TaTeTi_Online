#define WM_ONSOCKET WM_USER+1
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

	WSAEventSelect(sock, EventHandler, (FD_READ | FD_CONNECT | FD_CLOSE));

	std::cout << "Ingrese su nombre: " << std::endl;
	std::getline(std::cin, playerData.name);
	//std::cin >> dataBuffer;
	SendMSG();
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

	int bytesIn = recvfrom(sock, (char*)&playerData,sizeof(playerData), 0, (sockaddr*)&from, &dataLenght);
	//int bytesIn = recvfrom(sock, dataBuffer, 1024, 0, (sockaddr*)&from, &dataLenght);
	if (bytesIn == SOCKET_ERROR)
	{
		return;
		//std::cout << "Error receiving from client " << WSAGetLastError() << std::endl;
	}
	else {
		ZeroMemory(serverIp, 256);
		ShowReceivedMessage();
	}
}

void Client::ListenForEvents()
{
}

void Client::ShowReceivedMessage()
{
	inet_ntop(AF_INET, &from.sin_addr, serverIp, 256);
	std::cout << "Message recv from " << serverIp << " : " << playerData.name << std::endl;
}

void Client::Shutdown()
{
	closesocket(sock);
	WSACleanup();
}
