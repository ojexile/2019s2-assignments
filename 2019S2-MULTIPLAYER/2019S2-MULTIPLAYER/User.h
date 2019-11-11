#pragma once
#include <WinSock2.h>

struct user
{
	SOCKET s;

	user(SOCKET sd)
		: s(sd)
	{
	}
};