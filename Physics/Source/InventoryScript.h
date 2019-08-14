#pragma once
#include "ScriptComponent.h"
#define INVENTORY_SIZE 3
class InventoryScript :
	public ScriptComponent
{
private:
	int m_iNumInInventory;
	GameObject* m_List[INVENTORY_SIZE];
	std::vector<GameObject*> m_SlotList;
public:
	InventoryScript(std::vector<GameObject*> &list);
	virtual ~InventoryScript();
	virtual ComponentBase* Clone() { return new InventoryScript(*this); };
	void AddItem(GameObject* go);
};

