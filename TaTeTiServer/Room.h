#pragma once
#include "Board.h"
#include "Player.h"

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
	Board board;
public:

};

