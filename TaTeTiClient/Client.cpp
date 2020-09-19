#include "Client.h"
#include <string>

Client::Client(int _port)
	:
	port(_port)
{
}

void Client::Initialize(int argc, char* argv[])
{
	version = MAKEWORD(2, 2);
	int wsOk = WSAStartup(version, &data);
	if (wsOk != 0)
	{
		cout << "CLIENT_DEBUG : Can't start Winsock! " << wsOk;
		return;
	}
	cout << "CLIENT_DEBUG : Client initialized correctly!" << endl;

	// Create a hint structure for the server
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

	// Socket Creation
	out = socket(AF_INET, SOCK_DGRAM, 0);

	// Write out to that socket
	string s(argv[1]);
	int sendOk = sendto(out, s.c_str(), s.size() + 1, 0, (sockaddr*)&server, sizeof(server));
	if (sendOk == SOCKET_ERROR) 
	{
		cout << " CLIENT_DEBUG : Can't send msg" << WSAGetLastError << endl;
	}
}

void Client::Shutdown()
{
	closesocket(out);
	WSACleanup();
}
