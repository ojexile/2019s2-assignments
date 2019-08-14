#pragma once
#include "ScriptComponent.h"

/********************************************************************************
Author: Ryan Tan Zheng Rong
Brief: Base Script for weapon parts that can be attached to the weapon
	   etc.
********************************************************************************/

class PartScript : public ScriptComponent
{
public:

	enum PART_TYPE
	{
		WEAPON,
		MISC
	};

	enum SLOT_TYPE
	{
		SCOPE,
		STOCK,
		GRIP,
		MUZZLE,
		ALL
	};

	PartScript(PART_TYPE type, SLOT_TYPE slot, double Multiplier, bool isAttached = false, float Durability = 5.f);
	~PartScript();

	virtual void Effect() = 0;
	virtual bool DecreaseDurability(double deltaTime);

	PART_TYPE GetPartType();
	SLOT_TYPE GetSlotType();

	float GetMultiplier();

private:
	PART_TYPE m_partType;
	SLOT_TYPE m_slotType;

	bool m_isAttached;

	float m_fDurability;
	float m_fStatMultiplier;

};

