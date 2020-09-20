#define OLC_PGE_APPLICATION
#include "Client.h"
#include "olcPixelGameEngine.h"
namespace GameSpace {

class Game : public olc::PixelGameEngine
{
public:
	Game()
	{
		// Name you application
		sAppName = "TaTeTi Online";
	}


public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame, draws random coloured pixels
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
		return true;
	}

};
}

void main()
{
	//Client* client = new Client(8900);

	//client->Initialize();

	GameSpace::Game demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();
	//client->Shutdown();

	//delete client;
}