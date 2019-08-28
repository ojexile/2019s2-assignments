#pragma once
#include <string>

class LogData
{
	friend class Logger;
private:
	int m_iNumCalls;
	std::string m_sLog;
	std::string m_sOptional;
public:
	LogData(std::string sLog, std::string sOptional);
	~LogData();
};
