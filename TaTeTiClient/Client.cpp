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
	std::string name;
	std::getline(std::cin, name);
	player.SetName(name);

	SendMessageToServer();
}

void Client::SendMessageToServer()
{
	// Write out to that socket
	int sendOk = sendto(sock, (char*)&player, sizeof(player), 0, (sockaddr*)&server, sizeof(server));
	if (sendOk == SOCKET_ERROR)
	{
		std::cout << " CLIENT_DEBUG : Can't send msg" << WSAGetLastError << std::endl;
	}
}



bool Client::ListenForMessages()
{
	dataLenght = sizeof(from);
	ZeroMemory(&from, dataLenght);

	int bytesIn = recvfrom(sock, (char*)&player,sizeof(player), 0, (sockaddr*)&from, &dataLenght);
	if (bytesIn == 0) {
		std::cout<<"Connection with server closed"<< std::endl;
		closesocket(sock);
		WSACleanup();
		exit(1);
	}
	else if (bytesIn >0){	
		ShowReceivedMessage();
		return true;
	}
	//int bytesIn = recvfrom(sock, dataBuffer, 1024, 0, (sockaddr*)&from, &dataLenght);
	if (bytesIn == SOCKET_ERROR)
	{
		return false;
		//std::cout << "Error receiving from client " << WSAGetLastError() << std::endl;
	}
}

void Client::ListenForEvents()
{
}

void Client::ShowReceivedMessage()
{
	std::cout << "SERVER: " << player.GetGameState() << std::endl;
}

void Client::Shutdown()
{
	closesocket(sock);
	WSACleanup();
}
