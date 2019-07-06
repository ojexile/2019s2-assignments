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

	float m_fCurrentTime;
public:
	ParticleSpawnerScript(GameObject* ParticleRef, const float fSpawnRate, const Vector3 vSpawnRadius, const float fSizeOffset);
	virtual ~ParticleSpawnerScript();
	virtual ComponentBase* Clone()
	{
		return new ParticleSpawnerScript(*this);
	}

	virtual void Update(double dt) override;
};
