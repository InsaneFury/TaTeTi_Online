#include "Room.h"

Room::Room(Player one, Player two)
	:
	playerOne(one),
	playerTwo(two),
	board(new Board())
{
}

Room::~Room()
{
	delete board;
}

void Room::StartGame()
{

}

