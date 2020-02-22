#pragma once
#include <WinSock2.h>
#include <string.h>

struct user
{
	SOCKET s;
	std::string name;
	bool afk;

	user(SOCKET sd)
		: s(sd), 
		name("NEWUSER"),
		afk(false)
	{
	}

};