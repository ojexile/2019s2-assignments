#include "ChunkEvent.h"
#include "EntityScript.h"
#include "LootScript.h"
//Temporary
#include "DataContainer.h"

ChunkEvent::ChunkEvent(ChunkData* chunk)
	: m_eventType (NIL),
	  m_chunkRef (chunk),
	  m_BaseEntityRef (nullptr)
{
	m_BaseEntityRef = DataContainer::GetInstance()->GetGameObject("BaseEnemy");
}


ChunkEvent::~ChunkEvent()
{
}

void ChunkEvent::SetChunkRef(ChunkData* chunk)
{
	this->m_chunkRef = chunk;
}

void ChunkEvent::SetEntityRef(GameObject* go)
{
	this->m_BaseEntityRef = go;
}

void ChunkEvent::GenerateEvent()
{
	m_eventType = static_cast<EVENT_TYPE>(Math::RandIntMinMax(NIL, LOOT_AND_ENEMIES));
	
	Vector3 size = m_chunkRef->GetSize();

	switch (m_eventType)
	{
	case NIL:
	{
		break;
	}
	case ENEMIES:
	{
		unsigned int spawnCount = 3;

		for (unsigned int i = 0; i < spawnCount; ++i)
		{
			float x = Math::RandFloatMinMax(0.f, size.x);
			float z = Math::RandFloatMinMax(0.f, size.z);
			Vector3 pos = m_chunkRef->GetGroundPosition(Vector3(x, 0.f, z));

			GameObject* newEntity = m_BaseEntityRef->Clone();
			newEntity->TRANS->SetPosition(pos);
		}
		break;
	}
	case LOOT_CHEST:
	{
		//NOTE: Wait on chest interactable
		break;
	}
	case LOOT_AND_ENEMIES:
	{
		unsigned int spawnCount = 5;
		for (unsigned int i = 0; i < spawnCount; ++i)
		{
			GameObject* newEntity = m_BaseEntityRef->Clone();
		}
		break;
	}
	}

}

//void ChunkEvent::GenerateEntities()
//{
//
//}