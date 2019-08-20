#include "IdleState.h"
#include "WanderState.h"
#include "EntityScript.h"
#include "AIStatesList.h"
#include "AIEntityScript.h"

#define MIN_TIME 0.1f
#define MAX_TIME 4

IdleState::IdleState()
{
	m_fTime = 0;
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
	m_fTime = Math::RandFloatMinMax(MIN_TIME, MAX_TIME);
}

void IdleState::OnExit(ComponentBase * com)
{
}