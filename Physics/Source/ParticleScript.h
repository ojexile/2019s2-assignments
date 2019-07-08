#pragma once
#include "ScriptComponent.h"
#include <cstdlib>
class ParticleScript :
	public ScriptComponent
{
private:
	const float m_fLifeTime;
	Vector3 m_vSpeed;
	const Vector3 m_vGravity;
	const Vector3 m_vAccel;
	const Vector3 m_vSizeChange;
	const Vector3 m_vRandAxis;
	float m_CurrentDuration;
	bool Started = false;
public:
	ParticleScript(const float fLifeTime, const Vector3 vSpeed, 
		const Vector3 vGravity, const Vector3 vAccel, 
		const Vector3 vSizeChange
	, const Vector3 vRandAxis);
	virtual ~ParticleScript();
	virtual ComponentBase* Clone()
	{
		return new ParticleScript(*this);
	}

	// virtual void Start();
	virtual void Update(double dt) override;
};
