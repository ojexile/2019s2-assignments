#include "LogData.h"

LogData::LogData(std::string sLog, std::string sOptional)
{
	m_iNumCalls = 1;
	m_sLog = sLog;
	m_sOptional = sOptional;
}

LogData::~LogData()
{
}