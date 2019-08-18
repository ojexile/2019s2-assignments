#pragma once
#include "../MiscellaneousPartScript.h"

class StaminaRegenPart : public MiscellaneousPartScript
{
public:
	StaminaRegenPart(float SpreadDebuff, float FireRateDebuff, int MaxMagazineDebuff, int MaxAmmoDebuff, float durability);
	virtual ~StaminaRegenPart();

	virtual Component* Clone() { return new StaminaRegenPart(*this); }

	void Buff(bool reverse) override;
	void Debuff(bool reverse) override;

	void Effect() override;
	void RevertEffect() override;
};

