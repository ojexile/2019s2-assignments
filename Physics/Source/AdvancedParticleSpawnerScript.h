#pragma once
#include "ParticleSpawnerScript.h"

/*
author: lorenzo yanga
desc: ParticleSpawnerScript with more variables passed to
*/
class AdvancedParticleSpawnerScript : public ParticleSpawnerScript
{
private:
	//GameObject* m_ParticleRef;
	//const float m_fSpawnRate;
	//const Vector3 m_vSpawnRadius;
	//const float m_fSizeOffset;
	const float m_fParticleLifetimeOffset;

	const Vector3 m_vSpawnDirection;
	const Vector3 m_vSpawnDirectionOffset;
	const float m_fSpawnSpeed;
	const float m_vAccelOffset;
	const float m_fSpawnSpeedOffset;
	 
	const Vector3 m_vSpeedOffset;
	const float m_fRotateOffset;
	
	/// spawner parameters
	//const float m_fLifeTime;
	//float m_fCurrentTime;
	//float m_fCurrentLifeTime;
	//std::string m_sLayer;
};