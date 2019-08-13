#pragma once
#include "PartScript.h"
class WeaponPartScript : public PartScript
{
public:
	WeaponPartScript(SLOT_TYPE slot, float Effect, float durability, bool isAttached = false);
	virtual ~WeaponPartScript();

	void Effect() override;

};

