#include "Preferences.h"
#include "Resources.h"

std::map<std::string, std::string> Preferences::m_map_Data;
bool Preferences::m_bInitialsed = false;
Preferences::Preferences()
{
}

Preferences::~Preferences()
{
}
void Preferences::Clear()
{
	m_map_Data.clear();
}
void Preferences::InitDefault()
{
	// Defualt data
	m_map_Data[Resources::PreferencesTerm::WindowSize] = "1280,720";
	m_map_Data[Resources::PreferencesTerm::ConsoleSize] = "1900,320";
	m_map_Data[Resources::PreferencesTerm::WindowPosition] = "320,10";
	m_map_Data[Resources::PreferencesTerm::ConsolePosition] = "20,720";
	m_map_Data[Resources::PreferencesTerm::FontSize] = "12,22";
	m_map_Data[Resources::PreferencesTerm::AudioVolume] = "0.1";
	m_map_Data[Resources::PreferencesTerm::LogUpdateRate] = "1";
	m_map_Data[Resources::PreferencesTerm::Quality] = "LOW";
	m_map_Data[Resources::PreferencesTerm::LogUser] = "ALL";
	m_map_Data[Resources::PreferencesTerm::CamDist] = "30";

	GetData();
}
void Preferences::GetData()
{
	std::string filePath = Resources::Path::Preferences;
	std::ifstream ifFile(filePath);
	if (!ifFile.is_open())
	{
		std::stringstream error;
		error << "Cannot open preferences file, using default sizing. Create file at " << filePath << ".";
		DEFAULT_LOG(error.str());
		return;
	}
	std::string sLine;
	while (getline(ifFile, sLine))
	{
		for (unsigned i = 0; i < sLine.size(); ++i)
		{
			if (sLine[i] == ' ' || sLine[i] == '	')
			{
				sLine.erase(i, 1);
				--i;
			}
		}
		if (sLine[0] == '#' || sLine == "")
			continue;
		std::string sTerm = sLine.substr(0, sLine.find("=", 0));
		std::string sVal = sLine.substr(sLine.find("=", 0) + 1);

		if (m_map_Data.count(sTerm) <= 0)
			DEFAULT_LOG("Unknown preference term: " + sTerm);
		m_map_Data[sTerm] = sVal;
	}
}

std::string Preferences::GetPref(std::string s)
{
	if (!m_bInitialsed)
	{
		InitDefault();
		m_bInitialsed = true;
	}
	if (m_map_Data.count(s) <= 0)
	{
		DEFAULT_LOG("Pref not found: " + s);
		return "";
	}
	else
	{
		return m_map_Data[s];
	}
}
void Preferences::SetPref(std::string sTerm, std::string sVal)
{
	if (m_map_Data.count(sTerm) <= 0)
		DEFAULT_LOG("Unknown preference term: " + sTerm);
	m_map_Data[sTerm] = sVal;
}