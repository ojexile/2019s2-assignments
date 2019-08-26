#include "ChunkEvent.h"
#include "EntityScript.h"
#include "LootScript.h"
#include "GameObjectManager.h"
//Temporary
#include "EntityLibrary.h"

ChunkEvent::ChunkEvent()
	: m_eventType (NIL)
{
}


ChunkEvent::~ChunkEvent()
{

}

void ChunkEvent::SetEntityRef(GameObject* go)
{
	/*this->m_BaseEntityRef = go;*/
}

void ChunkEvent::GenerateEvent(GameObjectManager* GOM_ref, ChunkData* chunk_ref, Vector3 Chunk_Pos)
{
	unsigned int chance = Math::RandIntMinMax(0, 9);
	if (chance > 5)
		m_eventType = NIL;
	else
		m_eventType = static_cast<EVENT_TYPE>(Math::RandIntMinMax(NIL, LOOT_AND_ENEMIES));
	
	Vector3 size = chunk_ref->GetSize();
	EntityLibrary* EL = EntityLibrary::GetInstance();

	switch (m_eventType)
	{
	case NIL:
	{
		break;
	}
	case ENEMIES_LEVEL_1:
	{
		const unsigned int SPAWNCOUNT = 1;
		for (unsigned int i = 0; i < SPAWNCOUNT; ++i)
		{
			float x = Math::RandFloatMinMax(0.f, size.x);
			float z = Math::RandFloatMinMax(0.f, size.z);
			Vector3 pos = /*Vector3(x, 16.5, z)*/chunk_ref->GetGroundPosition(Vector3(x, 0.f, z)) + Chunk_Pos;

			int selectedEnemy = Math::RandIntMinMax(EntityLibrary::MELEE, EntityLibrary::NUM_ENEMIES - 1);

			GameObject* newEntity = EL->GetEnemyArray()[selectedEnemy]->Clone();
			
			newEntity->TRANS->SetPosition(pos);
			newEntity->SetDisableDistance(200.f);
			newEntity->RENDER->SetRenderDistance(200.f);
			
			
			GOM_ref->AddGameObject(newEntity);
		}
		break;
	}
	case ENEMIES_LEVEL_2:
	{
		const unsigned int SPAWNCOUNT = 3;
		for (unsigned int i = 0; i < SPAWNCOUNT; ++i)
		{
			float x = Math::RandFloatMinMax(0.f, size.x);
			float z = Math::RandFloatMinMax(0.f, size.z);
			Vector3 pos = /*Vector3(x, 16.5, z)*/chunk_ref->GetGroundPosition(Vector3(x, 0.f, z)) + Chunk_Pos;

			int selectedEnemy = Math::RandIntMinMax(EntityLibrary::MELEE, EntityLibrary::NUM_ENEMIES - 1);

			GameObject* newEntity = EL->GetEnemyArray()[selectedEnemy]->Clone();

			newEntity->TRANS->SetPosition(pos);
			newEntity->SetDisableDistance(200.f);
			newEntity->RENDER->SetRenderDistance(200.f);


			GOM_ref->AddGameObject(newEntity);
		}
		break;
	}
	case ENEMIES_LEVEL_3:
	{
		const unsigned int SPAWNCOUNT = 5;
		for (unsigned int i = 0; i < SPAWNCOUNT; ++i)
		{
			float x = Math::RandFloatMinMax(0.f, size.x);
			float z = Math::RandFloatMinMax(0.f, size.z);
			Vector3 pos = /*Vector3(x, 16.5, z)*/chunk_ref->GetGroundPosition(Vector3(x, 0.f, z)) + Chunk_Pos;

			int selectedEnemy = Math::RandIntMinMax(EntityLibrary::MELEE, EntityLibrary::NUM_ENEMIES - 1);

			GameObject* newEntity = EL->GetEnemyArray()[selectedEnemy]->Clone();

			newEntity->TRANS->SetPosition(pos);
			newEntity->SetDisableDistance(200.f);
			newEntity->RENDER->SetRenderDistance(200.f);


			GOM_ref->AddGameObject(newEntity);
		}

		break;
	}
	case LOOT_CHEST:
	{
		float x = Math::RandFloatMinMax(0.f, size.x);
		float z = Math::RandFloatMinMax(0.f, size.z);
		Vector3 pos = /*Vector3(x, 16.5, z)*/chunk_ref->GetGroundPosition(Vector3(x, 0.f, z)) + Chunk_Pos;

		int selectedEnemy = Math::RandIntMinMax(EntityLibrary::MELEE, EntityLibrary::NUM_ENEMIES - 1);

		GameObject* newEntity = EL->GetLoot(EntityLibrary::LOOT_CHEST)->Clone();

		newEntity->TRANS->SetPosition(pos);
		newEntity->SetDisableDistance(200.f);
		newEntity->RENDER->SetRenderDistance(200.f);


		GOM_ref->AddGameObject(newEntity);

		break;
	}
	case LOOT_AND_ENEMIES:
	{
		//NOTE: Wait on chest interactable
		const unsigned int SPAWNCOUNT = 4;
		for (unsigned int i = 0; i < SPAWNCOUNT; ++i)
		{
			float x = Math::RandFloatMinMax(0.f, size.x);
			float z = Math::RandFloatMinMax(0.f, size.z);
			Vector3 pos = /*Vector3(x, 16.5, z)*/chunk_ref->GetGroundPosition(Vector3(x, 0.f, z)) + Chunk_Pos;
			GameObject* newEntity;

			if (i < 3)
			{
				int selectedEnemy = Math::RandIntMinMax(EntityLibrary::MELEE, EntityLibrary::NUM_ENEMIES - 1);

				newEntity = EL->GetEnemyArray()[selectedEnemy]->Clone();

				newEntity->TRANS->SetPosition(pos);
				newEntity->SetDisableDistance(200.f);
				newEntity->RENDER->SetRenderDistance(200.f);
			}
			else
			{
				newEntity = EL->GetLoot(EntityLibrary::LOOT_CHEST)->Clone();

				newEntity->TRANS->SetPosition(pos);
				newEntity->SetDisableDistance(200.f);
				newEntity->RENDER->SetRenderDistance(200.f);
			}


			GOM_ref->AddGameObject(newEntity);
		}
		break;
	}
	}
}

void ChunkEvent::GenerateEntities(GameObjectManager* GOM_ref, ChunkData* chunk_ref, Vector3 Chunk_Pos, BiomeComponent::eBiomeTypes type)
{
	const unsigned int SPAWNCOUNT = Math::RandIntMinMax(2, 4);
	Vector3 size = chunk_ref->GetSize();
	EntityLibrary* EL = EntityLibrary::GetInstance();

	for (unsigned int i = 0; i < SPAWNCOUNT; ++i)
	{
		float x = Math::RandFloatMinMax(0.f, size.x);
		float z = Math::RandFloatMinMax(0.f, size.z);
		Vector3 pos =  /*Vector3(x, 16.5, z)*/chunk_ref->GetGroundPosition(Vector3(x, 0.f, z)) + Chunk_Pos;

		int selectedEntity = Math::RandIntMinMax(EntityLibrary::FISH, EntityLibrary::NUM_ENTITIES - 1);
		GameObject* newEntity = EL->GetEntityArray()[selectedEntity]->Clone();

		if (selectedEntity == EntityLibrary::BIRD)
		{

			pos.y = Math::RandFloatMinMax(25.f, 30.5f);

			newEntity->TRANS->SetPosition(pos);
			newEntity->SetDisableDistance(100.f);
			newEntity->RENDER->SetRenderDistance(100.f);

			GOM_ref->AddGameObject(newEntity, "Birds");
		}
		else
		{

			newEntity->TRANS->SetPosition(pos);
			newEntity->SetDisableDistance(100.f);
			newEntity->RENDER->SetRenderDistance(100.f);
			GOM_ref->AddGameObject(newEntity);
		}

	}
}

void ChunkEvent::GenerateEnvironment(GameObjectManager* GOM_ref, ChunkData* chunk_ref, Vector3 Chunk_Pos)
{
	const unsigned int SPAWNCOUNT = Math::RandIntMinMax(2, 4);
	Vector3 size = chunk_ref->GetSize();
	EntityLibrary* EL = EntityLibrary::GetInstance();

	for (unsigned int i = 0; i < SPAWNCOUNT; ++i)
	{
		float x = Math::RandFloatMinMax(0.f, size.x);
		float z = Math::RandFloatMinMax(0.f, size.z);
		Vector3 pos = chunk_ref->GetGroundPosition(Vector3(x, 0.f, z)) + Chunk_Pos;

		if (pos.y > 17)
			continue;


		int selectedEntity = Math::RandIntMinMax(EntityLibrary::STONE_1, EntityLibrary::NUM_ENVIRONMENT - 1);
		GameObject* newEntity = EL->GetEnvironmentArray()[selectedEntity]->Clone();

		newEntity->TRANS->SetPosition(pos);
		newEntity->TRANS->SetScale(Math::RandFloatMinMax(0.5f, 1.0f));
		newEntity->SetDisableDistance(100.f);
		newEntity->RENDER->SetRenderDistance(100.f);
		GOM_ref->AddGameObject(newEntity);

	}
}