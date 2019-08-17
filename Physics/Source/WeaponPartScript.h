#pragma once
#include "PartScript.h"
class WeaponPartScript : public PartScript
{
public:
	WeaponPartScript(SLOT_TYPE slot, float Multiplier, float durability, bool isAttached = false);
	virtual ~WeaponPartScript();

	virtual Component* Clone() { return new WeaponPartScript(*this); }
	void Effect() override;
};
