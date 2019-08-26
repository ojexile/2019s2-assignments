#include "MapSpawningScript.h"
#include "SceneManager.h"
#include "DataContainer.h"
#include "ChunkCollider.h"
#include "ChunkEvent.h"

#include "Utility.h"

#include <algorithm>
#include <random>
#include <array>

#define NCHUNKS 16
#define FLATMAP false
MapSpawningScript::MapSpawningScript()
{
	for (int i = 0; i < 4096; ++i)
	{
		m_biomeNoise.emplace_back(Vector3(sin(Math::RandFloatMinMax(-Math::PI, Math::PI)), sin(Math::RandFloatMinMax(-Math::PI, Math::PI)), sin(Math::RandFloatMinMax(-Math::PI, Math::PI))));
	}
	m_biomeToVec3Mapping.emplace(Vector3(0, -1, 0), BiomeComponent::BIOME_BEACHY);
	m_biomeToVec3Mapping.emplace(Vector3(0, 0, 0), BiomeComponent::BIOME_PLAINS);
	m_biomeToVec3Mapping.emplace(Vector3(0, 1, 0), BiomeComponent::BIOME_SNOW);
	m_biomeToVec3Mapping.emplace(Vector3(1, 0, 0), BiomeComponent::BIOME_MESA);
	m_biomeToVec3Mapping.emplace(Vector3(0, 0, 1), BiomeComponent::BIOME_GAMEBOY);
	m_biomeToVec3Mapping.emplace(Vector3(0, 1, 1), BiomeComponent::BIOME_VOID);
	m_biomeToVec3Mapping.emplace(Vector3(-1, 0, 1), BiomeComponent::BIOME_CRIMSON);
	m_biomeToVec3Mapping.emplace(Vector3(-1, -1, 1), BiomeComponent::BIOME_MONOCHROME);
}

MapSpawningScript::~MapSpawningScript()
{
}

const char* GetChunkByID(int id)
{
#if FLATMAP
	return "flat";
#endif
	switch (id)
	{
	case 0:
	case 1:
		return "archway";
	case 2:
		return "goldmine";
	case 3:
		return "smallhouse";
	case 4:
		return "bazaar1";
	case 13:
		return "flat";
	case 5:
		return "barline_3";
	case 6:
		return "bazaar1_1";
	case 7:
		return "bazaar1_2";
	case 8:
		return "bazaar1_3";
	case 9:
	case 10:
		return "barline";
	case 11:
		return "barline_1";
	case 12:
		return "barline_2";
	default:
		return "archway";
	}
}

const char* RandomChunk()
{
	return GetChunkByID(Math::RandIntMinMax(0, 16));
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
	std::array<int, 5> orderX{ -2, -1, 0, 1, 2 };
	std::array<int, 5> orderZ{ -2, -1, 0, 1, 2 };

	std::shuffle(orderX.begin(), orderX.end(), std::default_random_engine(Math::RandIntMinMax(0, 100000)));
	std::shuffle(orderZ.begin(), orderZ.end(), std::default_random_engine(Math::RandIntMinMax(0, 100000)));
	for (auto it1 = orderX.begin(); it1 != orderX.end(); ++it1)
	{
		for (auto it2 = orderZ.begin(); it2 != orderZ.end(); ++it2)
		{
			int x = *it1;
			int z = *it2;
			int offsetX = (int)floor(v.x / 16.f) + x;
			int offsetZ = (int)floor(v.z / 16.f) + z;
			if (m_spawnedLocations.count(Vector3((float)offsetX, 0, (float)offsetZ))) continue;
			std::vector<ChunkData*> validChunks;
			ChunkData* chunk;
			for (int nChunksTried = 0; nChunksTried < NCHUNKS; nChunksTried++)
			{
				bool fits = true;
				chunk = dataContainer->GetChunk(GetChunkByID(nChunksTried));
				for (int xDiff = 0; xDiff < chunk->GetSize().x / 16; ++xDiff)
					for (int zDiff = 0; zDiff < chunk->GetSize().z / 16; ++zDiff)
						if (m_spawnedLocations.count(Vector3((float)offsetX + (float)xDiff, 0, (float)offsetZ + (float)zDiff)))
						{
							fits = false;
						}
				if (fits)
					validChunks.push_back(chunk);
			}
			if (validChunks.size() == 0) return;
			chunk = validChunks[Math::RandIntMinMax(0, validChunks.size() - 1)];
			GameObject* go = GOM->AddGameObject();
			go->m_sName = "Chunk";
			Vector3 goPos = Vector3((float)offsetX * 16, 0, (float)offsetZ * 16);
			go->TRANS->SetPosition(goPos);
			RenderComponent* render = new RenderComponent(chunk->GenerateMeshBiomed());
			render->SetRenderDistance(100);
			go->AddComponent(render);
			go->AddComponent(new BiomeComponent(GetBiomeAt(Vector3((float)offsetX, 0, (float)offsetZ))));
			//
			go->AddComponent(new ChunkCollider(chunk));

#ifdef DEBUG_NUMBERS
			for (int i = 0; i < 4; ++i) {
				GameObject* s0 = GOM->AddGameObject("UI");
				Vector3 ks = Vector3(-6, 0, 0);
				Mtx44 mr; mr.SetToRotation(i * 90, 0, -1, 0);
				s0->TRANS->SetPosition(goPos + Vector3(8, 22, 8) + mr * ks);
				s0->TRANS->SetScale(Vector3(3, 3, 3));
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
					m_spawnedLocations.emplace(Vector3((float)offsetX + (float)xDiff, 0, (float)offsetZ + (float)zDiff));
					m_connections[Vector3((float)offsetX + (float)xDiff + 1, 0, (float)offsetZ + (float)zDiff)][0] = chunk->GetChunkConnection(Vector3((float)xDiff, 0, (float)zDiff), 2); // 0 = -x
					m_connections[Vector3((float)offsetX + (float)xDiff, 0, (float)offsetZ + (float)zDiff + 1)][1] = chunk->GetChunkConnection(Vector3((float)xDiff, 0, (float)zDiff), 3); // 1 = -z
					m_connections[Vector3((float)offsetX + (float)xDiff - 1, 0, (float)offsetZ + (float)zDiff)][2] = chunk->GetChunkConnection(Vector3((float)xDiff, 0, (float)zDiff), 0); // 2 = +x
					m_connections[Vector3((float)offsetX + (float)xDiff, 0, (float)offsetZ + (float)zDiff - 1)][3] = chunk->GetChunkConnection(Vector3((float)xDiff, 0, (float)zDiff), 1); // 3 = +z (from centre of chunk)
				}

			for (int xDiff = 0; xDiff < chunk->GetSize().x / 16; ++xDiff)
				for (int zDiff = 0; zDiff < chunk->GetSize().z / 16; ++zDiff)
				{
					Vector3 noise = GetNoiseAt(Vector3(((float)offsetX + (float)xDiff) / 3, 0, (float)((float)offsetZ + (float)zDiff) / 3)) * 1.5 + Vector3(1.5f, 1.5f, 1.5f);
					noise.y = 0;
					if (floor(noise.x) == Mod(offsetX + xDiff, 3))
						if (floor(noise.z) == Mod(offsetZ + zDiff, 3))
						{
							chunk->GetEvent()->GenerateEvent(GOM, chunk, go->TRANS->GetPosition());
							chunk->GetEvent()->GenerateEntities(GOM, chunk, go->TRANS->GetPosition(), go->GetComponent<BiomeComponent>()->GetBiomeType());
						}
				}
		}
	}
}

Vector3 MapSpawningScript::GetNoiseAt(Vector3 v)
{
	Vector3 biomeWeights;
	int X = (int)v.x;
	int Z = (int)v.z;
	float multiplier = 1;
	for (int i = 1; i < 12; ++i)
	{
		float x = X * multiplier;
		float z = Z * multiplier;
		x = Mod(x + 14, 64.f);
		z = Mod(z + 14, 64.f);
		int xLow = (int)floor(x);
		int zLow = (int)floor(z);
		int offset = ((((i * 351863) % 49231 + 1077) * 9221 + 829) % 34 * 24177) % 4096; //bad set rng
		biomeWeights.x += BiLerp2D(m_biomeNoise[(offset + xLow * 64 + zLow) % 4096].x,
			m_biomeNoise[(offset + xLow * 64 + Mod(zLow + 1, 64)) % 4096].x,
			m_biomeNoise[(offset + Mod(xLow + 1, 64) * 64 + zLow) % 4096].x,
			m_biomeNoise[(offset + Mod(xLow + 1, 64) * 64 + Mod(zLow + 1, 64)) % 4096].x,
			Mod(x, 1.f),
			Mod(z, 1.f)) / multiplier;
		biomeWeights.y += BiLerp2D(m_biomeNoise[(offset + xLow * 64 + zLow) % 4096].y,
			m_biomeNoise[(offset + xLow * 64 + Mod(zLow + 1, 64)) % 4096].y,
			m_biomeNoise[(offset + Mod(xLow + 1, 64) * 64 + zLow) % 4096].y,
			m_biomeNoise[(offset + Mod(xLow + 1, 64) * 64 + Mod(zLow + 1, 64)) % 4096].y,
			Mod(x, 1.f),
			Mod(z, 1.f)) / multiplier;
		biomeWeights.z += BiLerp2D(m_biomeNoise[(offset + xLow * 64 + zLow) % 4096].z,
			m_biomeNoise[(offset + xLow * 64 + Mod(zLow + 1, 64)) % 4096].z,
			m_biomeNoise[(offset + Mod(xLow + 1, 64) * 64 + zLow) % 4096].z,
			m_biomeNoise[(offset + Mod(xLow + 1, 64) * 64 + Mod(zLow + 1, 64)) % 4096].z,
			Mod(x, 1.f),
			Mod(z, 1.f)) / multiplier;
		multiplier *= 2;
	}
	return biomeWeights;
}

BiomeComponent::eBiomeTypes MapSpawningScript::GetBiomeFromNoise(Vector3 vec)
{
	std::map<float, BiomeComponent::eBiomeTypes> neighbors;
	for (auto i = m_biomeToVec3Mapping.begin(); i != m_biomeToVec3Mapping.end(); ++i)
	{
		neighbors.emplace(1 / (i->first - vec).Length(), i->second);
	}
	unsigned i = 0;
	std::map< BiomeComponent::eBiomeTypes, float> output;
	for (auto m = neighbors.begin(); i < m_biomeToVec3Mapping.size() && m != neighbors.end(); ++i, ++m)
	{
		output[m->second] += m->first;
	}
	std::map< float, BiomeComponent::eBiomeTypes> candidates;
	for (auto m = output.begin(); m != output.end(); ++m)
	{
		candidates[m->second] = m->first;
	}
	auto x = candidates.rbegin();
	BiomeComponent::eBiomeTypes one = x->second;
	float oneW = x->first;
	return one;
}

BiomeComponent::eBiomeTypes MapSpawningScript::GetBiomeAt(Vector3 vec)
{
	int x = (int)(vec.x / 7);
	int z = (int)(vec.z / 7);

	BiomeComponent::eBiomeTypes a00 = GetBiomeFromNoise(GetNoiseAt(Vector3((float)x, 0, (float)z)));
	BiomeComponent::eBiomeTypes a01 = GetBiomeFromNoise(GetNoiseAt(Vector3((float)x, 0, (float)z + 1)));
	BiomeComponent::eBiomeTypes a10 = GetBiomeFromNoise(GetNoiseAt(Vector3((float)x + 1, 0, (float)z)));
	BiomeComponent::eBiomeTypes a11 = GetBiomeFromNoise(GetNoiseAt(Vector3((float)x + 1, 0, (float)z + 1)));

	float f00 = ((Vector3((float)x, 0, (float)z) - vec * (1 / 7.f)).IsZero() ? 1000000 : 1 / ((Vector3((float)x, 0, (float)z) - vec * (1 / 7.f)).Length()));
	float f01 = ((Vector3((float)x, 0, (float)z + 1) - vec * (1 / 7.f)).IsZero() ? 1000000 : 1 / ((Vector3((float)x, 0, (float)z + 1) - vec * (1 / 7.f)).Length()));
	float f10 = ((Vector3((float)x + 1, 0, (float)z) - vec * (1 / 7.f)).IsZero() ? 1000000 : 1 / ((Vector3((float)x + 1, 0, (float)z) - vec * (1 / 7.f)).Length()));
	float f11 = ((Vector3((float)x + 1, 0, (float)z + 1) - vec * (1 / 7.f)).IsZero() ? 1000000 : 1 / ((Vector3((float)x + 1, 0, (float)z + 1) - vec * (1 / 7.f)).Length()));

	float sum = f00 + f01 + f10 + f11;
	float rand = Math::RandFloatMinMax(0, sum);
	if (rand < f00) return a00;
	if (rand < f00 + f01) return a01;
	if (rand < f00 + f01 + f10) return a10;
	return a11;
}