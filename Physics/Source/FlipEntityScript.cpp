#include "FlipEntityScript.h"

FlipEntityScript::FlipEntityScript()
	: InteractionBaseScript(),
	m_flipDirection(FLIP_NONE),
	m_fRotationAmount(0.f)
{
	
}

FlipEntityScript::~FlipEntityScript()
{
}

void FlipEntityScript::Update(double dt)
{
	if (!m_bIsTriggered)
		return;

	if (m_fTimeElapsed > m_fMaximumTimeElapsed)
		return;

	m_fTimeElapsed += (float)dt;
	m_fRotationAmount = m_fTimeElapsed / m_fMaximumTimeElapsed * 90;

	TRANS->SetRotation(m_fRotationAmount, 1, 0, 0);
}

void FlipEntityScript::Trigger(GameObject * go, GameObject * go2)
{
	m_bIsTriggered = true;
	// determine flip direction here

}
