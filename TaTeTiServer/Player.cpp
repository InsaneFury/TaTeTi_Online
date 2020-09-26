#include "Player.h"

void Player::SetInput(int _input)
{
	data.input = _input;
}

void Player::SetName(std::string _name)
{
	data.name = _name;
}

void Player::SetGameState(std::string _gameState)
{
	data.gameState = _gameState;
}

void Player::SetID(int _ID)
{
	data.ID = _ID;
}

void Player::SetAddress(sockaddr_in _address)
{
	data.address = _address;
}
