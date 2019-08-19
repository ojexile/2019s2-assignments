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
	switch (Math::RandIntMinMax(0, 1))
	{
	case 0:
		return "Map";
	case 1:
		return "goldmine";
	}
}

void MapSpawningScript::Update(double dt)
{
	DataContainer* dataContainer = DataContainer::GetInstance();
	GameObjectManager* GOM = SceneManager::GetInstance()->GetScene()->GetGameObjectManager();
	Vector3 v = GetComponent<TransformComponent>()->GetPosition();
	for (int x = -1; x <= 1; ++x)
	{
		for (int z = -1; z <= 1; ++z)
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
			m_spawnedLocations.emplace(Vector3(offsetX + xDiff, 0, offsetZ + zDiff));
			
		}
	}
}
