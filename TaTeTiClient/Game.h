#pragma once
#define _WINSOCKAPI_
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Client.h"
#include <string.h>

class Game : public olc::PixelGameEngine
{
private:
	Client* client;
	bool ourDrawPos[9];
	bool enemyDrawPos[9];
	int slotPos[3][3];
	int slotX;
	int slotY;
	std::string ourSkin;
	std::string enemySkin;
private:
	//TaTeTi
	void DrawBoard();
	void DrawBoardState();

public:
	Game();
public:
	bool OnUserCreate() override;	
	bool OnUserUpdate(float fElapsedTime) override;
	bool OnUserDestroy() override;

	void SetDrawPos(bool playerTurn,int pos);
};

