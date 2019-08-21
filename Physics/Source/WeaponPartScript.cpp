#include "WeaponPartScript.h"



WeaponPartScript::WeaponPartScript(SLOT_TYPE slot, float Multiplier, float durability)
	:m_SlotType(slot),
	m_fStatMultiplier(Multiplier),
	m_fDurability(durability)
{
}


WeaponPartScript::~WeaponPartScript()
{
}


bool WeaponPartScript::DecreaseDurability(double deltaTime)
{
	double multiplier = 10.0;
	m_fDurability = m_fDurability - deltaTime * multiplier;
	return m_fDurability <= 0.f;
}

void WeaponPartScript::SetSlotType(WeaponPartScript::SLOT_TYPE slot)
{
	m_SlotType = slot;
}


WeaponPartScript::SLOT_TYPE WeaponPartScript::GetSlotType()
{
	return m_SlotType;
}

float WeaponPartScript::GetMultiplier()
{
	return m_fStatMultiplier;
}

void WeaponPartScript::SetDurability(float durability)
{
	m_fDurability = durability;
}

void WeaponPartScript::SetMultiplier(float multiplier)
{
	m_fStatMultiplier = multiplier;
}