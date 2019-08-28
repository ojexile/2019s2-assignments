#include "FlipEntityScript.h"
#define FLIP_RADIUS 5.f

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
	auto rendered = GetChild(0);

	switch (m_flipDirection)
	{
	case FLIP_NORTH:
		rendered->TRANS->SetRotation(m_fRotationAmount, 1, 0, 0);
		break;
	case FLIP_SOUTH:
		rendered->TRANS->SetRotation(-m_fRotationAmount, 1, 0, 0);
		break;
	case FLIP_EAST:
		rendered->TRANS->SetRotation(m_fRotationAmount, 0, 0, 1);
		break;
	case FLIP_WEST:
		rendered->TRANS->SetRotation(-m_fRotationAmount, 0, 0, 1);
		break;
	}
	rendered->TRANS->SetRelativePosition(0, rendered->TRANS->GetScale().x * m_fTimeElapsed, 0);

}

void FlipEntityScript::Trigger(ComponentBase * player)
{
	if (m_bIsTriggered)
		return;
	// distance check needed
	Vector3 dist = this->GetPosition() - dynamic_cast<Component*>(player)->GetPosition();
	Vector3 distCheck = Vector3(TRANS->GetScale().x, TRANS->GetScale().z, 0.f);
	
	if (dist.LengthSquared() > (distCheck.LengthSquared() + FLIP_RADIUS * FLIP_RADIUS))
		return; // dist check fails
	LZ_LOG("flipenttiyscript there was a yeet detected");
	// determine flip direction here
	dist.Normalize();
	if (Math::FAbs(dist.z) > Math::FAbs(dist.x))
	{
		if (dist.z > 0.f)
		{
			m_flipDirection = FLIP_NORTH;
		}
		else
		{
			m_flipDirection = FLIP_SOUTH;
		}
	}
	else
	{
		if (dist.x > 0.f)
		{
			m_flipDirection = FLIP_WEST;
		}
		else
		{
			m_flipDirection = FLIP_EAST;
		}
	}
	m_bIsTriggered = true;
	
}
