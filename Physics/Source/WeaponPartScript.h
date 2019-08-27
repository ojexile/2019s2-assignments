#pragma once
#include "Augment.h"
/********************************************************************************
Author: Ryan Tan Zheng Rong
Brief: Base Script for weapon parts that can be attached to the weapon
	   etc.
********************************************************************************/

class WeaponPartScript : public ScriptComponent
{
public:

	enum SLOT_TYPE
	{
		SCOPE = 1,
		CLIP,
		GRIP,
		MUZZLE,
	};

	WeaponPartScript(SLOT_TYPE slot, float Multiplier, float Durability = 5.f, Augment* Augment = nullptr);
	virtual ~WeaponPartScript();

	bool DecreaseDurability(double deltaTime);
	void RepairPart(float healingAmt);
	SLOT_TYPE GetSlotType();
	float GetMultiplier();
	Augment* GetAugment();

	void SetSlotType(SLOT_TYPE slot);
	void SetAugment(Augment* Augment);
	void SetDurability(float durability);
	void SetMultiplier(float multiplier);
	void SetDescription(std::string s);
	void SetName(std::string s);

	std::string GetName(void);
	std::string GetDescription(void);

	virtual Component* Clone() { return new WeaponPartScript(*this); }

private:
	float m_fDurability;
	float m_fStatMultiplier;

	Augment* m_Augment;
	
	SLOT_TYPE m_SlotType;
	
	std::string m_Name;
	std::string m_Description;
};
