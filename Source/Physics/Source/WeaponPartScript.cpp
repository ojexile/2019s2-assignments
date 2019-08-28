#include "WeaponPartScript.h"

WeaponPartScript::WeaponPartScript(SLOT_TYPE slot, float Multiplier, float durability, Augment* augment)
	:m_SlotType(slot),
	m_fStatMultiplier(Multiplier),
	m_fDurability(durability),
	m_Augment(augment)
{
	switch (slot)
	{
	case SCOPE:
		m_Name = "Scope";
		m_Description = "Reduces Bullet spread by " + std::to_string(1 - m_fStatMultiplier) + "\n";
		break;
	case CLIP:
		m_Name = "Clip";
		m_Description = "Increases clip size by " + std::to_string(m_fStatMultiplier) + "\n";
		break;
	case GRIP:
		m_Name = "Grip";
		m_Description = "Reduces Bullet spread by " + std::to_string(1 - m_fStatMultiplier) + "\n";
		break;
	case MUZZLE:
		m_Name = "Muzzle";
		m_Description = "Increases fire rate by " + std::to_string(1 - m_fStatMultiplier) + "\n";
		break;
	}
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
	m_fDurability = m_fDurability - (float)deltaTime * (float)multiplier;
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

void WeaponPartScript::SetName(std::string s)
{
	m_Name = s;
}

std::string WeaponPartScript::GetName(void)
{
	return m_Name;
}

void WeaponPartScript::SetDescription(std::string s)
{
	m_Description = s;
}

std::string WeaponPartScript::GetDescription(void)
{
	return m_Description;
}
