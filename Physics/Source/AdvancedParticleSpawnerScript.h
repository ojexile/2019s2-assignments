#pragma once
#include "ParticleSpawnerScript.h"
/*
author; lorenzo sayo yanga
desc; particlespawner child class to support 1) one-time triggers, 2) defined spawning patterns
*/

class AdvancedParticleSpawnerScript : public ParticleSpawnerScript
{
public:
	enum eSpawnerType
	{
		SPEW, // spit out at random directions
		CIRCULAR, // spawns multiple particles spawned all on the same y-plane, going outwards in all diff. directions
	};

private:
	int m_iSpawnCount;
	eSpawnerType m_spawnerType;

	bool m_bOneTimeTrigger;
	bool m_Triggered;
public:
	AdvancedParticleSpawnerScript(eSpawnerType type, int spawncount, bool isonetimetrigger, GameObject* refobj, float spawnrate, Vector3 spawnradius, const float fsizeoffset,  std::string layer = "Default", float flifeftime = -1.f);
	~AdvancedParticleSpawnerScript();

	virtual Component* Clone() { return new AdvancedParticleSpawnerScript(*this); }
	virtual void Update(double dt);
	virtual void Trigger();
};