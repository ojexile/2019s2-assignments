#pragma once
#include "PartScript.h"

class WeaponPartScript : public PartScript
{
public:
	WeaponPartScript(SLOT_TYPE slot, double Multiplier, float durability);
	virtual ~WeaponPartScript();


	virtual ComponentBase* Clone() { return new WeaponPartScript(*this); }
	void Effect() override;

};

