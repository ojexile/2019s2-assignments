#pragma once
#include "ChunkData.h"
#include "ScriptComponent.h"
#include "BiomeComponent.h"
#include <set>
class MapSpawningScript :
	public ScriptComponent
{
private:
	std::map<Vector3, std::map<unsigned char, unsigned int>> m_connections;
	std::set<Vector3> m_spawnedLocations;
	std::set<std::pair<Vector3, BiomeComponent::eBiomeTypes>> m_biomeToVec3Mapping;
	std::vector<Vector3> m_biomeNoise;
public:
	MapSpawningScript();
	virtual ~MapSpawningScript();
	virtual void Update(double dt) override;
	virtual Component* Clone() { return new MapSpawningScript(*this); };
	Vector3 GetNoiseAt(Vector3 v);
	BiomeComponent::eBiomeTypes GetBiomeFromNoise(Vector3 noise);
};
