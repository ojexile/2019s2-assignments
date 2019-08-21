#include "BirdWingScript.h"

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
	float rate = 20 * (float)dt;
	if (!m_bUp)
		rate = -rate;
	m_fAngle += rate;

	GameObject* l = GetChild(1);
	GameObject* r = GetChild(2);

	l->TRANS->SetRelativeRotation(m_fAngle, 0, 1, 0);
	r->TRANS->SetRelativeRotation(m_fAngle, 0, 1, 0);

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

	CHENG_LOG("Wing: ", std::to_string(m_fAngle));
}