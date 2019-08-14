#include "PartScript.h"



PartScript::PartScript(PART_TYPE type, SLOT_TYPE slot, double Multiplier, bool isAttached, float durability) 
	:m_partType (type),
	 m_slotType (slot),
	 m_fStatMultiplier(Multiplier),
	 m_isAttached (isAttached),
	 m_fDurability(durability)
{
}


PartScript::~PartScript()
{
}


bool PartScript::DecreaseDurability(double deltaTime)
{
	m_fDurability = m_fDurability - 0.1;
	return m_fDurability <= 0.f;
}

PartScript::PART_TYPE PartScript::GetPartType()
{
	return m_partType;
}

PartScript::SLOT_TYPE PartScript::GetSlotType()
{
	return m_slotType;
}

float PartScript::GetMultiplier()
{
	return m_fStatMultiplier;
}