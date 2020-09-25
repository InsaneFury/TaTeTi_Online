#pragma once
#include <iostream>

class Player
{
private:
	struct PlayerData
	{
		int input = 0;
		std::string name = "";
		std::string gameState = "";
		int ID = 0;
		bool playerTurn = true;
	};
	PlayerData data;
public:
	void SetInput(int _input);
	void SetName(std::string _name);
	void SetGameState(std::string _gameState);
	void SetID(int _ID);
	inline int GetInput() { return data.input; };
	inline std::string GetName() { return data.name; };
	inline std::string GetGameState() { return data.gameState; };
	inline int GetID() { return data.ID; };
};

