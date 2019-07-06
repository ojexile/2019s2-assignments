#include "ParticleScript.h"

ParticleScript::ParticleScript(const float fLifeTime, const float fAngle, const float fGravity, const float fSpeed, const float fAccel, const float fSizeChange)
	: m_fLiftTime(fLifeTime)
	, m_fAngle(fAngle)
	, m_fGravity(fGravity)
	, m_fSpeed(fSpeed)
	, m_fAccel(fAccel)
	, m_fSizeChange(fSizeChange)
{
}

ParticleScript::~ParticleScript()
{
}

void ParticleScript::Update(double dt)
{
}