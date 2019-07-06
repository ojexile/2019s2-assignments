#pragma once
#include "ScriptComponent.h"
class ParticleScript :
	public ScriptComponent
{
private:
	const float m_fLiftTime;
	const float m_fAngle;
	const float m_fGravity;
	const float m_fSpeed;
	const float m_fAccel;
	const float m_fSizeChange;
public:
	ParticleScript(const float fLifeTime, const float fAngle, const float fGravity, const float fSpeed, const float fAccel, const float fSizeChange);
	virtual ~ParticleScript();

	// virtual void Start();
	virtual void Update(double dt) override;
};
