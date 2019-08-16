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
	int m_iNumInInventory;
	GameObject* m_Weapon;
	GameObject* m_List[INVENTORY_SIZE];
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

