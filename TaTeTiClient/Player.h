#pragma once
#include <iostream>
#include <WS2tcpip.h>

enum class CLIENT_STATUS
{
	NONE,
	IN_LOBBY,
	READY,
	IN_GAME,
	WAITING,
	TURN,
	WIN,
	LOSE,
	TIE
};

class Player
{
private:
	struct PlayerData
	{
		int input = 0;
		std::string name = "";
		std::string msg = "";
		CLIENT_STATUS clientStatus = CLIENT_STATUS::NONE;
		int ID = -1;
		bool playerTurn = true;
		sockaddr_in address;
	};
	PlayerData data;
public:
	void SetInput(int _input);
	void SetName(std::string _name);
	void SetStatusMessage(std::string _msg);
	void SetID(int _ID);
	void SetAddress(sockaddr_in _address);
	void SetClientStatus(CLIENT_STATUS status);
	void SetTurn(bool turn);
	inline int GetInput() { return data.input; };
	inline std::string GetName() { return data.name; };
	inline std::string GetStatusMessage() { return data.msg; };
	inline int GetID() { return data.ID; };
	inline sockaddr_in GetAddress() { return data.address; };
	inline CLIENT_STATUS GetClientStatus() { return data.clientStatus; };
	inline bool GetTurn() { return data.playerTurn; };
};

