#pragma once

class Board
{
private:
	int gameBoard[3][3];
public:
	Board();
	bool SetPlayerMove(int x, int y,int playerTurn);
	void ResetBoard();
	inline int GetDataFrom(int x, int y) { return gameBoard[x][y]; };
	bool CheckPlayerWin();
	bool IsFilled();
};

