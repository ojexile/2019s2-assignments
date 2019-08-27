#include "PlayerData.h"
#include "AbilityDash.h"
#include "Resources.h"
#include <fstream>
PlayerData::PlayerData()
{
	m_SelectedAbility = new AbilityDash(3, 45);
	m_bAbilityDash = true;
	m_bAbilityGrenade = false;
	m_iCoins = 5;

	m_sUser = "Cheng";
	m_sPass = "69";
}

PlayerData::~PlayerData()
{
	delete m_SelectedAbility;
}

void PlayerData::SetAbility(AbilityBase * a)
{
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

bool PlayerData::GetGetAbilityActivated(eAbilities e)
{
	switch (e)
	{
	case eDASH:
		return m_bAbilityDash;
		break;
	case eGRENADE:
		return m_bAbilityGrenade;
		break;
	default:
		break;
	}
	return false;
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
	}
	ifFile.close();
	return true;
}