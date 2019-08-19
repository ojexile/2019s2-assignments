#include "MapSpawningScript.h"
#include "SceneManager.h"
#include "DataContainer.h"
#include "ChunkCollider.h"
#define NCHUNKS 12
MapSpawningScript::MapSpawningScript()
{
}

MapSpawningScript::~MapSpawningScript()
{
}


const char* GetChunkByID(int id)
{
	switch (id)
	{
	case 0:
		return "archway";
	case 1:
		return "goldmine";
	case 2:
		return "smallhouse";
	case 3:
		return "bazaar1";
	case 4:
		return "wellspring";
	case 5:
		return "walledoff";
	case 6:
		return "bazaar1_1";
	case 7:
		return "bazaar1_2";
	case 8:
		return "bazaar1_3";
	case 9:
		return "wellspring_1";
	case 10:
		return "walledoff_1";
	case 11:
		return "walledoff_2";
	case 12:
		return "walledoff_3";
	default:
		return "archway";
	}
}


const char* RandomChunk()
{
	return GetChunkByID(Math::RandIntMinMax(3, 12));
}

bool IsCompatible(unsigned short k, unsigned short l)
{
	if (k < l)
	{
		int m = k;
		k = l;
		l = m;
	}
	
	switch (k)
	{
	case 0:
		switch (l)
		{
		case 0: return false;
		case 1:	return false;
		default:
			return true;
		}
	case 1:
		switch (l)
		{
		case 1: return true;
		default:
			return true;
		}
	default:
		return true;
	}
}

void MapSpawningScript::Update(double dt)
{
	DataContainer* dataContainer = DataContainer::GetInstance();
	GameObjectManager* GOM = SceneManager::GetInstance()->GetScene()->GetGameObjectManager();
	Vector3 v = GetComponent<TransformComponent>()->GetPosition();
	for (int x = 0; x <= 3; x = (x > 0? -x : -x + 1))
	{
		for (int z = 0; z <= 3; z = (z > 0? -z : -z + 1))
		{
			int offsetX = floor(v.x / 16.f) + x;
			int offsetZ = floor(v.z / 16.f) + z;
			if (m_spawnedLocations.count(Vector3(offsetX, 0, offsetZ))) continue;
			std::vector<ChunkData*> validChunks;
			ChunkData* chunk;
			for (int nChunksTried = 0; nChunksTried < NCHUNKS; nChunksTried++)
			{
				bool fits = true;
				chunk = dataContainer->GetChunk(GetChunkByID(nChunksTried));
				for (int xDiff = 0; xDiff < chunk->GetSize().x / 16; ++xDiff)
					for (int zDiff = 0; zDiff < chunk->GetSize().z / 16; ++zDiff)
						if (m_spawnedLocations.count(Vector3(offsetX + xDiff, 0, offsetZ + zDiff)) || (
							((IsCompatible(m_connections[Vector3(offsetX + xDiff, 0, offsetZ + zDiff)][0], chunk->GetChunkConnection(Vector3(xDiff, 0, zDiff), 0))) &&
							(IsCompatible(m_connections[Vector3(offsetX + xDiff, 0, offsetZ + zDiff)][1], chunk->GetChunkConnection(Vector3(xDiff, 0, zDiff), 1))) &&
								(IsCompatible(m_connections[Vector3(offsetX + xDiff, 0, offsetZ + zDiff)][2], chunk->GetChunkConnection(Vector3(xDiff, 0, zDiff), 2))) &&
								(IsCompatible(m_connections[Vector3(offsetX + xDiff, 0, offsetZ + zDiff)][3], chunk->GetChunkConnection(Vector3(xDiff, 0, zDiff), 3))))))
						{
							fits = false;
						}
				if(fits)
					validChunks.push_back(chunk);
			}
			if (validChunks.size() == 0)
			{
				for (int nChunksTried = 0; nChunksTried < NCHUNKS; nChunksTried++)
				{
					bool fits = true;
					chunk = dataContainer->GetChunk(GetChunkByID(nChunksTried));
					for (int xDiff = 0; xDiff < chunk->GetSize().x / 16; ++xDiff)
						for (int zDiff = 0; zDiff < chunk->GetSize().z / 16; ++zDiff)
							if (m_spawnedLocations.count(Vector3(offsetX + xDiff, 0, offsetZ + zDiff)))
							{
								fits = false;
							}
					if (fits)
						validChunks.push_back(chunk);
				}
			}
			if (validChunks.size() == 0) return;
			chunk = validChunks[Math::RandIntMinMax(0, validChunks.size() - 1)];
			GameObject* go = GOM->AddGameObject();
			go->TRANS->SetPosition(Vector3(offsetX * 16, 0, offsetZ * 16));
			RenderComponent* render = new RenderComponent(chunk->GenerateMeshBiomed());
			render->SetRenderDistance(100);
			go->AddComponent(render);
			go->AddComponent(new BiomeComponent(static_cast<BiomeComponent::eBiomeTypes>(Math::RandInt() % BiomeComponent::BIOME_COUNT)));
			go->AddComponent(new ChunkCollider(chunk));
			GameObject* s0 = GOM->AddGameObject();
			s0->TRANS->SetRelativePosition(Vector3(8, 32, 16));
			go->AddChild(s0);
			std::stringstream numbers;
			numbers << chunk->GetChunkConnection(Vector3(0, 0, 0), 0);
			s0->AddComponent(new RenderComponent(DataContainer::GetInstance()->GetMesh("Text"), numbers.str()));
			for (int xDiff = 0; xDiff < chunk->GetSize().x / 16; ++xDiff)
				for (int zDiff = 0; zDiff < chunk->GetSize().z / 16; ++zDiff)
				{
					m_spawnedLocations.emplace(Vector3(offsetX + xDiff, 0, offsetZ + zDiff));
					m_connections[Vector3(offsetX + xDiff + 1, 0, offsetZ + zDiff)][0] = chunk->GetChunkConnection(Vector3(xDiff, 0, zDiff), 2); // 0 = -x
					m_connections[Vector3(offsetX + xDiff, 0, offsetZ + zDiff + 1)][1] = chunk->GetChunkConnection(Vector3(xDiff, 0, zDiff), 3); // 1 = -z
					m_connections[Vector3(offsetX + xDiff - 1, 0, offsetZ + zDiff)][2] = chunk->GetChunkConnection(Vector3(xDiff, 0, zDiff), 0); // 2 = +x
					m_connections[Vector3(offsetX + xDiff, 0, offsetZ + zDiff - 1)][3] = chunk->GetChunkConnection(Vector3(xDiff, 0, zDiff), 1); // 3 = +z (from centre of chunk)
				}
			
		}
	}
}

