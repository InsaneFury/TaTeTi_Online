#include "Player.h"

void Player::SetInput(int _input)
{
	data.input = _input;
}

void Player::SetName(std::string _name)
{
	data.name = _name;
}

void Player::SetStatusMessage(std::string _msg)
{
	data.msg = _msg;
}

void Player::SetID(int _ID)
{
	data.ID = _ID;
}

void Player::SetAddress(sockaddr_in _address)
{
	data.address = _address;
}

void Player::SetClientStatus(CLIENT_STATUS status)
{
	data.clientStatus = status;
}
