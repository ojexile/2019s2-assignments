#pragma once
#include "ScriptComponent.h"
#include <vector>
#define INVENTORY_SIZE 3
class InventoryScript :
	public ScriptComponent
{
private:
	GameObject* m_Holding;
	int m_iHoldingIndex;
	GameObject* m_Weapon;
	std::vector<GameObject*> m_InventoryItems;
	std::vector<GameObject*> m_SlotList;
	std::vector<GameObject*> m_WeaponSlotList;
public:
	InventoryScript(GameObject* gun, std::vector<GameObject*> list, std::vector<GameObject*> wlist);
	virtual ~InventoryScript();
	virtual ComponentBase* Clone() { return new InventoryScript(*this); };
	virtual void Update(double dt) override;
	
	void AddItem(GameObject* go);
	void Attach();
};

