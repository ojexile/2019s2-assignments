#pragma once
#include "ScriptComponent.h"
#include "PartScript.h"
#include "WeaponPartScript.h"
#include "MiscellaneousPartScript.h"

class LootScript : public ScriptComponent
{
public:
	LootScript();
	virtual ~LootScript();

	void DropLoot(void);

	virtual Component* Clone() { return new LootScript(*this); }

	enum MISC_PARTLIST
	{
		STAMINA,
	};
	
	virtual void Collide(GameObject* go);

private:

	//Returns a partScript
	WeaponPartScript* GenerateWeaponPart(void);
	MiscellaneousPartScript* GenerateMiscPart(void);

	GameObject* m_LootDrop;
};
