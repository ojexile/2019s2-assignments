#pragma once
#include "ChunkData.h"
#include "BiomeComponent.h"
#include <vector>
/********************************************************************************/
/*!
\author Ryan Tan Zheng Rong
\brief
 Objects associated with chunks to generate random events & entities on the world
/*!
/********************************************************************************/


class ChunkEvent
{
public:

	enum EVENT_TYPE
	{
		NIL = 0,
		ENEMIES_LEVEL_1,
		ENEMIES_LEVEL_2,
		ENEMIES_LEVEL_3,
		LOOT_CHEST,
		LOOT_AND_ENEMIES,
	};

	ChunkEvent();
	virtual ~ChunkEvent();

	void SetEntityRef(GameObject* go);

	void GenerateEntities(GameObjectManager* GOM_ref, ChunkData* chunk_ref, Vector3 Chunk_Pos, BiomeComponent::eBiomeTypes type);
	void GenerateEvent(GameObjectManager* GOM_ref, ChunkData* chunk_ref, Vector3 Chunk_Pos);
	void GenerateEnvironment(GameObjectManager* GOM_ref, ChunkData* chunk_ref, Vector3 Chunk_Pos);

private:
	EVENT_TYPE m_eventType;
};

