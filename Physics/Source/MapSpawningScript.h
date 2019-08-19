#pragma once
#include "ChunkData.h"
#include "ScriptComponent.h"
#include <set>
class MapSpawningScript :
	public ScriptComponent
{
private:
	std::map<Vector3, std::map<unsigned char, unsigned int>> m_connections;
	std::set<Vector3> m_spawnedLocations;
public:
	MapSpawningScript();
	virtual ~MapSpawningScript();
	virtual void Update(double dt) override;
	virtual Component* Clone() { return new MapSpawningScript(*this); };
};
