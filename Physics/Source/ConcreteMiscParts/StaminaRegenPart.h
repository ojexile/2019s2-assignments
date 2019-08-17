#pragma once
#include "../MiscellaneousPartScript.h"

class StaminaRegenPart : public MiscellaneousPartScript
{
public:
	StaminaRegenPart(double Multiplier, float durability);
	virtual ~StaminaRegenPart();

	void Buff(bool reverse);
	void Debuff(bool reverse);

	void Effect();
	void ReverseEffect();
};

