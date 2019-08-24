#include "BirdWingScript.h"
#include "WorldValues.h"

BirdWingScript::BirdWingScript()
{
	m_fAngle = 0;
	m_bUp = false;
}

BirdWingScript::~BirdWingScript()
{
}

void BirdWingScript::Update(double dt)
{
	float rate = 800 * (float)dt;
	if (!m_bUp)
		rate = -rate;
	m_fAngle += rate;

	GameObject* l = GetChild(1);
	GameObject* r = GetChild(2);

	l->TRANS->SetRelativeRotation(m_fAngle, 0, 0, 1);
	r->TRANS->SetRelativeRotation(-m_fAngle, 0, 0, 1);

	float max = 50;
	if (m_fAngle > max)
	{
		m_fAngle = max;
		m_bUp = !m_bUp;
	}
	else if (m_fAngle < -max)
	{
		m_fAngle = -max;
		m_bUp = !m_bUp;
	}
}