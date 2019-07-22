#include "ParticleScript.h"
#include "Time.h"
ParticleScript::ParticleScript(const float fLifeTime, const Vector3 vSpeed,
	const Vector3 vGravity, const Vector3 vAccel, const Vector3 vSizeChange, const Vector3 vRandAxis, Vector3 sin, Vector3 sinfreq)
	: m_fLifeTime(fLifeTime)
	, m_vSpeed(vSpeed)
	, m_vGravity(vGravity)
	, m_vAccel(vAccel)
	, m_vSizeChange(vSizeChange)
	, m_vRandAxis(vRandAxis)
	, m_vSin(sin)
	, m_vSinFreq(sinfreq)
{
	m_CurrentDuration = 0;
	if (m_vRandAxis.x > 0)
	{
		int x = 0;
	}
}

ParticleScript::~ParticleScript()
{
}

void ParticleScript::Update(double dt)
{
	if (!Started)
	{
		if (m_vRandAxis.x > 0)
		{
			try
			{
				m_vSpeed.x = Math::RandFloatMinMax(-m_vSpeed.x, m_vSpeed.x);
			}
			catch (const std::exception&)
			{
				DEFAULT_LOG("Speed is 0 for x axis");
			}
		}

		if (m_vRandAxis.y > 0)
		{
			try
			{
				m_vSpeed.y = Math::RandFloatMinMax(-m_vSpeed.y, m_vSpeed.y);
			}
			catch (const std::exception&)
			{
				DEFAULT_LOG("Speed is 0 for y axis");
			}
		}
		if (m_vRandAxis.z > 0)
		{
			try
			{
				m_vSpeed.z = Math::RandFloatMinMax(-m_vSpeed.z, m_vSpeed.z);
			}
			catch (const std::exception&)
			{
				DEFAULT_LOG("Speed is 0 for z axis");
			}
		}

		Started = true;
	}
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
	Trans->SetScale(vNewScale.y, vNewScale.y, vNewScale.z);
	// Sin
	Vector3 vSinOffset;
	if (m_vSin.x > 0)
		vSinOffset.x = m_vSin.x * sin(Time::GetInstance()->GetElapsedTimeF() * m_vSinFreq.x);
	if (m_vSin.y > 0)
		vSinOffset.y = m_vSin.y * sin(Time::GetInstance()->GetElapsedTimeF() * m_vSinFreq.y);
	if (m_vSin.z > 0)
		vSinOffset.z = m_vSin.z * sin(Time::GetInstance()->GetElapsedTimeF() * m_vSinFreq.z);
	Trans->Translate(vSinOffset);
	// Cos
	Vector3 vCosOffset;
	if (m_vCos.x > 0)
		vCosOffset.x = m_vCos.x * cos(Time::GetInstance()->GetElapsedTimeF() * m_vCosFreq.x);
	if (m_vCos.y > 0)
		vCosOffset.y = m_vCos.y * cos(Time::GetInstance()->GetElapsedTimeF() * m_vCosFreq.y);
	if (m_vCos.z > 0)
		vCosOffset.z = m_vCos.z * cos(Time::GetInstance()->GetElapsedTimeF() * m_vCosFreq.z);
	Trans->Translate(vCosOffset);
	// rot
	if (m_vRotateRate.x > 0)
		Trans->RotateBy(m_vRotateRate.x * (float)dt, { 1, 0, 0 });
	if (m_vRotateRate.y > 0)
		Trans->RotateBy(m_vRotateRate.y * (float)dt, Vector3{ 0, 1, 0 });
	if (m_vRotateRate.z > 0)
		Trans->RotateBy(m_vRotateRate.z * (float)dt, { 0, 0, 1 });
	//--------------------------------------------------------------------------------
	m_CurrentDuration += (float)dt;
	// LifeTime
	if (m_CurrentDuration >= m_fLifeTime)
	{
		// Destroy object
		DestroySelf();
	}
}
void ParticleScript::SetCos(Vector3 a, Vector3 f)
{
	m_vCos = a;
	m_vCosFreq = f;
}
void ParticleScript::SetRot(Vector3 v)
{
	m_vRotateRate = v;
}