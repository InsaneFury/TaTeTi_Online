#include "NetworkServices.h"

int NetworkServices::SendMessage(SOCKET CurrentSocket, char* Message, int MessageSize)
{
	return send(CurrentSocket, Message, MessageSize, 0);
}

int NetworkServices::RecieveMessage(SOCKET CurrentSocket, char* Buffer, int BufferSize)
{
	return recv(CurrentSocket, Buffer, BufferSize, 0);
}