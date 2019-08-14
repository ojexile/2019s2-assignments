#include "InventoryScript.h"
#include "InputManager.h"
#include "UIButtonComponent.h"
InventoryScript::InventoryScript(GameObject* weapon, std::vector<GameObject*> &list)
{
	m_Weapon = weapon;
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
void InventoryScript::Update(double dt)
{
	// Check if inventory click
	if (InputManager::GetInstance()->GetInputStrength("Click"))
	{
		for (int i = 0; i < m_iNumInInventory; ++i)
		{
			if (m_List[i]->GetComponent<UIButtonComponent>()->GetHover())
			{
				//
			}
		}
	}
}
void InventoryScript::AddItem(GameObject* go)
{
	if (m_iNumInInventory < INVENTORY_SIZE)
	{
		m_List[m_iNumInInventory] = go;
		Vector3 pos = m_SlotList.at(m_iNumInInventory)->TRANS->GetPosition();
		Vector3 scal = {20,20,1};
		Instantiate(go, pos, scal, "UI");
		Destroy(go);
		++m_iNumInInventory;
	}
}