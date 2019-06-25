#include "WindowData.h"

WindowData::WindowData()
{
	// Defualt data
	m_vWindowSize = { 1280,720 };
	m_vConsoleSize = { 1280, 1000 };
	m_vWindowPosition = { 0, 80 };
	m_vConsolePosition = { 1280, 50 };
	m_vFontSize = { 8,16 };

	GetData();
}

WindowData::~WindowData()
{
}
// converts string of format "x,y" into a vector3
Vector3 StringToVector(std::string s)
{
	std::string sX = s.substr(0, s.find(",", 0));
	std::string sY = s.substr(s.find(",", 0) + 1);

	return	Vector3((float)std::stoi(sX), (float)std::stoi(sY));
}
void WindowData::GetData()
{
	std::ifstream ifFile(FILE_PATH);
	if (!ifFile.is_open())
	{
		std::stringstream error;
		error << "Cannot open windowData file, using default sizing. Create file at " << FILE_PATH << ".";
		DEFAULT_LOG(error.str());
		return;
	}
	std::string sLine;
	while (getline(ifFile, sLine))
	{
		for (unsigned i = 0; i < sLine.size(); ++i)
		{
			if (sLine[i] == ' ')
			{
				sLine.erase(i);
				--i;
			}
		}
		std::string sTerm = sLine.substr(0, sLine.find("=", 0));
		std::string sVal = sLine.substr(sLine.find("=", 0) + 1);
		Vector3 pos = StringToVector(sVal);

		if (sTerm == "windowSize")
		{
			m_vWindowSize = pos;
		}
		else if (sTerm == "windowPosition")
		{
			m_vWindowPosition = pos;
		}
		else if (sTerm == "consoleSize")
		{
			m_vConsoleSize = pos;
		}
		else if (sTerm == "consolePosition")
		{
			m_vConsolePosition = pos;
		}
		else if (sTerm == "fontSize")
		{
			m_vFontSize = pos;
		}
		else
		{
			DEFAULT_LOG("Unknown term in windowData file");
		}
	}
}

Vector3 WindowData::GetWindowSize()
{
	return m_vWindowSize;
}
Vector3 WindowData::GetConsoleSize()
{
	return m_vConsoleSize;
}
Vector3 WindowData::GetConsolePosition()
{
	return m_vConsolePosition;
}
Vector3 WindowData::GetWindowPosition()
{
	return m_vWindowPosition;
}
Vector3 WindowData::GetFontSize()
{
	return m_vFontSize;
}