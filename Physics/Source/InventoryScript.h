#pragma once
#include "ScriptComponent.h"
#define INVENTORY_SIZE 3
class InventoryScript :
	public ScriptComponent
{
private:
	int m_iNumInInventory;
	GameObject* m_List[INVENTORY_SIZE] ;
public:
	InventoryScript();
	virtual ~InventoryScript();
	virtual ComponentBase* Clone() { return new InventoryScript(*this); };
	bool AddItem(GameObject* go);
};

