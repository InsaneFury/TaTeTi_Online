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

bool Board::CheckPlayerWin()
{
	//check Rows and Columns
	for (int i = 0; i < 3; i++)
	{
		if (gameBoard[i][0] == gameBoard[i][1] && gameBoard[i][0] == gameBoard[i][2] || 
			gameBoard[0][i] == gameBoard[1][i] && gameBoard[0][i] == gameBoard[2][i]) 
		{
			return true;
		}
	}

	//check diagonals
	bool diagonal1 = gameBoard[0][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][2];
	bool diagonal2 = gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0];
	if (diagonal1 || diagonal2) { return true; }

	return false;
}

bool Board::IsFilled()
{
	//Check filled
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (gameBoard[i][j] == 0)
				return false;
		}
	}
	return true;
}
