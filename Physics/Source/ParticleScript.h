#pragma once
#include "ScriptComponent.h"
class ParticleScript :
	public ScriptComponent
{
private:
	const float m_fLifeTime;
	Vector3 m_vSpeed;
	const Vector3 m_vGravity;
	const Vector3 m_vAccel;
	const Vector3 m_vSizeChange;

	float m_CurrentDuration;
public:
	ParticleScript(const float fLifeTime, const Vector3 vSpeed, const Vector3 vGravity, const Vector3 vAccel, const Vector3 vSizeChange);
	virtual ~ParticleScript();

	// virtual void Start();
	virtual void Update(double dt) override;
};
