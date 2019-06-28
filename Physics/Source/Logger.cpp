#include "Logger.h"

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

int Logger::PrintLogs(int iYOffset)
{
	for (unsigned i = 0; i < m_vec_LogList.size(); ++i)
	{
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

		COORD coord;
		coord.X = 0;
		coord.Y = i + 1 + iYOffset;
		SetConsoleCursorPosition(handle, coord);

		// Name Color
		SetConsoleTextAttribute(handle, m_Color);
		std::cout << '[' + m_sUser + ']' + '	';
		if (m_sUser.size() <= 6)
			std::cout << '	';

		LogData log = m_vec_LogList[i];
		WindowData* WinData = WindowData::GetInstance();
		const int WINDOW_LENGTH = (int)WinData->GetConsoleSize().x;
		const int WINDOW_CHAR_LENGTH = WINDOW_LENGTH / (int)WinData->GetFontSize().x;
		iYOffset += log.m_sLog.size() / WINDOW_CHAR_LENGTH;

		// Print
		SetConsoleTextAttribute(handle, 0x0F);
		std::cout << log.m_iNumCalls << "  " << log.m_sLog << log.m_sOptional << '\n';

		SetConsoleTextAttribute(handle, 0x0F);
		++iYOffset;
	}
	return iYOffset;
}