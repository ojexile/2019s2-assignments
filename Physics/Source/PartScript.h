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

	enum SLOT_TYPE
	{
		SCOPE = 1,
		CLIP,
		GRIP,
		MUZZLE,
	};

	PartScript(SLOT_TYPE slot, float Multiplier, float Durability = 5.f);
	~PartScript();

	virtual void Effect() = 0;
	virtual bool DecreaseDurability(double deltaTime);

	SLOT_TYPE GetSlotType();

	float GetMultiplier();

	//This is for Miscellaneous Parts, initially their slot type will be ALL
	void SetSlotType(SLOT_TYPE slot);

	void SetDurability(float durability);
	void SetMultiplier(float multiplier);

protected:
	SLOT_TYPE m_SlotType;

private:
	float m_fDurability;
	float m_fStatMultiplier;

};

