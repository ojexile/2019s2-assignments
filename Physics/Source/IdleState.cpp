#include "IdleState.h"
#include "WanderState.h"
#include "EntityScript.h"
#include "AIStatesList.h"
#include "AIEntityScript.h"

IdleState::IdleState(float min, float max)
{
	m_fTime = 0;
	m_fMinTime = min;
	m_fMaxTime = max;
}

IdleState::~IdleState()
{
}

State * IdleState::HandleState(ComponentBase * com)
{
	com->RENDER->ResetColor();
	if (PlayerInRange(com))
		return com->GetComponent<AIEntityScript>()->GetCombatState();
	if (m_SW.Stop()->GetTime() < m_fTime)
		return this;
	else
		return &AIStatesList::Wander;
}

void IdleState::OnEnter(ComponentBase * com)
{
	m_SW.Start();
	m_fTime = Math::RandFloatMinMax(m_fMinTime, m_fMaxTime);
}

void IdleState::OnExit(ComponentBase * com)
{
}