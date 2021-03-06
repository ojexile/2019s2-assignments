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
	if (PlayerInRange(com))
		return com->GetComponent<EntityScript>()->GetBehaviour()->GetCombatState();
	if (m_SW.GetTime() < m_fTime)
		return this;
	else
		return com->GetComponent<EntityScript>()->GetBehaviour()->GetWanderState();
}

void IdleState::OnEnter(ComponentBase * com)
{
	GameObject* ret = dynamic_cast<Component*>(com)->GetChild(0);
	if (ret)
		ret->RENDER->ResetColor();
	com->GetComponent<AIEntityScript>()->SetTarget({ 0, 0, 0 });
	m_SW.Start();
	m_fTime = Math::RandFloatMinMax(m_fMinTime, m_fMaxTime);
}

void IdleState::OnExit(ComponentBase * com)
{
}