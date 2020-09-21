#pragma once
#define _WINSOCKAPI_
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Client.h"
#include <string.h>

class Game : public olc::PixelGameEngine
{
private:
	//Networking
	Client* client;

	//Game
	bool ourDrawPos[9];
	bool enemyDrawPos[9];
	bool gameStarted;
	bool gameOver;
	bool won;
	int slotPos[3][3];
	int slotX;
	int slotY;
	std::string ourSkin;
	std::string enemySkin;

	//Client info
	std::string name;
	int ID;
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

	//Game
	void SetDrawPos(bool playerTurn,int pos);
	void GameOver(bool playerWon);

	//Client info
	void SetClientID(int _ID);
	inline int GetClientID() { return ID; }
	inline std::string GetClientName() { return name; }

};

