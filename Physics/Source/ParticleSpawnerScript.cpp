#include "ParticleSpawnerScript.h"

ParticleSpawnerScript::ParticleSpawnerScript(GameObject* ParticleRef, const float fSpawnRate, const Vector3 vSpawnRadius, const float fSizeOffset)
	: m_ParticleRef(ParticleRef)
	, m_fSpawnRate(fSpawnRate)
	, m_vSpawnRadius(vSpawnRadius)
	, m_fSizeOffset(fSizeOffset)
{
	m_fCurrentTime = 0;
}

ParticleSpawnerScript::~ParticleSpawnerScript()
{
}

void ParticleSpawnerScript::Update(double dt)
{
	m_fCurrentTime += (float)dt;
	//--------------------------------------------------------------------------------
	if (m_fCurrentTime <= m_fSpawnRate)
		return;
	m_fCurrentTime = 0;
	TransformComponent* Trans = GetComponent<TransformComponent>();
	Vector3 vScale = { Math::RandFloatMinMax(-(100 - m_fSizeOffset), (100 + m_fSizeOffset)),Math::RandFloatMinMax(-(100 - m_fSizeOffset), (100 + m_fSizeOffset)) , Math::RandFloatMinMax(-(100 - m_fSizeOffset), (100 + m_fSizeOffset)) };

	float fXPos = Trans->GetPosition().x + Math::RandFloatMinMax(-m_vSpawnRadius.x, m_vSpawnRadius.x);
	float fYPos = Trans->GetPosition().x + Math::RandFloatMinMax(-m_vSpawnRadius.y, m_vSpawnRadius.y);
	float fZPos = Trans->GetPosition().x + Math::RandFloatMinMax(-m_vSpawnRadius.z, m_vSpawnRadius.z);
	Vector3 SpawnPosition = { fXPos, fYPos, fZPos };
	Instantiate(m_ParticleRef, SpawnPosition, {}, vScale);
}