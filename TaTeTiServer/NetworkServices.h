#pragma once
#include "winsock2.h"
class NetworkServices
{
public:

	static int SendMessage(SOCKET CurrentSocket, char* Message, int MessageSize);
	static int RecieveMessage(SOCKET CurrentSocket, char* Buffer, int BufferSize);
};

