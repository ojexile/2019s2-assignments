#include "ParticleScript.h"

ParticleScript::ParticleScript(const float fLifeTime, const Vector3 vSpeed, const Vector3 vGravity, const Vector3 vAccel, const Vector3 vSizeChange)
	: m_fLifeTime(fLifeTime)
	, m_vSpeed(vSpeed)
	, m_vGravity(vGravity)
	, m_vAccel(vAccel)
	, m_vSizeChange(vSizeChange)
{
	m_CurrentDuration = 0;
}

ParticleScript::~ParticleScript()
{
}

void ParticleScript::Update(double dt)
{
	TransformComponent* Trans = GetComponent<TransformComponent>();
	//--------------------------------------------------------------------------------
	// Move
	Trans->Translate(m_vSpeed);
	// Gravity
	if (!m_vGravity.IsZero())
	{
		Trans->Translate(m_vGravity * (float)dt);
	}
	// Accel
	m_vSpeed += m_vAccel * (float)dt;
	// Size change
	Vector3 vCurrentScale = Trans->GetScale();
	Vector3 vNewScale = vCurrentScale + (float)dt * m_vSizeChange;
	if (vNewScale.x <= 0)
	{
		DestroySelf();
		return;
	}
	if (vNewScale.y <= 0)
	{
		DestroySelf();
		return;
	}
	if (vNewScale.z <= 0)
	{
		DestroySelf();
		return;
	}
	// Should destroy
	Trans->SetScale(vNewScale.y, vNewScale.y, vNewScale.z);
	//--------------------------------------------------------------------------------
	m_CurrentDuration += (float)dt;
	// LifeTime
	if (m_CurrentDuration >= m_fLifeTime)
	{
		// Destroy object
		DestroySelf();
	}
}