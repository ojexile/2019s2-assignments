#pragma once
#include "ScriptComponent.h"
#include "WeaponPartScript.h"
#include "Augment.h"

class LootScript : public ScriptComponent
{
public:
	LootScript();
	virtual ~LootScript();

	void DropLoot(void);

	virtual Component* Clone() { return new LootScript(*this); }
	virtual void Collide(GameObject* go);

private:

	//Returns a partScript
	WeaponPartScript* GenerateWeaponPart(void);
	/*Augment* GenerateAugment(void);*/
	GameObject* m_LootDrop;
};
