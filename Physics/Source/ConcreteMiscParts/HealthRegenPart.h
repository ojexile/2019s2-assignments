#pragma once
#include "../MiscellaneousPartScript.h"
class HealthRegenPart : public MiscellaneousPartScript
{
public:
	HealthRegenPart(SLOT_TYPE slot, double Multiplier, float durability);
	virtual ~HealthRegenPart();

	void Buff();
	void Debuff();

	void Effect();

};

