#pragma once
#include "ChunkData.h"
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
		ENEMIES,
		LOOT_CHEST,
		LOOT_AND_ENEMIES,
	};

	ChunkEvent(ChunkData* chunk);
	~ChunkEvent();

	void SetChunkRef(ChunkData* chunk);
	void SetEntityRef(GameObject* go);

	void GenerateEvent(GameObjectManager* GOM_ref, Vector3 Chunk_Pos);
	//void GenerateEntities();

private:
	EVENT_TYPE m_eventType;
	ChunkData* m_chunkRef;
	GameObject* m_BaseEntityRef;
};

