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

	// Create a hint structure for the server
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

	// Socket Creation
	out = socket(AF_INET, SOCK_DGRAM, 0);
	SendMSG("HELLO THERE");
}

void Client::SendMSG(std::string msg)
{
	// Write out to that socket
	int sendOk = sendto(out, msg.c_str(), msg.size() + 1, 0, (sockaddr*)&server, sizeof(server));
	if (sendOk == SOCKET_ERROR)
	{
		std::cout << " CLIENT_DEBUG : Can't send msg" << WSAGetLastError << std::endl;
	}
}

void Client::Shutdown()
{
	closesocket(out);
	WSACleanup();
}
