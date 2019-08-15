#include "InventoryScript.h"
#include "InputManager.h"
#include "UIButtonComponent.h"
#include "WeaponScript.h"
InventoryScript::InventoryScript(GameObject* weapon, std::vector<GameObject*> list)
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
			if (m_SlotList[i]->GetComponent<UIButtonComponent>()->GetHover())
			{
				if (!m_List[i])
					return;
				GameObject* Part = m_List[i];
				GameObject* cpy = Instantiate(Part, Vector3{ 0,0,0 }, Vector3{ 1,1,1 }, "Default", true);
				cpy->RIGID->SetAffectedByGravity(false);
				m_Weapon->AddChild(cpy);
				m_Weapon->GetComponent<WeaponScript>()->AddPart(cpy);
				Destroy(Part);
				m_List[i] = nullptr;
				--m_iNumInInventory;
				CHENG_LOG("Part added");
				break;
			}
		}
	}
}
void InventoryScript::AddItem(GameObject* go)
{
	if (m_iNumInInventory < INVENTORY_SIZE)
	{
		Vector3 pos = m_SlotList.at(m_iNumInInventory)->TRANS->GetPosition();
		Vector3 scal = { 20,20,1 };
		GameObject* go2 = Instantiate(go, pos, scal, "UI");
		go2->RIGID->SetAffectedByGravity(false);
		m_List[m_iNumInInventory] = go2;
		Destroy(go);
		++m_iNumInInventory;
	}
}