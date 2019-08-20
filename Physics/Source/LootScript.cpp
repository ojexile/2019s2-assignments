#include "LootScript.h"
#include "DataContainer.h"
#include "Rigidbody.h"
#include "ChunkCollider.h"
#include "ConcreteMiscParts/StaminaRegenPart.h"
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

	if (go->GetComponent<ChunkCollider>() != nullptr)
		return;

	//Vector3 chunkspacepos = TRANS->GetPosition() - go->TRANS->GetPosition();
	DropLoot();
	//DestroySelf();
	SceneManager::GetInstance()->GetScene()->GetGameObjectManager()->QueueDestroyFromComponent(this);
	
}

WeaponPartScript* LootScript::GenerateWeaponPart(void)
{
	PartScript::SLOT_TYPE SlotType = static_cast<PartScript::SLOT_TYPE>(Math::RandIntMinMax(1, PartScript::SLOT_TYPE::MUZZLE));
	float Durability = Math::RandFloatMinMax(5, 15);
	float Multiplier;

	if (SlotType == PartScript::SLOT_TYPE::MUZZLE || SlotType == PartScript::SLOT_TYPE::SCOPE)
	{
		Multiplier = Math::RandFloatMinMax(0.5f, 0.9f);
		
		if (SlotType == PartScript::SLOT_TYPE::MUZZLE)
		{
			m_LootDrop->RENDER->SetMesh(DataContainer::GetInstance()->GetMesh("Muzzle"));
		}
		else
		{
			m_LootDrop->RENDER->SetMesh(DataContainer::GetInstance()->GetMesh("Scope"));
		}

	}
	else if (SlotType == PartScript::SLOT_TYPE::CLIP || SlotType == PartScript::SLOT_TYPE::GRIP)
	{
		Multiplier = Math::RandFloatMinMax(1.2f, 2.f);
		if (SlotType == PartScript::SLOT_TYPE::CLIP)
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

MiscellaneousPartScript* LootScript::GenerateMiscPart(void)
{
	PartScript::SLOT_TYPE SlotType = PartScript::SLOT_TYPE::ALL;
	MISC_PARTLIST concreteType = STAMINA;
	
	float Durability = Math::RandFloatMinMax(5, 15);

	float SpreadDebuff = Math::RandFloatMinMax(1.f, 1.5f);
	float FireRateDebuff = Math::RandFloatMinMax(1.f, 1.25f);
	int MaxMagazineDebuff = Math::RandIntMinMax(1, 3);
	int MaxAmmoDebuff = Math::RandIntMinMax(5, 10);

	switch (concreteType)
	{
	case STAMINA:
	{

		return new StaminaRegenPart(SpreadDebuff, FireRateDebuff, MaxMagazineDebuff, MaxAmmoDebuff, Durability);
	}
	default:
	{
		break;
	}
	}
}

void LootScript::DropLoot(void)
{

	PartScript::PART_TYPE type = static_cast<PartScript::PART_TYPE>(Math::RandIntMinMax(PartScript::PART_TYPE::WEAPON, PartScript::PART_TYPE::MISC));
	PartScript* NewPartScript = nullptr;
	
	if (type == PartScript::PART_TYPE::WEAPON)
	{
		NewPartScript = GenerateWeaponPart();
	}
	else if (type == PartScript::PART_TYPE::MISC)
	{
		NewPartScript = GenerateMiscPart();
	}

	GameObject* Loot = Instantiate(m_LootDrop, this->GetPosition());

	Loot->AddComponent(NewPartScript);
	Loot->RENDER->SetActive(true);
	Loot->RIGID->SetAffectedByGravity(true);

	RYAN_LOG("LOOT_DROP");

}