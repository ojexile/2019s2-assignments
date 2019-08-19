#include "MapSpawningScript.h"
#include "SceneManager.h"
#include "DataContainer.h"
#include "ChunkCollider.h"
#include "Utility.h"
#define NCHUNKS 17
MapSpawningScript::MapSpawningScript()
{
	for (int i = 0; i < 4096; ++i)
	{
		m_biomeNoise.emplace_back();
		for (BiomeComponent::eBiomeTypes b = (BiomeComponent::eBiomeTypes) 0; b < BiomeComponent::BIOME_COUNT; b = (BiomeComponent::eBiomeTypes) (b + 1))
		{
			m_biomeNoise[i][b] = Math::RandFloatMinMax(-1, 1);
		}
	}
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
	case 13:
		return "barline";
	case 14:
		return "barline_1";
	case 15:
		return "barline_2";
	case 16:
		return "barline_3";
	default:
		return "archway";
	}
}


const char* RandomChunk()
{
	return GetChunkByID(Math::RandIntMinMax(0, 16));
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
		for (int z = 0; z <= 3; z = (z > 0 ? -z : -z + 1))
		{
			int offsetX = floor(v.x / 16.f) + x;
			int offsetZ = floor(v.z / 16.f) + z;
			if (m_spawnedLocations.count(Vector3(offsetX, 0, offsetZ))) continue;
			std::vector<ChunkData*> validChunks;
			ChunkData* chunk;
			for (int nChunksTried = 13; nChunksTried < NCHUNKS; nChunksTried++)
			{
				bool fits = true;
				chunk = dataContainer->GetChunk(GetChunkByID(nChunksTried));
				for (int xDiff = 0; xDiff < chunk->GetSize().x / 16; ++xDiff)
					for (int zDiff = 0; zDiff < chunk->GetSize().z / 16; ++zDiff)
						if (m_spawnedLocations.count(Vector3(offsetX + xDiff, 0, offsetZ + zDiff)) || (
							(
								(m_connections[Vector3(offsetX + xDiff, 0, offsetZ + zDiff)].count(0) != 0 && !IsCompatible(m_connections[Vector3(offsetX + xDiff, 0, offsetZ + zDiff)][0], chunk->GetChunkConnection(Vector3(xDiff, 0, zDiff), 0))) ||
								(m_connections[Vector3(offsetX + xDiff, 0, offsetZ + zDiff)].count(1) != 0 && !IsCompatible(m_connections[Vector3(offsetX + xDiff, 0, offsetZ + zDiff)][1], chunk->GetChunkConnection(Vector3(xDiff, 0, zDiff), 1))) ||
								(m_connections[Vector3(offsetX + xDiff, 0, offsetZ + zDiff)].count(2) != 0 && !IsCompatible(m_connections[Vector3(offsetX + xDiff, 0, offsetZ + zDiff)][2], chunk->GetChunkConnection(Vector3(xDiff, 0, zDiff), 2))) ||
								(m_connections[Vector3(offsetX + xDiff, 0, offsetZ + zDiff)].count(3) != 0 && !IsCompatible(m_connections[Vector3(offsetX + xDiff, 0, offsetZ + zDiff)][3], chunk->GetChunkConnection(Vector3(xDiff, 0, zDiff), 3)))
							)))
						{
							fits = false;
						}
				if (fits)
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
			Vector3 goPos = Vector3(offsetX * 16, 0, offsetZ * 16);
			go->TRANS->SetPosition(goPos);
			RenderComponent* render = new RenderComponent(chunk->GenerateMeshBiomed());
			render->SetRenderDistance(100);
			go->AddComponent(render);
			go->AddComponent(new BiomeComponent(GetBiomeAt(Vector3(offsetX, 0, offsetZ))));
			go->AddComponent(new ChunkCollider(chunk));
			
#ifdef DEBUG_NUMBERS
			for (int i = 0; i < 4; ++i) {
				GameObject* s0 = GOM->AddGameObject("UI");
				Vector3 ks = Vector3(-6, 0, 0);
				Mtx44 mr; mr.SetToRotation(i * 90, 0, -1, 0);
				s0->TRANS->SetPosition(goPos + Vector3(8, 22, 8) + mr * ks);
				s0->TRANS->SetScale(Vector3(3,3,3));
				std::stringstream numbers;
				numbers << chunk->GetChunkConnection(Vector3(0, 0, 0), i);
				RenderComponent* rc0 = new RenderComponent(DataContainer::GetInstance()->GetMesh("Text"), numbers.str(), false);
				s0->AddComponent(rc0);
				rc0->Set3DBillboard(true);
				rc0->SetColor(0, 1, 0);
			}
#endif
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

float PolyLerp1D(float x0, float fx0, float x1, float fx1, float k)
{
	return Lerp(fx0, fx1, (k - x0) / (x1 - x0));
}
float BiLerp2D(float x0y0, float x0y1, float x1y0, float x1y1, float x, float y)
{
	return Lerp(Lerp(x0y0, x0y1, y), Lerp(x1y0, x1y1, y), x);
}
float Mod(float x, float b)
{
	return x - floor(x / b) * b;
}
int Mod(int x, int b)
{
	return (x % b + b) % b;
}
BiomeComponent::eBiomeTypes MapSpawningScript::GetBiomeAt(Vector3 v)
{
	std::map<BiomeComponent::eBiomeTypes, float> biomeWeights;
	float X = v.x;
	float Z = v.z;
	for (int i = 0; i < 6; ++i)
	{
		float multiplier = pow(2, i) / 8;
		float x = X * multiplier;
		float z = Z * multiplier;
		x = Mod(x, 64.f);
		z = Mod(z, 64.f);
		int xLow = floor(x);
		int zLow = floor(z); 
		for (BiomeComponent::eBiomeTypes b = (BiomeComponent::eBiomeTypes) 0; b < BiomeComponent::BIOME_COUNT; b = (BiomeComponent::eBiomeTypes) (b+1))
		{
			biomeWeights[b] += BiLerp2D(m_biomeNoise[Mod(xLow * 64 + zLow, 4096)][b],
				m_biomeNoise[Mod(xLow * 64 + zLow + 1, 4096)][b],
				m_biomeNoise[Mod(xLow * 64 + zLow + 64, 4096)][b],
				m_biomeNoise[Mod(xLow * 64 + zLow + 65, 4096)][b],
				Mod(x, 1.f),
				Mod(z, 1.f)) / multiplier;
		}
	}
	BiomeComponent::eBiomeTypes highestBiome = BiomeComponent::BIOME_COUNT;
	for (BiomeComponent::eBiomeTypes b = (BiomeComponent::eBiomeTypes) 0; b < BiomeComponent::BIOME_COUNT; b = (BiomeComponent::eBiomeTypes) (b + 1))
	{
		if (biomeWeights[b] > biomeWeights[highestBiome] || highestBiome == BiomeComponent::BIOME_COUNT) highestBiome = b;
	}
	return highestBiome;
}

