#include "Game.h"

Game::Game()
{
	// Name you application
	sAppName = "TaTeTi Online";
}

bool Game::OnUserCreate() 
{
	// Called once at the start, so create things here
	client = new Client(8900);
	client->Initialize();
	return true;
}

bool Game::OnUserUpdate(float fElapsedTime)
{
	// Erase previous frame
	Clear(olc::WHITE);
	DrawBoard();
	return true;
}

bool Game::OnUserDestroy()
{
	// Called when window is closed
	client->Shutdown();
	delete client;
	return true;
}

void Game::DrawBoard()
{
	int border = 150;
	//Bottom Line
	DrawLine(border, border, ScreenWidth() - border, border, olc::DARK_GREY);
	//Top Line
	DrawLine(border, ScreenHeight() - border, ScreenWidth() - border, ScreenHeight() - border, olc::DARK_GREY);
	//Right Line
	DrawLine(border, border, border, ScreenHeight() - border, olc::DARK_GREY);
	//Left Line
	DrawLine(ScreenWidth() - border, border, ScreenWidth() - border, ScreenHeight() - border, olc::DARK_GREY);

	int inside = 160;
	int insideOffset = 10;
	int verticalOffset = -43;
	int horizontalOffset = -42;
	//Bottom Line
	DrawLine(inside - insideOffset, inside + verticalOffset, ScreenWidth() - inside + insideOffset, inside + verticalOffset, olc::DARK_GREY);
	//Top Line
	DrawLine(inside - insideOffset, ScreenHeight() - inside - verticalOffset, ScreenWidth() - inside + insideOffset, ScreenHeight() - inside - verticalOffset, olc::DARK_GREY);
	//Right Line
	DrawLine(inside + horizontalOffset, inside - insideOffset, inside + horizontalOffset, ScreenHeight() - inside + insideOffset, olc::DARK_GREY);
	//Left Line
	DrawLine(ScreenWidth() - inside - horizontalOffset, inside - insideOffset, ScreenWidth() - inside - horizontalOffset, ScreenHeight() - inside + insideOffset, olc::DARK_GREY);
}
