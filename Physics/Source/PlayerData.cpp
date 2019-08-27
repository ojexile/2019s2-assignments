#include "PlayerData.h"
#include "AbilityDash.h"
#include "Resources.h"
#include <fstream>
PlayerData::PlayerData()
{
	m_SelectedAbility = new AbilityDash(3, 45);
	m_eAbility = eDASH;
	m_bAbilityDash = true;
	m_bAbilityGrenade = false;
	m_bAbilityHeal = false;
	m_bAbilitySlowTime = false;
	m_iCoins = 0;

	m_sUser = "DEBUG";
	m_sPass = "DEBUG";
}

PlayerData::~PlayerData()
{
	delete m_SelectedAbility;
}

void PlayerData::SetAbility(AbilityBase * a, eAbilities e)
{
	m_eAbility = e;
	if (m_SelectedAbility)
		delete m_SelectedAbility;
	m_SelectedAbility = a;
}

AbilityBase * PlayerData::GetAbility()
{
	return m_SelectedAbility;
}

int PlayerData::GetCoins()
{
	return m_iCoins;
}

void PlayerData::OffsetCoins(int i)
{
	m_iCoins += i;
}

bool PlayerData::GetAbilityActivated(eAbilities e)
{
	switch (e)
	{
	case eDASH:
		return m_bAbilityDash;
		break;
	case eGRENADE:
		return m_bAbilityGrenade;
		break;
	case eHEAL:
		return m_bAbilityHeal;
		break;
	case eSLOW_TIME:
		return m_bAbilitySlowTime;
		break;
	default:
		break;
	}
	return false;
}

PlayerData::eAbilities PlayerData::GetCurrentAbility()
{
	return m_eAbility;
}

void PlayerData::ActivateAbility(eAbilities e)
{
	switch (e)
	{
	case PlayerData::eDASH:
		m_bAbilityDash = true;
		break;
	case PlayerData::eGRENADE:
		m_bAbilityGrenade = true;
		break;
	case PlayerData::eHEAL:
		m_bAbilityHeal = true;
		break;
	case PlayerData::eSLOW_TIME:
		m_bAbilitySlowTime = true;
		break;
	default:
		break;
	}
}

void PlayerData::Save()
{
	std::string filePath = Resources::Path::SaveData + "/" + m_sUser + ".dat";
	std::ofstream File;
	File.open(filePath, std::ios::out);
	if (!File.is_open())
	{
		std::stringstream error;
		error << "Cannot open sav file.";
		DEFAULT_LOG(error.str());
		return;
	}
	File << "USER=" << m_sUser << '\n';
	File << "PASS=" << m_sPass << '\n';
	File << "COINS=" << m_iCoins << '\n';
	File << "DASH=" << m_bAbilityDash << '\n';
	File << "GRENADE=" << m_bAbilityGrenade << '\n';
	File << "HEAL=" << m_bAbilityHeal << '\n';
	File << "SLOWTIME=" << m_bAbilitySlowTime << '\n';
}

bool PlayerData::Create(std::string user, std::string pass)
{
	std::string filePath = Resources::Path::SaveData + "/" + user + ".dat";
	std::ifstream File;
	File.open(filePath);
	if (File.is_open())
	{
		// exists
		File.close();
		return false;
	}
	m_sUser = user;
	m_sPass = pass;
	Save();
	return true;
}

bool PlayerData::Load(std::string user, std::string pass)
{
	std::string filePath = Resources::Path::SaveData + user + ".dat";
	std::ifstream ifFile(filePath);
	if (!ifFile.is_open())
	{
		std::stringstream error;
		error << "Cannot open save file " << filePath << ".";
		DEFAULT_LOG(error.str());
		return false;
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

		if (sTerm == "PASS")
		{
			if (sVal != pass)
				return false;
		}
		if (sTerm == "COINS")
			m_iCoins = std::stoi(sVal);
		if (sTerm == "DASH")
			m_bAbilityDash = std::stoi(sVal);
		if (sTerm == "GRENADE")
			m_bAbilityGrenade = std::stoi(sVal);
		if (sTerm == "HEAL")
			m_bAbilityHeal = std::stoi(sVal);
		if (sTerm == "SLOWTIME")
			m_bAbilitySlowTime = std::stoi(sVal);
	}
	ifFile.close();
	m_sUser = user;
	m_sPass = pass;
	return true;
}

std::string PlayerData::GetUsername()
{
	return m_sUser;;
}