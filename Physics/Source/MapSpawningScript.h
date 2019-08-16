#pragma once
#include "ChunkData.h"
#include "ScriptComponent.h"
#include <set>
class MapSpawningScript :
	public ScriptComponent
{
private:
	std::set<Vector3> m_spawnedLocations;
public:
	MapSpawningScript();
	virtual ~MapSpawningScript();
	virtual void Update(double dt) override;
	virtual ComponentBase* Clone() { return new MapSpawningScript(*this); };
};
