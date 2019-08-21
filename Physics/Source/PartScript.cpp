#include "PartScript.h"



PartScript::PartScript(PART_TYPE type, SLOT_TYPE slot, float Multiplier, float durability) 
	:m_PartType (type),
	 m_SlotType (slot),
	 m_fStatMultiplier(Multiplier),
	 m_fDurability(durability)
{
}


PartScript::~PartScript()
{
}


bool PartScript::DecreaseDurability(double deltaTime)
{
	double multiplier = 10.0;
	m_fDurability = m_fDurability - deltaTime * multiplier;
	return m_fDurability <= 0.f;
}

void PartScript::SetSlotType(PartScript::SLOT_TYPE slot)
{
	m_SlotType = slot;
}

PartScript::PART_TYPE PartScript::GetPartType()
{
	return m_PartType;
}

PartScript::SLOT_TYPE PartScript::GetSlotType()
{
	return m_SlotType;
}

float PartScript::GetMultiplier()
{
	return m_fStatMultiplier;
}

void PartScript::SetDurability(float durability)
{
	m_fDurability = durability;
}

void PartScript::SetMultiplier(float multiplier)
{
	m_fStatMultiplier = multiplier;
}