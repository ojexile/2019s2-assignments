#include "LootScript.h"
#include "DataContainer.h"
#include "Rigidbody.h"
#include "ChunkCollider.h"
#include "SceneManager.h"

LootScript::LootScript()
{
	m_LootDrop = DataContainer::GetInstance()->GetGameObject("Loot");
}


LootScript::~LootScript()
{
}

void LootScript::Collide(GameObject * go)
{

	if (go->GetComponent<ChunkCollider>(true) != nullptr)
		return;

	//Vector3 chunkspacepos = TRANS->GetPosition() - go->TRANS->GetPosition();
	DropLoot();
	//DestroySelf();
	SceneManager::GetInstance()->GetScene()->GetGameObjectManager()->QueueDestroyFromComponent(this);
	
}

WeaponPartScript* LootScript::GenerateWeaponPart(void)
{
	WeaponPartScript::SLOT_TYPE SlotType = static_cast<WeaponPartScript::SLOT_TYPE>(Math::RandIntMinMax(1, WeaponPartScript::SLOT_TYPE::MUZZLE));
	float Durability = Math::RandFloatMinMax(5, 15);
	float Multiplier;

	if (SlotType == WeaponPartScript::SLOT_TYPE::MUZZLE || SlotType == WeaponPartScript::SLOT_TYPE::SCOPE)
	{
		Multiplier = Math::RandFloatMinMax(0.5f, 0.9f);
		
		if (SlotType == WeaponPartScript::SLOT_TYPE::MUZZLE)
		{
			m_LootDrop->RENDER->SetMesh(DataContainer::GetInstance()->GetMesh("Muzzle"));
		}
		else
		{
			m_LootDrop->RENDER->SetMesh(DataContainer::GetInstance()->GetMesh("Scope"));
		}

	}
	else if (SlotType == WeaponPartScript::SLOT_TYPE::CLIP || SlotType == WeaponPartScript::SLOT_TYPE::GRIP)
	{
		Multiplier = Math::RandFloatMinMax(1.2f, 2.f);
		if (SlotType == WeaponPartScript::SLOT_TYPE::CLIP)
		{
			m_LootDrop->RENDER->SetMesh(DataContainer::GetInstance()->GetMesh("Clip"));
		}
		else
		{
			m_LootDrop->RENDER->SetMesh(DataContainer::GetInstance()->GetMesh("Grip"));
		}
	
	}

	return new WeaponPartScript(SlotType, Multiplier, Durability);

}

void LootScript::DropLoot(void)
{

	WeaponPartScript* NewWeaponPartScript = nullptr;
	
	NewWeaponPartScript = GenerateWeaponPart();

	GameObject* Loot = Instantiate(m_LootDrop, this->GetPosition());

	Loot->AddComponent(NewWeaponPartScript);
	Loot->RENDER->SetActive(true);
	Loot->RIGID->SetAffectedByGravity(true);

	RYAN_LOG("LOOT_DROP");

}