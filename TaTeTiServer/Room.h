#pragma once
#include "Board.h"
#include "../TaTeTiClient/Player.h"

enum PlayerTurn
{
	PLAYER_ONE = 1,
	PLAYER_TWO
};

class Room
{
private:
	Player playerOne;
	Player playerTwo;
	Board* board;
public:
	Room(Player one, Player two);
	~Room();

	void StartGame();
};

