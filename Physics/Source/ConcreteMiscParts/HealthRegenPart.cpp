#include "HealthRegenPart.h"



HealthRegenPart::HealthRegenPart(float SpreadDebuff, float FireRateDebuff, int MaxMagazineDebuff, int MaxAmmoDebuff, float durability)
	: MiscellaneousPartScript(SpreadDebuff, FireRateDebuff, MaxMagazineDebuff, MaxAmmoDebuff, durability)
{
}


HealthRegenPart::~HealthRegenPart()
{
}


void HealthRegenPart::Effect()
{
	Buff(false);
	Debuff(false);
}

void HealthRegenPart::RevertEffect()
{
	Buff(true);
	Debuff(true);
}


void HealthRegenPart::Buff(bool reverse)
{
	//switch (m_BuffedStat)
	//{
	//default:
	//{
	//	break;
	//}
	//}
}

void HealthRegenPart::Debuff(bool reverse)
{
	switch (m_SlotType)
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