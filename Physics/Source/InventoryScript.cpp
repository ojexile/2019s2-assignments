#include "InventoryScript.h"



InventoryScript::InventoryScript()
{
	m_iNumInInventory = 0;
	for (int i = 0; i < INVENTORY_SIZE; ++i)
	{
		m_List[i] = nullptr;
	}
}


InventoryScript::~InventoryScript()
{
}

bool InventoryScript::AddItem(GameObject* go)
{
	if (m_iNumInInventory < INVENTORY_SIZE)
	{
		m_List[m_iNumInInventory] = go;
		return true;
	}
	return false;
}