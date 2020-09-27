#pragma once
#include <iostream>
#include <WS2tcpip.h>

enum class CLIENT_STATUS
{
	IN_LOBBY,
	READY,
	IN_GAME
};

class Player
{
private:
	struct PlayerData
	{
		int input = 0;
		std::string name = "";
		std::string msg = "";
		CLIENT_STATUS clientStatus;
		int ID = 0;
		bool playerTurn = true;
		sockaddr_in address;
	};
	PlayerData data;
public:
	void SetInput(int _input);
	void SetName(std::string _name);
	void SetGameState(std::string _gameState);
	void SetID(int _ID);
	void SetAddress(sockaddr_in _address);
	void SetClientStatus(CLIENT_STATUS status);
	inline int GetInput() { return data.input; };
	inline std::string GetName() { return data.name; };
	inline std::string GetGameState() { return data.msg; };
	inline int GetID() { return data.ID; };
	inline sockaddr_in GetAddress() { return data.address; };
	inline CLIENT_STATUS GetClientStatus() { return data.clientStatus; };
};

