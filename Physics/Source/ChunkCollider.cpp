#include "ChunkCollider.h"

ChunkCollider::ChunkCollider(ChunkData* data) : Rigidbody(ePhysicsTypes::NONE, false)
{
	m_chunk = data;
}

ChunkData* ChunkCollider::GetChunk()
{
	return m_chunk;
}

