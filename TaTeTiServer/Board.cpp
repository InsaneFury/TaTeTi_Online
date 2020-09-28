#include "Board.h"

Board::Board()
{
	ResetBoard();
}

bool Board::SetPlayerMove(int move, int playerSkin)
{
	switch (move)
	{
	case 1:
		if(gameBoard[2][0] == 0)
		{
			gameBoard[2][0] = playerSkin;
			return true;
		}
		return false;
		break;
	case 2:
		if (gameBoard[2][1] == 0)
		{
			gameBoard[2][1] = playerSkin;
			return true;
		}
		return false;
		break;
	case 3:
		if (gameBoard[2][2] == 0)
		{
			gameBoard[2][2] = playerSkin;
			return true;
		}
		return false;
		break;
	case 4:
		if (gameBoard[1][0] == 0)
		{
			gameBoard[1][0] = playerSkin;
			return true;
		}
		return false;
		break;
	case 5:
		if (gameBoard[1][1] == 0)
		{
			gameBoard[1][1] = playerSkin;
			return true;
		}
		return false;
		break;
	case 6:
		if (gameBoard[1][2] == 0)
		{
			gameBoard[1][2] = playerSkin;
			return true;
		}
		return false;
		break;
	case 7:
		if (gameBoard[0][0] == 0)
		{
			gameBoard[0][0] = playerSkin;
			return true;
		}
		return false;
		break;
	case 8:
		if (gameBoard[0][1] == 0)
		{
			gameBoard[0][1] = playerSkin;
			return true;
		}
		return false;
		break;
	case 9:
		if (gameBoard[0][2] == 0)
		{
			gameBoard[0][2] = playerSkin;
			return true;
		}
		return false;
		break;
	default:
		return false;
		break;
	}
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
