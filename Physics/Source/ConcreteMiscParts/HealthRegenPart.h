#pragma once
#include "../MiscellaneousPartScript.h"
class HealthRegenPart : public MiscellaneousPartScript
{
public:
	HealthRegenPart(float SpreadDebuff, float FireRateDebuff, int MaxMagazineDebuff, int MaxAmmoDebuff, float durability);
	virtual ~HealthRegenPart();

	virtual Component* Clone() { return new HealthRegenPart(*this); }

	void Buff(bool reverse) override;
	void Debuff(bool reverse) override;

	void Effect() override;
	void RevertEffect() override;

};

