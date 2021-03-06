#pragma once
#include "ScriptComponent.h"
#include "WeaponPartScript.h"
#include "StopWatch.h"
#include <vector>
#define INVENTORY_SIZE 6
class InventoryScript :
	public ScriptComponent
{
private:
	GameObject* m_Holding;
	int m_iHoldingIndex;
	int m_iNumInventory;
	GameObject* m_Weapon;
	GameObject* m_InventoryItems[INVENTORY_SIZE];
	GameObject** m_SlotList;
	std::vector<GameObject*> m_WeaponSlotList;
	GameObject* m_Reticle;
	StopWatch s;
	bool m_bAttach;
public:
	InventoryScript(GameObject* gun, GameObject** list
		, std::vector<GameObject*> wlist, GameObject* reticle);
	virtual ~InventoryScript();
	virtual Component* Clone() { return new InventoryScript(*this); };
	virtual void Update(double dt) override;

	void AddItem(GameObject* go);
	void Attach(WeaponPartScript::SLOT_TYPE e);
};
