#include "ParticleSpawnerScript.h"

ParticleSpawnerScript::ParticleSpawnerScript(GameObject* ParticleRef, const float fSpawnRate,
	const Vector3 vSpawnRadius, const float fSizeOffset, std::string sLayer, float fLifeTime)
	: m_ParticleRef(ParticleRef)
	, m_fSpawnRate(1.f / fSpawnRate)
	, m_vSpawnRadius(vSpawnRadius)
	, m_fSizeOffset(fSizeOffset)
	, m_sLayer(sLayer)
	, m_fLifeTime(fLifeTime)
{
	m_fCurrentTime = 0.f;
	m_fCurrentLifeTime = 0.f;
}

ParticleSpawnerScript::~ParticleSpawnerScript()
{
	// delete m_ParticleRef;
}

void ParticleSpawnerScript::Update(double dt)
{
	m_fCurrentTime += (float)dt;
	m_fCurrentLifeTime += (float)dt;
	//--------------------------------------------------------------------------------
	if (m_fCurrentTime <= m_fSpawnRate)
		return;

	else
	{
		do
		{
			m_fCurrentTime -= m_fSpawnRate;
			TransformComponent* Trans = GetComponent<TransformComponent>();
			Vector3 vCurrentScale = Trans->GetScale();
			//vCurrentScale = { 20,20,20 };
			Vector3 vScale;
			Vector3 vBaseScale = m_ParticleRef->TRANS->GetScale();
			vScale.x = Math::RandFloatMinMax((vBaseScale.x - m_fSizeOffset), (vBaseScale.x + m_fSizeOffset));
			vScale.y = Math::RandFloatMinMax((vBaseScale.y - m_fSizeOffset), (vBaseScale.y + m_fSizeOffset));
			vScale.z = Math::RandFloatMinMax((vBaseScale.z - m_fSizeOffset), (vBaseScale.z + m_fSizeOffset));
			vScale.x *= vCurrentScale.x;
			vScale.y *= vCurrentScale.y;
			vScale.z *= vCurrentScale.z;
			//vScale = vScale * 20;
			float fXPos = Trans->GetPosition().x + Math::RandFloatMinMax(-m_vSpawnRadius.x, m_vSpawnRadius.x);
			float fYPos = Trans->GetPosition().y + Math::RandFloatMinMax(-m_vSpawnRadius.y, m_vSpawnRadius.y);
			float fZPos = Trans->GetPosition().z + Math::RandFloatMinMax(-m_vSpawnRadius.z, m_vSpawnRadius.z);
			Vector3 SpawnPosition = Vector3{ fXPos, fYPos, fZPos };
			Instantiate(m_ParticleRef, SpawnPosition, vScale, m_sLayer);
		} while (m_fCurrentTime >= m_fSpawnRate);
	}
	//--------------------------------------------------------------------------------
	if (m_fLifeTime > 0) // if lifetime is positive, i.e. not infinite
	{
		if (m_fCurrentLifeTime >= m_fLifeTime)
			DestroySelf();
	}
}