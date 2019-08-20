#pragma once
#include "PartScript.h"
#include "PlayerStatsScript.h"
#include <string>

/********************************************************************************
Author: Ryan Tan Zheng Rong
Brief: Script for special weapon parts that can be attached to the weapon
	   etc. they can be attached anywhere and will have a buff & a debuff
	   these parts will affect the player and not the weapon 
********************************************************************************/

class MiscellaneousPartScript : public PartScript
{
public:
	MiscellaneousPartScript(float SpreadDebuff, float FireRateDebuff, int MaxMagazineDebuff, int MaxAmmoDebuff, float durability);
	virtual ~MiscellaneousPartScript();

	void SetGunReference(GameObject* ref);
	void SetPlayerReference(ComponentBase* ref);

	std::string getName();

	
	virtual void Effect();
	virtual void RevertEffect() = 0;
	
	virtual void Buff(bool reverse) = 0;
	virtual void Debuff(bool reverse) = 0;

protected:

	ComponentBase* m_PlayerRef;
	GameObject* m_GunRef;

	float m_fSpreadDebuff;
	float m_fFireRateDebuff;
	int m_iMaxMagazineDebuff;
	int m_iMaxAmmoDebuff;

	std::string m_Name;

};

