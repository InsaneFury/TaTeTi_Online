
#include "Server.h"
#include <string>

Server::Server(int _port)
	:
	port(_port),
	listenSocket(INVALID_SOCKET),
	clientSocket(INVALID_SOCKET),
	client_ID(0),
	dataLenght(0)
{
	for (int i = 0; i < 1024; i++)
		dataBuffer[i] = 0;
	for (int i = 0; i < 256; i++)
		clientIp[i] = 0;
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
	// Escucho y agrego nuevos clientes
	ListenForMessages();
	// Recorro todo los clientes en busca de gente en estado ready 
	TaTeTiUpdate();
}

void Server::AcceptNewClient()
{
	if (player.GetID() == -1) {
		player.SetID(client_ID);
	}
	if (clients.size() > 0) 
	{
		if ((clients.find(player.GetID()) != clients.end())) 
		{
			cout << endl;
			cout << "Client "+player.GetName() + " says:" << endl;
			return;
		}
	}

	clients[player.GetID()] = player;
	cout << endl;
	cout << "Client " + clients[player.GetID()].GetName() + " has been connected to the server" << endl;
	client_ID++;
	clientsConnected++;
	player.SetClientStatus(CLIENT_STATUS::IN_LOBBY);
	player.SetStatusMessage("IN LOBBY");
	SendMessageTo(player);
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

	for (auto iter = clients.begin(); iter != clients.end(); iter++)
	{
		player = iter->second;
		player.SetStatusMessage(gameState + player.GetName());
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
	cout << clientIp << " : " << player.GetInput() << endl;
}

void Server::Shutdown()
{
	if (listenSocket != INVALID_SOCKET)
		closesocket(listenSocket);

	if (clientSocket != INVALID_SOCKET)
		closesocket(clientSocket);
	
	WSACleanup();
}

void Server::TaTeTiUpdate()
{
	for (auto iter = clients.begin(); iter != clients.end(); iter++)
	{
		if(iter->second.GetClientStatus() < CLIENT_STATUS::READY)
		{
			iter->second.SetClientStatus(CLIENT_STATUS::READY);
			cout << "STATUS IN SERVER: "<<(int)iter->second.GetClientStatus() << endl;
			iter->second.SetStatusMessage("READY");
			SendMessageTo(iter->second);
		}

		if (iter->second.GetClientStatus() == CLIENT_STATUS::READY) 
		{
			if (clientsPlaying.find(iter->first) == clientsPlaying.end()) 
			{
				clientsPlaying[iter->second.GetID()] = iter->second;
				if(clientsPlaying.size() %2 == 0)
				{
					//Crear board
					Board board;
					boards[boardsIDs] = board;
					auto tempIter = iter--;
					iter->second.SetBoardID(boardsIDs);
					tempIter->second.SetBoardID(boardsIDs);
					boardsIDs++;

					tempIter->second.SetEnemyID(iter->second.GetID());
					iter->second.SetEnemyID(tempIter->second.GetID());

					iter->second.SetSkin(1);
					tempIter->second.SetSkin(2);

					tempIter->second.SetStatusMessage("IN GAME");
					iter->second.SetStatusMessage("IN GAME");

					SendMessageTo(tempIter->second);
					SendMessageTo(iter->second);

					tempIter->second.SetClientStatus(CLIENT_STATUS::IN_GAME);
					iter->second.SetClientStatus(CLIENT_STATUS::IN_GAME);

					tempIter->second.SetStatusMessage("VS " + iter->second.GetName());
					iter->second.SetStatusMessage("VS " + tempIter->second.GetName());

					SendMessageTo(tempIter->second);
					SendMessageTo(iter->second);

					RandomTaTeTiTurn(iter->second, tempIter->second);

				}
			}
		}
	}

	//ListenForMessages();

	for (auto iter2 = clientsPlaying.begin(); iter2 != clientsPlaying.end(); iter2++)
	{
		if(iter2->second.GetTurn())
		{
			iter2->second.SetInput(player.GetInput());
			if(boards[player.GetBoardID()].SetPlayerMove(player.GetInput(),player.GetSkin()))
			{
				TaTeTiTurn(iter2->second, false, clientsPlaying[iter2->second.GetEnemyID()], true);
			}
		}
	}
}

void Server::RandomTaTeTiTurn(Player &playerOne, Player &playerTwo)
{
	int turn = rand() % 100 + 1;
	if (turn > 50) 
		TaTeTiTurn(playerOne, true, playerTwo, false);
	else 
		TaTeTiTurn(playerOne, false, playerTwo, true);
}

void Server::TaTeTiTurn(Player& playerOne, bool turnOne, Player& playerTwo, bool turnTwo)
{
	if(turnOne)
	{
		playerOne.SetTurn(turnOne);
		playerTwo.SetTurn(turnTwo);
		playerOne.SetClientStatus(CLIENT_STATUS::TURN);
		playerTwo.SetClientStatus(CLIENT_STATUS::WAITING);
		playerOne.SetStatusMessage("YOUR TURN");
		playerTwo.SetStatusMessage("WAIT FOR TURN");
	}
	else 
	{
		playerOne.SetTurn(turnOne);
		playerTwo.SetTurn(turnTwo);
		playerOne.SetClientStatus(CLIENT_STATUS::WAITING);
		playerTwo.SetClientStatus(CLIENT_STATUS::TURN);
		playerOne.SetStatusMessage("WAIT FOR TURN");
		playerTwo.SetStatusMessage("YOUR TURN");
	}
	SendMessageTo(playerOne);
	SendMessageTo(playerTwo);
}
