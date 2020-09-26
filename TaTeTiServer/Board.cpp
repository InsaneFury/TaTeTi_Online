#include "Board.h"

Board::Board()
{
	ResetBoard();
}

bool Board::SetPlayerMove(int x, int y, int playerTurn)
{
	if (gameBoard[x][y] == 0)
	{
		gameBoard[x][y] = playerTurn;
		return true;
	}
	return false;
}

void Board::ResetBoard()
{
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			gameBoard[x][y] = 0;
		}
	}
}
