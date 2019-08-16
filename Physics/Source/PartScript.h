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
		WEAPON = 1,
		MISC,
		NUM_TYPES
	};

	enum SLOT_TYPE
	{
		SCOPE = 1,
		CLIP,
		GRIP,
		MUZZLE,
		ALL
	};

	PartScript(PART_TYPE type, SLOT_TYPE slot, float Multiplier, float Durability = 5.f);
	~PartScript();

	virtual void Effect() = 0;
	virtual bool DecreaseDurability(double deltaTime);

	PART_TYPE GetPartType();
	SLOT_TYPE GetSlotType();

	float GetMultiplier();

private:
	PART_TYPE m_partType;
	SLOT_TYPE m_slotType;

	float m_fDurability;
	float m_fStatMultiplier;

};

