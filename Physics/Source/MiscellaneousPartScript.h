#pragma once
#include "PartScript.h"

#include <string>

/********************************************************************************
Author: Ryan Tan Zheng Rong
Brief: Script for special weapon parts that can be attached to the weapon
	   etc. they can be attached anywhere and will have a buff & a debuff
	   these parts will affect the player and not the weapon 
********************************************************************************/

enum STAT_EFFECTS
{
	NONE,
	STAMINA_REGEN,
	HEALTH_REGEN,
	MOVEMENT_SPEED,
	JUMP_HEIGHT,
	MAX_HEALTH,
	SELF_DAMAGE,
	EQUALIZER,
	NUM_EFFECTS
};

class MiscellaneousPartScript : public PartScript
{
public:
	MiscellaneousPartScript(SLOT_TYPE slot, double Multiplier, float durability);
	virtual ~MiscellaneousPartScript();

	void SetAttachment(SLOT_TYPE AttachedSlot);

	virtual void Effect();

	virtual void Buff() = 0;
	virtual void Debuff() = 0;

protected:

	GameObject* playerRef;

	STAT_EFFECTS m_BuffedStat;
	STAT_EFFECTS m_DebuffedStat;

	float m_fBuffMultiplier;
	float m_fDebuffMultiplier;

	SLOT_TYPE m_AttachedSlotType;

	std::string m_Name;

};

