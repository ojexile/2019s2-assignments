#include "PlayerData.h"
#include "AbilityDash.h"
PlayerData::PlayerData()
{
	m_SelectedAbility = new AbilityDash(3, 45);
	m_bAbilityDash = true;
	m_bAbilityGrenade = false;
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