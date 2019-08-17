#include "InventoryScript.h"
#include "InputManager.h"
#include "UIButtonComponent.h"
#include "WeaponScript.h"
#include "Application.h"
InventoryScript::InventoryScript(GameObject* weapon, GameObject** list, std::vector<GameObject*> wlist, GameObject* reticle)
	: m_WeaponSlotList(wlist)
	, m_Reticle(reticle)
{
	m_Weapon = weapon;
	m_SlotList = list;
	m_Holding = nullptr;
	m_iHoldingIndex = -1;
	m_iNumInventory = 0;

	for (int i = 0; i < INVENTORY_SIZE; ++i)
	{
		m_InventoryItems[i] = nullptr;
	}
}

InventoryScript::~InventoryScript()
{
}
void InventoryScript::Update(double dt)
{
	// Check if inventory click
	bool bClick = false;
	if (InputManager::GetInstance()->GetInputStrength("Click"))
	{
		bClick = true;
	}
	bool hover = false;
	if (m_Holding)
	{
		// check for hover
		for (int i = 0; i < 4; ++i)
		{
			if (m_WeaponSlotList[i]->GetComponent<UIButtonComponent>()->GetHover())
			{
				hover = true;
				if (bClick)
				{
					switch (i)
					{
					case 0:
						Attach();
						m_Holding = nullptr;
						break;
					case 1:
						Attach();
						m_Holding = nullptr;
						break;
					case 2:
						Attach();
						m_Holding = nullptr;
						break;
					case 3:
						Attach();
						m_Holding = nullptr;
						break;
					default:
						break;
					}
					// CHENG_LOG("Part added");
					break;
				}
			}
		}
	}

	else
	{
		for (unsigned i = 0; i < INVENTORY_SIZE; ++i)
		{
			if (m_SlotList[i]->GetComponent<UIButtonComponent>()->GetHover())
			{
				hover = true;

				if (bClick)
				{
					if (!m_InventoryItems[i])
						return;
					GameObject* Part = m_InventoryItems[i];
					m_Holding = Part;
					m_iHoldingIndex = i;
					CHENG_LOG("Part added");
				}
			}
		}
	}

	if (m_Holding)
	{
		double x, y;
		Application::GetCursorPosRelative(&x, &y);

		Vector3 ScreenMousePos((float)x * 1920, (1 - (float)y) * 1080);

		m_Holding->TRANS->SetPosition(ScreenMousePos);
		m_Reticle->SetActive(false);
	}
	else
		m_Reticle->SetActive(!hover);
}
void InventoryScript::AddItem(GameObject* go)
{
	int iSlot = -1;
	if (m_iNumInventory < INVENTORY_SIZE)
	{
		// find slot
		for (int i = 0; i < INVENTORY_SIZE; ++i)
		{
			if (m_InventoryItems[i] == nullptr)
			{
				iSlot = i;
				break;
			}
		}
		Vector3 pos = m_SlotList[iSlot]->TRANS->GetPosition();
		Vector3 scal = { 20,20,1 };
		GameObject* go2 = Instantiate(go, pos, scal, "UI");
		go2->RIGID->SetAffectedByGravity(false);
		m_InventoryItems[iSlot] = go2;
		Destroy(go);
		++m_iNumInventory;
	}
}

void InventoryScript::Attach()
{
	GameObject* go = m_InventoryItems[m_iHoldingIndex];
	GameObject* cpy = Instantiate(go, Vector3{ 0,0,0 }, Vector3{ 1,1,1 }, "Default", true);
	cpy->RIGID->SetAffectedByGravity(false);
	m_Weapon->AddChild(cpy);
	m_Weapon->GetComponent<WeaponScript>()->AddPart(cpy);
	Destroy(go);
	m_InventoryItems[m_iHoldingIndex] = nullptr;
	--m_iNumInventory;
}