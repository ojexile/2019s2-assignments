#pragma once
#include "CollisionManager.h"
#include "Rigidbody.h"
#include "ChunkData.h"

class ChunkCollider : public Rigidbody
{
	ChunkData* m_chunk;
public:
	ChunkCollider(ChunkData* chunk);
	ChunkData* GetChunk();
};
