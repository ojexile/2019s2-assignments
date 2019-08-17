#pragma once
#include "ScriptComponent.h"
class ParticleSpawnerScript :
	public ScriptComponent
{
private:
	GameObject* m_ParticleRef;
	const float m_fSpawnRate;
	const Vector3 m_vSpawnRadius;
	const float m_fSizeOffset;
	const float m_fLifeTime;

	float m_fCurrentTime;
	float m_fCurrentLifeTime;
	std::string m_sLayer;
public:
	ParticleSpawnerScript(GameObject* ParticleRef, const float fSpawnRate,
		const Vector3 vSpawnRadius, const float fSizeOffset, std::string sLayer = "Default", const float fLifeTime = -1);
	virtual ~ParticleSpawnerScript();
	virtual Component* Clone()
	{
		ParticleSpawnerScript* pss = new ParticleSpawnerScript(*this);
		pss->m_ParticleRef = m_ParticleRef->Clone();
		return pss;
	}

	virtual void Update(double dt) override;
};
