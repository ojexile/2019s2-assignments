#include "WanderState.h"
#include "EntityScript.h"
#include "IdleState.h"

#define MIN_TIME 1
#define MAX_TIME 5

WanderState::WanderState()
{
	m_fTime = 0;
}


WanderState::~WanderState()
{
}

State * WanderState::HandleState(ComponentBase * com)
{
	if (m_SW.Stop()->GetTime() < m_fTime)
	{
		com->GetComponent<EntityScript>()->Move(m_vDir);
		return this;
	}
	else
		return new IdleState;
}

void WanderState::OnEnter(ComponentBase * com)
{
	m_SW.Start();
	m_fTime = Math::RandFloatMinMax(MIN_TIME, MAX_TIME);
	// Rand dir
	m_vDir.x = Math::RandFloatMinMax(0.1f, 1);
	m_vDir.z = Math::RandFloatMinMax(0.1f, 1);
	m_vDir.Normalize();
}

void WanderState::OnExit(ComponentBase * com)
{
}
