#pragma once
#include "ScriptComponent.h"
#include "PartScript.h"
#include "WeaponPartScript.h"

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


	GameObject* m_LootDrop;
};
