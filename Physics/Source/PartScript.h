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

	//This is for Miscellaneous Parts, initially their slot type will be ALL
	void SetSlotType(SLOT_TYPE slot);

protected:
	//Allows for reading in subclasses
	PART_TYPE m_PartType;
	SLOT_TYPE m_SlotType;

private:
	float m_fDurability;
	float m_fStatMultiplier;

};

