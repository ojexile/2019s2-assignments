#include "IdleState.h"
#include "WanderState.h"
#include "EntityScript.h"

#define MIN_TIME 1
#define MAX_TIME 5

IdleState::IdleState(State* Combat)
{
	m_fTime = 0;
	m_Combat = Combat;
}


IdleState::~IdleState()
{
}

State * IdleState::HandleState(ComponentBase * com)
{
	if (m_SW.Stop()->GetTime() < m_fTime)
		return this;
	else
		return new WanderState(m_Combat);
}

void IdleState::OnEnter(ComponentBase * com)
{
	m_SW.Start();
	m_fTime = Math::RandFloatMinMax(MIN_TIME, MAX_TIME);
}

void IdleState::OnExit(ComponentBase * com)
{
}
