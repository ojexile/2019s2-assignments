#include "PlayerData.h"
#include "AbilityDash.h"
PlayerData::PlayerData()
{
	m_SelectedAbility = new AbilityDash(3, 45);
	m_bAbility0 = true;
	m_bAbility1 = false;
	m_iCoins = 5;
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

bool PlayerData::GetGetAbilityActivated(int i)
{
	switch (i)
	{
	case 0:
		return m_bAbility0;
		break;
	case 1:
		return m_bAbility1;
		break;
	default:
		break;
	}
	return false;
}