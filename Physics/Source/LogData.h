#pragma once
#include <string>


class LogData
{
	friend class Logger;
private:
	int m_iNumCalls;
	std::string m_sLog;
	
public:
	LogData(std::string sLog);
	~LogData();
};

