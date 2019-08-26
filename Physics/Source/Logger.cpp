#include "Logger.h"
#include "Utility.h"
#include "Resources.h"

#define LOG_ENABLED true

Logger::Logger(std::string sUser, SHORT Color)
	: m_sUser(sUser)
	, m_Color(Color)
{
}

Logger::~Logger()
{
}

void Logger::Log(std::string s, std::string sOptional)
{
	if (!LOG_ENABLED)
		return;
	// Remove endline
	for (unsigned i = 0; i < s.size(); ++i)
	{
		if (s[i] == '\n')
		{
			s[i] = ' ';
		}
	}
	for (unsigned i = 0; i < sOptional.size(); ++i)
	{
		if (sOptional[i] == '\n')
		{
			sOptional[i] = ' ';
		}
	}
	// check if exists
	for (unsigned i = 0; i < m_vec_LogList.size(); i++)
	{
		if (m_vec_LogList[i].m_sLog == s)
		{
			++m_vec_LogList[i].m_iNumCalls;
			m_vec_LogList[i].m_sOptional = sOptional;
			return;
		}
	}
	m_vec_LogList.push_back(LogData(s, sOptional));
}

void Logger::PrintLogs()
{
	// Logger print speed is limited due to reading preference through GetPref
	// Preference stores data in a map
	for (unsigned i = 0; i < m_vec_LogList.size(); ++i)
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		// Name Color
		SetConsoleTextAttribute(handle, m_Color);

		std::cout << '[' + m_sUser + ']' + "    ";
		if (m_sUser.size() <= 6)
			std::cout << ' ';

		LogData log = m_vec_LogList[i];
		Vector3 ConsoleSize = StringToVector(Preferences::GetPref(Resources::PreferencesTerm::ConsoleSize));
		Vector3 FontSize = StringToVector(Preferences::GetPref(Resources::PreferencesTerm::FontSize));
		const int WINDOW_LENGTH = (int)ConsoleSize.x;
		const int WINDOW_CHAR_LENGTH = WINDOW_LENGTH / (int)FontSize.x;
		std::stringstream ss;
		ss << log.m_iNumCalls << "  " << log.m_sLog << log.m_sOptional;

		// Print
		SetConsoleTextAttribute(handle, 0x0F);
		std::cout << ss.str() << '\n';
	}
}