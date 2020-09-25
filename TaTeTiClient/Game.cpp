#include "Game.h"

Game::Game()
{
	// Name you application
	sAppName = "TaTeTi Online";
	for (int i = 0; i < 9; i++)
	{
		ourDrawPos[i] = false;
		enemyDrawPos[i] = false;
	}
	slotX = 60;
	slotY = 60;
	ourSkin = 'O';
	enemySkin = 'X';
	gameStarted = true;
}

bool Game::OnUserCreate() 
{
	client = new Client(8900);
	client->Initialize();
	return true;
}

bool Game::OnUserUpdate(float fElapsedTime)
{
	// Erase previous frame
	Clear(olc::WHITE);
	client->ListenForMessages();
	if (gameStarted) {
		if (IsFocused())
		{
			if (GetKey(olc::Key::NP7).bPressed) {
				client->SendMSG();
				client->ListenForMessages();
				ourDrawPos[0] = true;
			}
			if (GetKey(olc::Key::NP8).bPressed) {
				client->SendMSG();
				client->ListenForMessages();
				ourDrawPos[1] = true;
			}
			if (GetKey(olc::Key::NP9).bPressed) {
				client->SendMSG();
				client->ListenForMessages();
				ourDrawPos[2] = true;
			}
			if (GetKey(olc::Key::NP4).bPressed) {
				client->SendMSG();
				client->ListenForMessages();
				ourDrawPos[3] = true;
			}
			if (GetKey(olc::Key::NP5).bPressed) {
				client->SendMSG();
				client->ListenForMessages();
				ourDrawPos[4] = true;
			}
			if (GetKey(olc::Key::NP6).bPressed) {
				client->SendMSG();
				client->ListenForMessages();
				ourDrawPos[5] = true;
			}
			if (GetKey(olc::Key::NP1).bPressed) {
				client->SendMSG();
				client->ListenForMessages();
				ourDrawPos[6] = true;
			}
			if (GetKey(olc::Key::NP2).bPressed) {
				client->SendMSG();
				client->ListenForMessages();
				ourDrawPos[7] = true;
			}
			if (GetKey(olc::Key::NP3).bPressed) {
				client->SendMSG();
				client->ListenForMessages();
				ourDrawPos[8] = true;
			}
		}
	DrawBoardState();
	DrawBoard();
		if (gameOver) 
		{
			//GameOver Screen
		}
	}
	DrawString(ScreenWidth() / 2 - 50, ScreenHeight() / 2 - 80, "TATETI ONLINE", olc::DARK_GREY);
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

void Game::DrawBoardState()
{	
	if (ourDrawPos[0] == true) {
		DrawString(slotX, slotY, ourSkin, olc::RED, 2);
	}
	if (ourDrawPos[1] == true) {
		DrawString(slotX + 33, slotY, ourSkin, olc::RED, 2);
	}
	if (ourDrawPos[2] == true) {
		DrawString(slotX + 68, slotY, ourSkin, olc::RED, 2);
	}
	if (ourDrawPos[3] == true) {
		DrawString(slotX, slotY + 33, ourSkin, olc::RED, 2);
	}
	if (ourDrawPos[4] == true) {
		DrawString(slotX + 33, slotY + 33, ourSkin, olc::RED, 2);
	}
	if (ourDrawPos[5] == true) {
		DrawString(slotX + 68, slotY + 33, ourSkin, olc::RED, 2);
	}
	if (ourDrawPos[6] == true) {
		DrawString(slotX, slotY + 68, ourSkin, olc::RED, 2);
	}
	if (ourDrawPos[7] == true) {
		DrawString(slotX + 33, slotY + 68, ourSkin, olc::RED, 2);
	}
	if (ourDrawPos[8] == true) {
		DrawString(slotX + 68, slotY + 68, ourSkin, olc::RED, 2);
	}

	if (enemyDrawPos[0] == true) {
		DrawString(slotX, slotY, enemySkin, olc::RED, 2);
	}
	if (enemyDrawPos[1] == true) {
		DrawString(slotX + 33, slotY, enemySkin, olc::RED, 2);
	}
	if (enemyDrawPos[2] == true) {
		DrawString(slotX + 68, slotY, enemySkin, olc::RED, 2);
	}
	if (enemyDrawPos[3] == true) {
		DrawString(slotX, slotY + 33, enemySkin, olc::RED, 2);
	}
	if (enemyDrawPos[4] == true) {
		DrawString(slotX + 33, slotY + 33, enemySkin, olc::RED, 2);
	}
	if (enemyDrawPos[5] == true) {
		DrawString(slotX + 68, slotY + 33, enemySkin, olc::RED, 2);
	}
	if (enemyDrawPos[6] == true) {
		DrawString(slotX, slotY + 68, enemySkin, olc::RED, 2);
	}
	if (enemyDrawPos[7] == true) {
		DrawString(slotX + 33, slotY + 68, enemySkin, olc::RED, 2);
	}
	if (enemyDrawPos[8] == true) {
		DrawString(slotX + 68, slotY + 68, enemySkin, olc::RED, 2);
	}
}

void Game::SetDrawPos(bool playerTurn,int pos)
{
	if (playerTurn)
		ourDrawPos[pos] = true;
	else
		enemyDrawPos[pos] = true;
}

void Game::GameOver(bool playerWon)
{
	if (playerWon)
		won = true;
	else
		won = false;
}

void Game::SetClientID(int _ID)
{
	ID = _ID;
}
