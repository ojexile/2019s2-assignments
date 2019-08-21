#include "WeaponPartScript.h"



WeaponPartScript::WeaponPartScript(SLOT_TYPE slot, float Multiplier, float durability, Augment* augment)
	:m_SlotType(slot),
	m_fStatMultiplier(Multiplier),
	m_fDurability(durability),
	m_Augment(augment)
{
}


WeaponPartScript::~WeaponPartScript()
{
	if (m_Augment)
	{
		delete m_Augment;
		m_Augment = nullptr;
	}
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

Augment* WeaponPartScript::GetAugment()
{
	return m_Augment;
}

void WeaponPartScript::SetDurability(float durability)
{
	m_fDurability = durability;
}

void WeaponPartScript::SetMultiplier(float multiplier)
{
	m_fStatMultiplier = multiplier;
}

void WeaponPartScript::SetAugment(Augment* augment)
{
	m_Augment = augment;
}