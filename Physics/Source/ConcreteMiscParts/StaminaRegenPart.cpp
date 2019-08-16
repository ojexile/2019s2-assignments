#include "StaminaRegenPart.h"



StaminaRegenPart::StaminaRegenPart(SLOT_TYPE slot, double Multiplier, float durability)
	: MiscellaneousPartScript(slot, Multiplier, durability)
{
}


StaminaRegenPart::~StaminaRegenPart()
{
}


void StaminaRegenPart::Effect()
{
	Buff();
	Debuff();
}

void StaminaRegenPart::Buff()
{
	switch (m_BuffedStat)
	{
	default:
	{
		break;
	}
	}
}

void StaminaRegenPart::Debuff()
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