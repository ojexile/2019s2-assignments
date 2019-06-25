#pragma once
#include "Logger.h"

#define CHENG_LOG(sLog)			Locator::ChengLogger.Log(sLog +" at " __FUNCTION__ + " " __FILE__)
#define DEFAULT_LOG(sLog)		Locator::DefaultLogger.Log(sLog +" at " __FUNCTION__ + " " __FILE__)

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
public:
	static Logger DefaultLogger;
	static Logger ChengLogger;
	static Logger NotChengLogger;
	Locator();
	~Locator();

	static Logger& GetLogger(eLoggerUsers user);
};
