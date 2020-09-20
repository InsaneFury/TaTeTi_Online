#pragma once
#define _WINSOCKAPI_
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Client.h"

class Game : public olc::PixelGameEngine
{
private:
	Client* client;
public:
	Game();
public:
	bool OnUserCreate() override;	
	bool OnUserUpdate(float fElapsedTime) override;
	bool OnUserDestroy() override;

	//TaTeTi
	void DrawBoard();
};

