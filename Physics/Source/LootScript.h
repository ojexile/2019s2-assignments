#pragma once
#include "ScriptComponent.h"
#include "WeaponPartScript.h"
#include "Augment.h"

/********************************************************************************/
/*!
\author Ryan Tan Zheng Rong
\brief
Script to handle Dropping of loot such as weapon parts, augmented parts and
 other rewards
/*!
/********************************************************************************/


class LootScript : public ScriptComponent
{
public:
	LootScript(bool isRigged = true);
	virtual ~LootScript();

	void DropLoot(void);

	virtual Component* Clone() { return new LootScript(*this); }
	virtual void Collide(GameObject* go);

private:

	//Returns a partScript
	WeaponPartScript* GenerateWeaponPart(void);
	//Returns an Augment
	bool GenerateAugment(GameObject* ptr);
	GameObject* m_LootDrop;
	bool m_isRigged;
	bool m_hasDropped;
};
