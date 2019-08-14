#include "InventoryScript.h"



InventoryScript::InventoryScript(std::vector<GameObject*> &list)
{
	m_SlotList = list;
	m_iNumInInventory = 0;
	for (int i = 0; i < INVENTORY_SIZE; ++i)
	{
		m_List[i] = nullptr;
	}
}


InventoryScript::~InventoryScript()
{
}

void InventoryScript::AddItem(GameObject* go)
{
	if (m_iNumInInventory < INVENTORY_SIZE)
	{
		m_List[m_iNumInInventory] = go;
		Vector3 pos = m_SlotList.at(m_iNumInInventory)->TRANS->GetPosition();
		Vector3 scal = {10,10,10};
		Instantiate(go, pos, "UI");
		Destroy(go);
		++m_iNumInInventory;
	}
}