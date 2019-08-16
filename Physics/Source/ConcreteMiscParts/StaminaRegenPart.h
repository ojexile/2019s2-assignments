#pragma once
#include "../MiscellaneousPartScript.h"
class StaminaRegenPart : public MiscellaneousPartScript
{
public:
	StaminaRegenPart(SLOT_TYPE slot, double Multiplier, float durability);
	virtual ~StaminaRegenPart();

	void Buff();
	void Debuff();

	void Effect();
};

