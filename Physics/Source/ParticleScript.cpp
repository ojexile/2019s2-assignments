#include "ParticleScript.h"

ParticleScript::ParticleScript(const float fLifeTime, const Vector3 vSpeed, 
	const Vector3 vGravity, const Vector3 vAccel, const Vector3 vSizeChange, const Vector3 vRandAxis)
	: m_fLifeTime(fLifeTime)
	, m_vSpeed(vSpeed)
	, m_vGravity(vGravity)
	, m_vAccel(vAccel)
	, m_vSizeChange(vSizeChange)
	, m_vRandAxis(vRandAxis)
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
			int pos = (rand() % ((int)m_vSpeed.x * 2)) - m_vSpeed.x;
			m_vSpeed.x = pos;

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
			int pos = rand() % (int)m_vSpeed.y * 2 - m_vSpeed.y;
			m_vSpeed.y = pos;

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
			int pos = rand() % (int)m_vSpeed.z * 2 - m_vSpeed.z;
			m_vSpeed.z = pos;

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