#include "HealthRegenPart.h"



HealthRegenPart::HealthRegenPart(SLOT_TYPE slot, double Multiplier, float durability)
	: MiscellaneousPartScript(slot, Multiplier, durability)
{
}


HealthRegenPart::~HealthRegenPart()
{
}


void HealthRegenPart::Effect()
{
	Buff();
	Debuff();
}

void HealthRegenPart::Buff()
{
	switch (m_BuffedStat)
	{
	default:
	{
		break;
	}
	}
}

void HealthRegenPart::Debuff()
{
	switch (m_AttachedSlotType)
	{
	case PartScript::SCOPE:
	{
		break;
	}
	case PartScript::MUZZLE:
	{
		break;
	}
	case PartScript::CLIP:
	{
		break;
	}
	case PartScript::GRIP:
	{
		break;
	}
	default:
	{
		break;
	}
	}
}