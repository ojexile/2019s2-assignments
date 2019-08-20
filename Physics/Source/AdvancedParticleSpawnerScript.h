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

public:

};