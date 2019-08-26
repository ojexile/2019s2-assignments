#include "PlayerData.h"
#include "AbilityDash.h"
PlayerData::PlayerData()
{
	m_SelectedAbility = new AbilityDash(3, 45);
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