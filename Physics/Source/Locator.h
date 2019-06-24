#pragma once
#include "Logger.h"



class Locator
{
public:
	enum eLoggerUsers
	{
		DEFAULT,
		CHENG,
		NOT_CHENG,
	};
private:
	static Logger DefaultLogger;
	static Logger ChengLogger;
	static Logger NotChengLogger;
public:
	Locator();
	~Locator();

	static Logger& GetLogger(eLoggerUsers user);
};

