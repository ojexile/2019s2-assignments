#include "LootScript.h"
#include "DataContainer.h"
#include "Rigidbody.h"
#include "ChunkCollider.h"
#include "SceneManager.h"
#include "ExplodeAugment.h"
#include "BlackHoleAugment.h"
#include "ParticleSpawnerScript.h"

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
	float Durability = Math::RandFloatMinMax(5.f, 10.f);
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

Augment* LootScript::GenerateAugment(void)
{
	int GenerateAugmentChance = Math::RandIntMinMax(1, 10);

	if (GenerateAugmentChance > 7)
	{
		GenerateAugmentChance = Math::RandIntMinMax(1, 10);
		if (GenerateAugmentChance == 1)
		{
			//return new ExplodeAugment();
		}
		//else if (GenerateAugmentChance == 2)
		//{
		//	return new BlackHoleAugment();
		//}
	}

	return nullptr;
}

void LootScript::DropLoot(void)
{

	//40% chance to drop loot
	int DropChance = Math::RandIntMinMax(1, 10);
	if (DropChance > 6)
	{
		DropChance = Math::RandIntMinMax(1, 10);
		//30% chance to drop a part
		//70% chacne to drop other loot
		if (DropChance > 7)
		{
			//Generate the part
			WeaponPartScript* NewWeaponPartScript = nullptr;
			NewWeaponPartScript = GenerateWeaponPart();

			GameObject* Loot = Instantiate(m_LootDrop, this->GetPosition());
			Loot->AddComponent(NewWeaponPartScript);
			Loot->RENDER->SetActive(true);
			Loot->RIGID->SetAffectedByGravity(true);

			//Augment Generation
			auto part = GenerateAugment();
			if (part != nullptr)
			{
				Loot->PART->SetAugment(GenerateAugment());
				Loot->AddComponent(new ParticleSpawnerScript(DataContainer::GetInstance()->GetGameObject("particleRareDrop"),
					5, { 0.1f,0.1f,0.1f }, 0.1f
					));
			}
		}
		else
		{

		}
	}

	RYAN_LOG("LOOT_DROP");
}