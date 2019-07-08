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
	std::string m_sLayer;
public:
	ParticleSpawnerScript(GameObject* ParticleRef, const float fSpawnRate, const Vector3 vSpawnRadius, const float fSizeOffset, std::string sLayer = "Default");
	virtual ~ParticleSpawnerScript();
	virtual ComponentBase* Clone()
	{
		return new ParticleSpawnerScript(*this);
	}

	virtual void Update(double dt) override;
};
