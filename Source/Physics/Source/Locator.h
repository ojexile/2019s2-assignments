#pragma once
#include "Logger.h"
#include <string>

#define TRUNC_FILE_PATH(PATH)	std::string(PATH).substr(std::string(PATH).find_last_of("\\") + 1)

#define LOG(...)				.Log(__VA_ARGS__ + std::string("----")\
+ std::string(__FUNCTION__) + std::string(" in ")\
+ TRUNC_FILE_PATH(__FILE__) + "-" + std::to_string(__LINE__))

#define CHENG_LOG(...)			Locator::ChengLogger LOG(__VA_ARGS__)
#define DEFAULT_LOG(...)		Locator::DefaultLogger LOG(__VA_ARGS__)
#define RYAN_LOG(...)			Locator::RyanLogger LOG(__VA_ARGS__)
#define KZ_LOG(...)				Locator::KZLogger LOG(__VA_ARGS__)
#define LZ_LOG(...)				Locator::LZLogger LOG(__VA_ARGS__)

class Locator
{
public:
	enum eLoggerUsers
	{
		DEFAULT,
		CHENG,
		RYAN,
		KZ,
		LZ,
		ALL,
	};
private:
public:
	static Logger DefaultLogger;
	static Logger ChengLogger;
	static Logger RyanLogger;
	static Logger KZLogger;
	static Logger LZLogger;
	Locator();
	~Locator();

	static Logger& GetLogger(eLoggerUsers user);
};
