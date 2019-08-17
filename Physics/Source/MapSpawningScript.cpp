#include "MapSpawningScript.h"
#include "SceneManager.h"
#include "DataContainer.h"
#include "ChunkCollider.h"

MapSpawningScript::MapSpawningScript()
{
}

MapSpawningScript::~MapSpawningScript()
{
}

const char* RandomChunk()
{
	switch (Math::RandIntMinMax(0, 2))
	{
	case 0:
		return "archway";
	case 1:
		return "goldmine";
	case 2:
		return "smallhouse";
	}
}

void MapSpawningScript::Update(double dt)
{
	DataContainer* dataContainer = DataContainer::GetInstance();
	GameObjectManager* GOM = SceneManager::GetInstance()->GetScene()->GetGameObjectManager();
	Vector3 v = GetComponent<TransformComponent>()->GetPosition();
	for (int x = 0; x <= 4; x = (x > 0? -x : -x + 1))
	{
		for (int z = 0; z <= 4; z = (z > 0? -z : -z + 1))
		{
			int offsetX = floor(v.x / 16.f) + x;
			int offsetZ = floor(v.z / 16.f) + z;
			if (m_spawnedLocations.count(Vector3(offsetX, 0, offsetZ))) continue;
			ChunkData* chunk = dataContainer->GetChunk(RandomChunk());
			bool flag = false;
			while (true)
			{
				flag = false;
				for (int xDiff = 0; xDiff < chunk->GetSize().x / 16 && !flag; ++xDiff)
					for (int zDiff = 0; zDiff < chunk->GetSize().z / 16 && !flag; ++zDiff)
						if (m_spawnedLocations.count(Vector3(offsetX + xDiff, 0, offsetZ + zDiff)))
						{
							offsetX = offsetX + Math::RandIntMinMax(-1, 1);
							offsetZ = offsetZ + Math::RandIntMinMax(-1, 1);
							flag = true;
						}
				if (!flag) break;
			}
			GameObject* go = GOM->AddGameObject();
			go->TRANS->SetPosition(Vector3(offsetX * 16, 0, offsetZ * 16));
			RenderComponent* render = new RenderComponent(chunk->GenerateMeshBiomed());
			render->SetRenderDistance(100);
			go->AddComponent(render);
			go->AddComponent(new BiomeComponent(static_cast<BiomeComponent::eBiomeTypes>(Math::RandInt() % BiomeComponent::BIOME_COUNT)));
			go->AddComponent(new ChunkCollider(chunk));
			for (int xDiff = 0; xDiff < chunk->GetSize().x / 16; ++xDiff)
				for (int zDiff = 0; zDiff < chunk->GetSize().z / 16; ++zDiff)
				{
					m_spawnedLocations.emplace(Vector3(offsetX + xDiff, 0, offsetZ + zDiff));
					m_connections[Vector3(offsetX + xDiff + 1, 0, offsetZ + zDiff)][0] = chunk->GetChunkConnection(Vector3(xDiff, 0, zDiff), 2);
					m_connections[Vector3(offsetX + xDiff, 0, offsetZ + zDiff + 1)][1] = chunk->GetChunkConnection(Vector3(xDiff, 0, zDiff), 3);
					m_connections[Vector3(offsetX + xDiff - 1, 0, offsetZ + zDiff)][2] = chunk->GetChunkConnection(Vector3(xDiff, 0, zDiff), 0);
					m_connections[Vector3(offsetX + xDiff, 0, offsetZ + zDiff - 1)][3] = chunk->GetChunkConnection(Vector3(xDiff, 0, zDiff), 1);
				}
			
		}
	}
}
