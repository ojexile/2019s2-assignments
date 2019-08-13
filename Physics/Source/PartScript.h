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
		GENERIC,
		UNIQUE
	};

	enum SLOT_TYPE
	{
		SCOPE,
		STOCK,
		GRIP,
		MUZZLE,
		ALL
	};

	PartScript();
	~PartScript();

	virtual void Effect() = 0;
	virtual void DecreaseDurability(float deltaTime);

private:

	PART_TYPE m_partType;
	SLOT_TYPE m_slotType;

	bool m_isAttached;

	float m_fDurability;
	float m_fStatEffect;

};

